#include "Plotter.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <mutex>

#define AXIS_WIDTH 3
#define CROSS_SIZE 10

Plotter::Plotter(SDL_Rect* renderArea, SDL_Renderer* renderer, sample_generator generator,
                 dpair* range, SDL_Color* ax_color, SDL_Color* f_color,
                 std::string x_unit, std::string y_unit
) : Component(renderArea, renderer)
{
    _generator = generator;
    _ax_color = ax_color;
    _f_color = f_color;

    _is_mouse_over = false;
    _mouse_x = 0;
    _mouse_y = 0;

    _x_unit = x_unit;
    _y_unit = y_unit;

    _data = NULL;
    _range = range;
    _generator_status = false;
    //recalc if range is updated
    /*
    _max_y = 0;
    _min_y = 0;
    _generator(_range, 0.5 * _renderArea->w, NULL);
    _x_scale = std::abs(_range->second - _range->first);
    _y_scale  = std::abs(_max_y - _min_y);
     */
}

double Plotter::scaleX(double x){
    //TODO, add logarithmic scale
    return ((x - _range->first)/(_x_scale) * (_renderArea->w - AXIS_WIDTH)) + AXIS_WIDTH;
}

double Plotter::scaleY(double y){
    //TODO, add logarithmic scale
    return (((1 - (y - _min_y)/(_y_scale)) * (_renderArea->h - AXIS_WIDTH)));
}

void Plotter::recalc(double min_y, double max_y, std::vector<dpair>* data){
    vecmutex.lock();
    _data = data;

    _max_y = max_y;
    _min_y = min_y;

    _x_scale = std::abs(_range->second - _range->first);
    _y_scale  = std::abs(_max_y - _min_y);

    vecmutex.unlock();
}


inline std::string doubleToString(double x, int precision){
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << x;
  return stream.str();
}

void Plotter::componentRender(){
    //draw axis
    setColor(_ax_color);
    SDL_Rect x_axis = {0, _renderArea->h - AXIS_WIDTH, _renderArea->w, AXIS_WIDTH};
    SDL_Rect y_axis = {0, 0, AXIS_WIDTH, _renderArea->h - AXIS_WIDTH};
    fillRect(&x_axis);
    fillRect(&y_axis);

    //check generator status
    if(_data == NULL){
        if(!_generator_status){
            _generator(_range, 0.5 * _renderArea->w, this);
            _generator_status = true;
        }
        return;
    }

    _generator_status = false;

    //draw function
    setColor(_f_color);

    vecmutex.lock();

    for(auto it = _data->begin(); it < _data->end() - 1; ++it){
        //std::cout << "original x : " << it->first << " scaled x : " << scaleX(it->first) << std::endl;
        drawLineAA(
            scaleX(it->first),
            scaleY(it->second),
            scaleX((it + 1)->first),
            scaleY((it + 1)->second),
            _f_color
        );
    }

    //draw cross and tooltip
    if(_is_mouse_over){
        SDL_RenderDrawLine(_renderer, _mouse_x, _mouse_y - CROSS_SIZE, _mouse_x, _mouse_y + CROSS_SIZE);
        SDL_RenderDrawLine(_renderer, _mouse_x - CROSS_SIZE, _mouse_y, _mouse_x + CROSS_SIZE, _mouse_y);
        SDL_Rect area = {_mouse_x + CROSS_SIZE, _mouse_y + CROSS_SIZE, 200, 20};


        double index_percentage = static_cast<double>(_mouse_x - _renderArea->x - AXIS_WIDTH)/static_cast<double>(_renderArea->w - AXIS_WIDTH);
        int index = std::floor(index_percentage * static_cast<double>(_data->size() - 1));
        std::string text = doubleToString(_data->at(index).first, 2) + " " + _x_unit + ", " + doubleToString(_data->at(index).second, 2) + " " + _y_unit;
        drawToolTip(text, &area, _f_color);
    }

    vecmutex.unlock();
}

void Plotter::feedEvent(SDL_Event* e){
    if(e->type == SDL_MOUSEMOTION){
        _mouse_x = e->motion.x;
        _mouse_y = e->motion.y;

        if(_mouse_x > _renderArea->x + AXIS_WIDTH && _mouse_x < _renderArea->x + _renderArea->w &&
          _mouse_y > _renderArea->y && _mouse_y < _renderArea->y + _renderArea->h - AXIS_WIDTH
        ) _is_mouse_over = true;

        else _is_mouse_over = false;
    }
}
