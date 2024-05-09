#ifndef ASYNC_COMPONENT_H
#define ASYNC_COMPONENT_H

#include <thread>
#include <mutex>

#include "Component.hpp"
#include "common.hpp"
#include <SDL2/SDL.h>

class AsyncPlotter : public Component{
  public:
     AsyncPlotter(SDL_Rect* _renderArea, SDL_Renderer* _renderer, AsyncPlotterConfig config);
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
        spair* _units;

        double scaleX(double x);
        double scaleY(double y);
        void componentRender() override;
};


#endif
