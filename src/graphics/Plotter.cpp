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

#define AXIS_WIDTH 2
#define CROSS_SIZE 10
#define WTOP_RATIO 0.9 // renderArea width to number of points ratio
#define HTOF_RATIO 0.85 // renderArea height to frame heigth ratio
#define NMARKS 6       // number of marks
#define MARK_DIGITS 4
#define MARK_FONT_SIZE 15

std::string toLimitedString(float value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << value;
    std::string result = oss.str();
    result.erase(result.find_last_not_of('0') + 1); // Rimuove zeri finali
    if (result.back() == '.') result.pop_back();    // Rimuove il punto finale
    return result;
}

Plotter::Plotter(SDL_Rect renderArea, dpair range) : Component(renderArea) {
  _first_render = true;
  _range = range;
  _max_y = 1.25;
  _min_y = -1.25;

  int frame_height = _renderArea.h * HTOF_RATIO;
  _npoints = renderArea.w * WTOP_RATIO;
  _frame = {_renderArea.x, _renderArea.y, _renderArea.w, frame_height};
  _data = std::vector<dpair>(_npoints - 1);
  _data_coordinates = std::vector<dpair>(_npoints - 1);
  _marks = std::vector<mark>(NMARKS);
  _x_scale = std::abs(_range.second - _range.first);
  _y_scale = std::abs(_max_y - _min_y);

  int posx, posy;
  Text t = Text({0, 0}, "1234", MARK_FONT_SIZE, {0, 0, 0});
  posy = _renderArea.y + _frame.h + (_renderArea.h * (1 - HTOF_RATIO) / 2) -
         ((float)t.getRenderArea().h) / 2;

  for (int i = 0; i < NMARKS; ++i) {
    posx = AXIS_WIDTH * 2 + _renderArea.x + i * _renderArea.w / NMARKS;
    Text *t = new Text({posx, posy}, "0.5", MARK_FONT_SIZE, {0, 0, 255, 255});
    _marks[i] = {0, t};
  }
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

  double delta = (_range.second - _range.first) / (double)(_npoints);

  _model->wav->seekStart();
  _model->wav->seek(_range.first);
  int mark_index = 0;
  for (int i = 0; i < _npoints - 1; ++i) {
    double sample = 0.0;
    _model->wav->readSample(&sample);
    // std::cout << "read sample index " << params.range->first + (i+1) * delta
    // << " "; std::cout << "position : " << _wav_file->tell() << std::endl;
    //  std::cout << " of value " << sample << std::endl ;
    int cast_delta = i * delta;
    _model->wav->seek((int)delta - 1);
    //_wav_file->seek((int)delta * (-1));
    
    //TODO: remove array access?
    _data[i] = {(int)_range.first + cast_delta, sample};
    _data_coordinates[i] = {scaleX(_data[i].first), scaleY(_data[i].second)};
    if(mark_index < NMARKS){
      SDL_Rect text_area = _marks[mark_index].text->getRenderArea();
      if(_data_coordinates[i].first > text_area.x + text_area.w/2.0 - _renderArea.w){
	_marks[mark_index].time = _data[i].first / 44000.0; // TODO: get actual sample rate
	_marks[mark_index].text->setText(toLimitedString(_marks[mark_index].time) + "s");
	mark_index++;
      }
    }
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
  return ((x - _range.first) / (_x_scale) * (_frame.w - AXIS_WIDTH)) +
         AXIS_WIDTH;
}

double Plotter::scaleY(double y) {
  // TODO, add logarithmic scale
  return (((1 - (y - _min_y) / (_y_scale)) * (_frame.h - AXIS_WIDTH)));
}

inline std::string doubleToString(double x, int precision) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << x;
  return stream.str();
}

void Plotter::componentRender() {
  // draw axis
  if (_first_render) {
    calcData();
    _first_render = false;
  }
  SDL_Color c = {0, 0, 255, 255};
  setColor(c);

  SDL_Rect down = {0, _frame.h - AXIS_WIDTH, _frame.w, AXIS_WIDTH};
  SDL_Rect left = {0, 0, AXIS_WIDTH, _frame.h - AXIS_WIDTH};
  SDL_Rect up = {0, 0, _frame.w, AXIS_WIDTH};
  SDL_Rect right = {_frame.w - AXIS_WIDTH, 0, AXIS_WIDTH, _frame.h};

  fillRect(&down);
  fillRect(&left);
  fillRect(&up);
  fillRect(&right);
  // draw function
  setColor(c);

  for (auto it = _data_coordinates.begin(); it < _data_coordinates.end() - 1;
       ++it) {
    // std::cout << "original x : " << it->first << " scaled x : " <<
    //  scaleX(it->first) << std::endl;
    // std::cout << it->first << " " << it->second << std::endl;
    drawLineAA(it->first, it->second, (it + 1)->first, (it + 1)->second,
               {0, 0, 255, 255});
  }

  for(auto m : _marks)
    m.text->render();
}

void Plotter::feedEvent(SDL_Event *e) {}

Plotter::~Plotter() {
  for(auto m : _marks)
    delete m.text;
}
