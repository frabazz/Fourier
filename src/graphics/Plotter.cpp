/*#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>

#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Event.hpp"
#include "Plotter.hpp"

#define AXIS_WIDTH 3
#define CROSS_SIZE 10
#define WTOP_RATIO 0.8

Plotter::Plotter(SDL_Rect *renderArea, SDL_Renderer *renderer, dpair *range,    
                 spair *units)
    : Component(renderArea, renderer) {

  _units = units;

  _is_mouse_over = false;
  _mouse_x = 0;
  _mouse_y = 0;
  _key_pressed = SDLK_CLEAR;
  _range = range;
  _max_y = 0;
  _min_y = 0;

  _data = std::vector<dpair>();
  _x_scale = INT_MAX;
  _y_scale = INT_MAX;
}

void Plotter::sendRecalcEvent() {

  plotter_recalc_ev *recalc_ev = new plotter_recalc_ev;
  *recalc_ev = {&_data, &_min_y, &_max_y, _range,
                (int)(WTOP_RATIO * _renderArea->w)};

  SDL_Event ev;
  ev.type = SDL_USEREVENT;
  ev.user.code = PLOTTER_RECALC;
  ev.user.data1 = (void *)recalc_ev;

  SDL_PushEvent(&ev);
}

void Plotter::zoom(double ratio) {

  double adj_ratio = (_range->second - _range->first) * ratio;

  if (_range->second - _range->first - 2 * adj_ratio <=
      _renderArea->w * WTOP_RATIO)
    return;

  _data.clear();

  *_range = {_range->first + adj_ratio, _range->second - adj_ratio};
  sendRecalcEvent();

  _x_scale = std::abs(_range->second - _range->first);
  _y_scale = std::abs(_max_y - _min_y);
}

void Plotter::shift(double ratio) {

  _data.clear();
  double adj_ratio = (_range->second - _range->first) * ratio;

  *_range = {_range->first + adj_ratio, _range->second + adj_ratio};
  sendRecalcEvent();

  _x_scale = std::abs(_range->second - _range->first);
  _y_scale = std::abs(_max_y - _min_y);
}

double Plotter::scaleX(double x) {
  // TODO, add logarithmic scale
  return ((x - _range->first) / (_x_scale) * (_renderArea->w - AXIS_WIDTH)) +
         AXIS_WIDTH;
}

double Plotter::scaleY(double y) {
  // TODO, add logarithmic scale
  return (((1 - (y - _min_y) / (_y_scale)) * (_renderArea->h - AXIS_WIDTH)));
}

inline std::string doubleToString(double x, int precision) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << x;
  return stream.str();
}

void Plotter::componentRender() {
  // draw axis
   if(_data.empty()) {
    sendRecalcEvent();
    return;
   }
  SDL_Color c = {0, 0, 255, 255};
  setColor(c);

  SDL_Rect x_axis = {0, _renderArea->h - AXIS_WIDTH, _renderArea->w,
                     AXIS_WIDTH};
  SDL_Rect y_axis = {0, 0, AXIS_WIDTH, _renderArea->h - AXIS_WIDTH};

  fillRect(&x_axis);
  fillRect(&y_axis);
  // draw function
  setColor(c);

  for (auto it = _data.begin(); it < _data.end() - 1; ++it) {
    // std::cout << "original x : " << it->first << " scaled x : " <<
    // scaleX(it->first) << std::endl;
    drawLineAA(scaleX(it->first), scaleY(it->second), scaleX((it + 1)->first),
	       scaleY((it + 1)->second), {0, 0, 255, 255});
  }

  // draw cross and tooltip
  if (_is_mouse_over) {
    SDL_RenderDrawLine(_renderer, _mouse_x, _mouse_y - CROSS_SIZE, _mouse_x,
                       _mouse_y + CROSS_SIZE);
    SDL_RenderDrawLine(_renderer, _mouse_x - CROSS_SIZE, _mouse_y,
                       _mouse_x + CROSS_SIZE, _mouse_y);
    SDL_Rect area = {_mouse_x + CROSS_SIZE, _mouse_y + CROSS_SIZE, 200, 20};

    double index_percentage =
        static_cast<double>(_mouse_x - _renderArea->x - AXIS_WIDTH) /
        static_cast<double>(_renderArea->w - AXIS_WIDTH);
    int index =
        std::floor(index_percentage * static_cast<double>(_data.size() - 1));
    std::string text =
        doubleToString(_data[index].first, 2) + " " + _units->first + ", " +
        doubleToString(_data[index].second, 2) + " " + _units->second;

    drawToolTip(text, &area, {0, 0, 255});
  }

  switch (_key_pressed) {
  case SDLK_RIGHT:
    shift(0.1);
    break;
  case SDLK_LEFT:
    shift(-0.1);
    break;
  case SDLK_PLUS:
    zoom(0.1);
    break;
  case SDLK_MINUS:
    zoom(-0.1);
    break;
  }

  _key_pressed = SDLK_CLEAR;
}

void Plotter::feedEvent(SDL_Event *e) {
  if (e->type == SDL_MOUSEMOTION) {
    _mouse_x = e->motion.x;
    _mouse_y = e->motion.y;

    if (_mouse_x > _renderArea->x + AXIS_WIDTH &&
        _mouse_x < _renderArea->x + _renderArea->w &&
        _mouse_y > _renderArea->y &&
        _mouse_y < _renderArea->y + _renderArea->h - AXIS_WIDTH)
      _is_mouse_over = true;
    else
      _is_mouse_over = false;
  } else if (e->type == SDL_KEYDOWN) {
    _key_pressed = e->key.keysym.sym;
  } else if (e->type == SDL_USEREVENT && e->user.code == PLOTTER_RECALC) {
    _x_scale = std::abs(_range->second - _range->first);
    _y_scale = std::abs(_max_y - _min_y);
  }
}
*/
