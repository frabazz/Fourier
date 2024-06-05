#ifndef PLOTTER_COMPONENT_H
#define PLOTTER_COMPONENT_H

#include <SDL2/SDL.h>

#include "PlotterWorker.hpp"
#include "Component.hpp"
#include "common.hpp"
#include "Event.hpp"

 struct PlotterConfig {
    PlotterWorker* worker;
    dpair* range;
    spair* units;
    color_theme* theme;
};

struct AsyncPlotterConfig {
    AsyncPlotterWorker* worker;
    dpair* range;
    spair* units;
    color_theme* theme;
};

class Plotter : public Component{
    public:
        Plotter(SDL_Rect* _renderArea, SDL_Renderer* _renderer, PlotterConfig config);
        void updateRange(dpair* new_range);
        void feedEvent(SDL_Event* e) override;
    private:
        PlotterWorker* _worker;
        dpair* _range;
        std::vector<dpair> _data;
        double _min_y, _max_y;
        double _x_scale, _y_scale;
        color_theme* _theme;
        bool _is_mouse_over;
        int _mouse_x, _mouse_y;
        SDL_Keycode _key_pressed;
        spair* _units;

        double scaleX(double x);
        double scaleY(double y);
        void componentRender() override;
        void zoom(double ratio);
        void shift(double ratio);
};

#endif
