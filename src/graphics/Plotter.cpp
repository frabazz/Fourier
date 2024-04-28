#include "Plotter.hpp"
#include <SDL2/SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <memory>

#define AXIS_WIDTH 3

Plotter::Plotter(SDL_Rect* renderArea, SDL_Renderer* renderer, sample_generator generator,
                 std::shared_ptr<dpair> range, SDL_Color* ax_color, SDL_Color* f_color
) : Component(renderArea, renderer)
{
    _generator = generator;
    _range = range;
    _ax_color = ax_color;
    _f_color = f_color;
    _sample = _generator(_range, _renderArea->w);
}

void Plotter::componentRender(){
    //TODO, add logarithmic scale

    //draw axis
    setColor(_ax_color);
    SDL_Rect x_axis = {0, _renderArea->h - AXIS_WIDTH, _renderArea->w, AXIS_WIDTH};
    SDL_Rect y_axis = {0, 0, AXIS_WIDTH, _renderArea->h - AXIS_WIDTH};
    fillRect(&x_axis);
    fillRect(&y_axis);

    //draw point by point mode
    if(_sample->data->size() >= _renderArea->w){

    }
}
