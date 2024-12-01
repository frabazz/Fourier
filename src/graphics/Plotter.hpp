#ifndef PLOTTER_COMPONENT_H
#define PLOTTER_COMPONENT_H

#include <SDL2/SDL.h>
#include <vector>

#include "../common.hpp"
#include "Component.hpp"
#include "Text.hpp"

struct mark {
  double time;
  Text* text;
};

class Plotter : public Component {
public:
  const std::vector<int> mark_gaps = {
    1,
    5,
    10,
    25,
    50,
    100,
    250,
    500,
    1000, // 1 second
    2500,
    5000,
    10000,
    15000,
    30000, // 30 second
    60000 // 1 minute
  };
  
  Plotter(SDL_Rect renderArea, dpair range);
  void updateRange(dpair *new_range);
  void feedEvent(SDL_Event *e) override;
  ~Plotter();
  
private:
  bool _first_render;
  dpair _range;
  std::vector<dpair> _data;
  std::vector<dpair> _data_coordinates;
  std::vector<mark> _marks;
  double _min_y, _max_y;
  double _x_scale, _y_scale;
  int _npoints;
  SDL_Rect _frame;
  
  void calcData();
  double scaleX(int i);
  double scaleY(double y);
  void componentRender() override;
  void zoom(double ratio);
  void shift(double ratio);
};

#endif
