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
#define WTOP_RATIO 0.8
/*
Plotter::Plotter(SDL_Rect renderArea, SDL_Renderer *renderer, dpair range)
    : Component(renderArea, renderer) {

  _range = range;
  _max_y = 0;
  _min_y = 0;

  _data = std::vector<dpair>();
  _x_scale = INT_MAX;
  _y_scale = INT_MAX;
}

void Plotter::calcData() {
  if (_range.first < 0) {
    _range.second += std::abs(_range.first);
    _range.first = 0;
    if (_range.second > _wav_file->sampleSize)
      _range->second = _wav_fileP->sampleSize;
  }

  if (params.range->second > _wav_file->sampleSize) {
    params.range->first -= (params.range->second - _wav_file->sampleSize);
    params.range->second = _wav_file->sampleSize;
    if (params.range->first < 0)
      params.range->first = 0;
  }

  double delta =
      (params.range->second - params.range->first) / (double)(params.npoints);

  _wav_file->seekStart();
  _wav_file->seek(params.range->first);

  for (int i = 0; i < params.npoints - 1; ++i) {
    double sample = 0.0;
    _wav_file->readSample(&sample);
    // std::cout << "read sample index " << params.range->first + (i+1) * delta
    // << " "; std::cout << "position : " << _wav_file->tell() << std::endl;
    //  std::cout << " of value " << sample << std::endl ;
    int cast_delta = i * delta;
    _wav_file->seek((int)delta - 1);
    //_wav_file->seek((int)delta * (-1));
    params.data->push_back({(int)params.range->first + cast_delta, sample});
  }

  _wav_file->seekStart(); // leave it as we got it!

  *params.min_y = -1.25;
  *params.max_y = 1.25;
  std::cout << "generated v of size: " << params.data->size() << std::endl;
}
*//*
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
    sendRecalcEvent();
    return;
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
    // std::cout << "original x : " << it->first << " scaled x : " <<
    // scaleX(it->first) << std::endl;
    drawLineAA(scaleX(it->first), scaleY(it->second), scaleX((it + 1)->first),
               scaleY((it + 1)->second), {0, 0, 255, 255});
  }
}

void Plotter::feedEvent(SDL_Event *e) {}
*/
