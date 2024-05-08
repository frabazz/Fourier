#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "Plotter.hpp"
#include "common.hpp"

#define AXIS_WIDTH 3
#define CROSS_SIZE 10

Plotter::Plotter(SDL_Rect* renderArea, SDL_Renderer* renderer,
                 sample_generator generator,
                 dpair* range, color_theme_t* theme,
                 spair* units
) : Component(renderArea, renderer)
{
    _generator = generator;
    _units = units;
    _theme = theme;

    _is_mouse_over = false;
    _mouse_x = 0;
    _mouse_y = 0;

    _range = range;
    _max_y = 0;
    _min_y = 0;

    _data = std::vector<dpair>();
    _generator(_range, 0.5 * _renderArea->w, &_data, &_min_y, &_max_y);

    _x_scale = std::abs(_range->second - _range->first);
    _y_scale  = std::abs(_max_y - _min_y);


}

double Plotter::scaleX(double x){
    //TODO, add logarithmic scale
    return ((x - _range->first)/(_x_scale) * (_renderArea->w - AXIS_WIDTH)) + AXIS_WIDTH;
}

double Plotter::scaleY(double y){
    //TODO, add logarithmic scale
    return (((1 - (y - _min_y)/(_y_scale)) * (_renderArea->h - AXIS_WIDTH)));
}

inline std::string doubleToString(double x, int precision){
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << x;
  return stream.str();
}

void Plotter::componentRender(){
    //draw axis
    setColor(_theme->secondary_color);
    SDL_Rect x_axis = {0, _renderArea->h - AXIS_WIDTH, _renderArea->w, AXIS_WIDTH};
    SDL_Rect y_axis = {0, 0, AXIS_WIDTH, _renderArea->h - AXIS_WIDTH};
    fillRect(&x_axis);
    fillRect(&y_axis);

    //draw function
    setColor(_theme->primary_color);

    for(auto it = _data.begin(); it < _data.end() - 1; ++it){
        //std::cout << "original x : " << it->first << " scaled x : " << scaleX(it->first) << std::endl;
        drawLineAA(
            scaleX(it->first),
            scaleY(it->second),
            scaleX((it + 1)->first),
            scaleY((it + 1)->second),
            _theme->primary_color
        );
    }

    //draw cross and tooltip
    if(_is_mouse_over){
        SDL_RenderDrawLine(_renderer, _mouse_x, _mouse_y - CROSS_SIZE, _mouse_x, _mouse_y + CROSS_SIZE);
        SDL_RenderDrawLine(_renderer, _mouse_x - CROSS_SIZE, _mouse_y, _mouse_x + CROSS_SIZE, _mouse_y);
        SDL_Rect area = {_mouse_x + CROSS_SIZE, _mouse_y + CROSS_SIZE, 200, 20};


        double index_percentage = static_cast<double>(_mouse_x - _renderArea->x - AXIS_WIDTH)/static_cast<double>(_renderArea->w - AXIS_WIDTH);
        int index = std::floor(index_percentage * static_cast<double>(_data.size() - 1));
        std::string text = doubleToString(_data[index].first, 2) + " " + _units->first + ", " + doubleToString(_data[index].second, 2) + " " + _units->second;
        drawToolTip(text, &area, _theme->primary_color);
    }

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
