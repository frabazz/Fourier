#ifndef PLOTTER_COMPONENT_H
#define PLOTTER_COMPONENT_H

#include <SDL2/SDL.h>
#include <vector>

#include "Component.hpp"
#include "../common.hpp"



class Plotter : public Component {
public:
  Plotter(SDL_Rect renderArea, dpair range);
  void updateRange(dpair *new_range);
  void feedEvent(SDL_Event *e) override;

private:
  dpair _range;
  std::vector<dpair> _data;
  double _min_y, _max_y;
  double _x_scale, _y_scale;
  int _npoints;
  
  void calcData();
  double scaleX(double x);
  double scaleY(double y);
  void   componentRender() override;
  void   zoom(double ratio);
  void   shift(double ratio);
};

#endif
