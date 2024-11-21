#include <SDL_events.h>
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
#define WTOP_RATIO 0.5

Plotter::Plotter(SDL_Rect renderArea, dpair range) : Component(renderArea) {

  _range = range;
  _max_y = 1.25;
  _min_y = -1.25;

  _data = std::vector<dpair>();
  _x_scale = std::abs(_range.second - _range.first);
  _y_scale  = std::abs(_max_y - _min_y);
  _npoints = renderArea.w * WTOP_RATIO;
  
  
}

void Plotter::calcData() {
  if (_range.first < 0) {
    _range.second += std::abs(_range.first);
    _range.first = 0;
    if (_range.second > _model->wav->sampleSize)
      _range.second = _model->wav->sampleSize;
  }

  if (_range.second > _model->wav->sampleSize) {
    _range.first -= (_range.second - _model->wav->sampleSize);
    _range.second = _model->wav->sampleSize;
    if (_range.first < 0)
      _range.first = 0;
  }

  double delta =
      (_range.second - _range.first) / (double)(_npoints);

  _model->wav->seekStart();
  _model->wav->seek(_range.first);

  for (int i = 0; i < _npoints - 1; ++i) {
    double sample = 0.0;
    _model->wav->readSample(&sample);
    // std::cout << "read sample index " << params.range->first + (i+1) * delta
    // << " "; std::cout << "position : " << _wav_file->tell() << std::endl;
    //  std::cout << " of value " << sample << std::endl ;
    int cast_delta = i * delta;
    _model->wav->seek((int)delta - 1);
    //_wav_file->seek((int)delta * (-1));
    _data.push_back({(int)_range.first + cast_delta, sample});
  }

  _model->wav->seekStart(); // leave it as we got it!

  _min_y = -1.25;
  _max_y = 1.25;
  std::cout << "generated v of size: " << _data.size() << std::endl;
}
/*
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
*/
double Plotter::scaleX(double x) {
  // TODO, add logarithmic scale
  return ((x - _range.first) / (_x_scale) * (_renderArea.w - AXIS_WIDTH)) +
         AXIS_WIDTH;
}

double Plotter::scaleY(double y) {
  // TODO, add logarithmic scale
  return (((1 - (y - _min_y) / (_y_scale)) * (_renderArea.h - AXIS_WIDTH)));
}

inline std::string doubleToString(double x, int precision) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << x;
  return stream.str();
}

void Plotter::componentRender() {
  // draw axis
  if (_data.empty()) {
    
    calcData();
  }
  SDL_Color c = {0, 0, 255, 255};
  setColor(c);

  SDL_Rect x_axis = {0, _renderArea.h - AXIS_WIDTH, _renderArea.w, AXIS_WIDTH};
  SDL_Rect y_axis = {0, 0, AXIS_WIDTH, _renderArea.h - AXIS_WIDTH};

  fillRect(&x_axis);
  fillRect(&y_axis);
  // draw function
  setColor(c);

  for (auto it = _data.begin(); it < _data.end() - 1; ++it) {
    //std::cout << "original x : " << it->first << " scaled x : " <<
    // scaleX(it->first) << std::endl;
    //std::cout << it->first << " " << it->second << std::endl;
    drawLineAA(scaleX(it->first), scaleY(it->second), scaleX((it + 1)->first),
               scaleY((it + 1)->second), {0, 0, 255, 255});
  }
}

void Plotter::feedEvent(SDL_Event *e) {}

