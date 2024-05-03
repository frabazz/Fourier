#include "Plotter.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>

#define AXIS_WIDTH 3

Plotter::Plotter(SDL_Rect* renderArea, SDL_Renderer* renderer, sample_generator generator,
                 std::shared_ptr<dpair> range, SDL_Color* ax_color, SDL_Color* f_color
) : Component(renderArea, renderer)
{
    _generator = generator;
    _ax_color = ax_color;
    _f_color = f_color;

    //recalc if range is updated
    _range = range;
    _sample = _generator(_range, _renderArea->w * 0.50);
    _x_scale = std::abs(_range->second - _range->first);
    _y_scale  = std::abs(_sample->max_y - _sample->min_y);

}

double Plotter::scaleX(double x){
    //TODO, add logarithmic scale
    return ((x - _range->first)/(_x_scale) * (_renderArea->w - AXIS_WIDTH)) + AXIS_WIDTH;
}

double Plotter::scaleY(double y){
    //TODO, add logarithmic scale
    std::cout << "min y : " << _sample->min_y << std::endl;
    return (((1 - (y - _sample->min_y)/(_y_scale)) * (_renderArea->h - AXIS_WIDTH)));
}


void Plotter::componentRender(){


    //draw axis
    setColor(_ax_color);
    SDL_Rect x_axis = {0, _renderArea->h - AXIS_WIDTH, _renderArea->w, AXIS_WIDTH};
    SDL_Rect y_axis = {0, 0, AXIS_WIDTH, _renderArea->h - AXIS_WIDTH};
    fillRect(&x_axis);
    fillRect(&y_axis);

    //draw function
    setColor(_f_color);
    for(auto it = _sample->data->begin(); it < _sample->data->end() - 1; ++it){
        //std::cout << "original x : " << it->first << " scaled x : " << scaleX(it->first) << std::endl;
        drawLineAA(
            scaleX(it->first),
            scaleY(it->second),
            scaleX((it + 1)->first),
            scaleY((it + 1)->second),
            _f_color
        );
    }
}
