#ifndef PLOTTER_COMPONENT_H
#define PLOTTER_COMPONENT_H

#include "Component.hpp"
#include <SDL2/SDL.h>
#include "common.hpp"

class Plotter;

/*
** probably shit code, the generator should calculate a function in the given range
** at n points, and return a vector with values, max_x and max_y (to avoid useless
** calculations).
**
** The callback structure
*/


class Plotter : public Component{
    public:
        Plotter(SDL_Rect* _renderArea, SDL_Renderer* _renderer, sample_generator, dpair* range, color_theme_t* theme , spair* units);
        void updateRange(dpair* new_range);
        void feedEvent(SDL_Event* e) override;
    private:
        sample_generator _generator;
        dpair* _range;
        std::vector<dpair> _data;
        double _min_y, _max_y;
        double _x_scale, _y_scale;
        color_theme_t* _theme;
        bool _is_mouse_over;
        int _mouse_x, _mouse_y;
        spair* _units;
        double scaleX(double x);
        double scaleY(double y);
        void componentRender() override;
};

#endif
