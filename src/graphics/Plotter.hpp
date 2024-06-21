#ifndef PLOTTER_COMPONENT_H
#define PLOTTER_COMPONENT_H

#include <SDL2/SDL.h>
#include <vector>

#include "Component.hpp"
#include "../common.hpp"


struct plotter_recalc_ev{
  std::vector<dpair> *data;
  double* min_y;
  double* max_y;
  dpair *range;
  int npoints;
};
    

class Plotter : public Component {
public:
  Plotter(SDL_Rect *renderArea, SDL_Renderer *renderer, dpair *range,
          spair *units);
  void updateRange(dpair *new_range);
  void feedEvent(SDL_Event *e) override;

private:
  dpair *_range;
  std::vector<dpair> _data;
  double _min_y, _max_y;
  double _x_scale, _y_scale;
  bool _is_mouse_over;
  int _mouse_x, _mouse_y;
  SDL_Keycode _key_pressed;
  spair *_units;

  void   sendRecalcEvent();
  double scaleX(double x);
  double scaleY(double y);
  void   componentRender() override;
  void   zoom(double ratio);
  void   shift(double ratio);
};

#endif
