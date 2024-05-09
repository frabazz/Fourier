#ifndef PLOTTER_COMPONENT_H
#define PLOTTER_COMPONENT_H

#include <SDL2/SDL.h>
#include <chrono>

#include "Component.hpp"
#include "common.hpp"

class Plotter;


class Plotter : public Component{
    public:
        Plotter(SDL_Rect* _renderArea, SDL_Renderer* _renderer, PlotterConfig config);
        void updateRange(dpair* new_range);
        void feedEvent(SDL_Event* e) override;
    private:
        sample_generator _generator;
        dpair* _range;
        std::vector<dpair> _data;
        double _min_y, _max_y;
        double _x_scale, _y_scale;
        color_theme* _theme;
        bool _is_mouse_over;
        int _mouse_x, _mouse_y;
        SDL_Keycode _key_pressed;
        spair* _units;
        decltype(std::chrono::system_clock::now()) _last_key_poll;

        double scaleX(double x);
        double scaleY(double y);
        void componentRender() override;
        void zoom(double ratio);
        void shift(double ratio);
};

#endif
