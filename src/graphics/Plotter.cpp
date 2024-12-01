#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "../utils/TimeStamp.hpp"
#include "Plotter.hpp"
#include "colors.hpp"

#define AXIS_WIDTH 2
#define CROSS_SIZE 10
#define WTOP_RATIO 0.8  // renderArea width to number of points ratio
#define HTOF_RATIO 0.85 // renderArea height to frame heigth ratio
#define NMARKS 6        // number of marks
#define MARK_DIGITS 4
#define MARK_FONT_SIZE 14

std::string toLimitedString(float value) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(1) << value;
  std::string result = oss.str();
  result.erase(result.find_last_not_of('0') + 1); // Rimuove zeri finali
  if (result.back() == '.')
    result.pop_back(); // Rimuove il punto finale
  return result;
}

Plotter::Plotter(SDL_Rect renderArea, dpair range) : Component(renderArea) {
  _first_render = true;
  _range = range;
  _max_y = 1.1;
  _min_y = -1.1;

  int frame_height = _renderArea.h * HTOF_RATIO;
  _npoints = renderArea.w * WTOP_RATIO;
  _frame = {_renderArea.x, _renderArea.y, _renderArea.w, frame_height};
  _data = std::vector<dpair>(_npoints);
  _data_coordinates = std::vector<dpair>(_npoints);
  _marks = std::vector<mark>(NMARKS);
  _x_scale = std::abs(_range.second - _range.first);
  _y_scale = std::abs(_max_y - _min_y);

  Text t = Text({0, 0}, "42", MARK_FONT_SIZE, {0, 0, 0});
  int posy = _renderArea.y + _frame.h + (_renderArea.h * (1 - HTOF_RATIO) / 2) -
             ((float)t.getRenderArea().h) / 2;

  for (int i = 0; i < NMARKS; ++i) {
    _marks[i] = {new TimeStamp(0.0),
                 new Text({0, posy}, "42", MARK_FONT_SIZE, Color::WHITE)};
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

  int range_samples = _range.second - _range.first + 1;
  int delta = range_samples / _npoints;
  _model->wav->seekStart();
  _model->wav->seek(_range.first);
  int mark_index = 0;
  std::cout << "calculating data" << std::endl;

  int curr_sample = _range.first;
  double sample = 0.0;

  for (int i = 0; i < _npoints; ++i) {
    _model->wav->readSample(&sample);
    _model->wav->seek(delta);
    _data[i] = {curr_sample, sample};
    _data_coordinates[i] = {
        ((double)(i) / (double)_npoints) * (_frame.w - AXIS_WIDTH) + AXIS_WIDTH,
        (((1 - (_data[i].second - _min_y) / (_y_scale)) *
          (_frame.h - AXIS_WIDTH)))};
    curr_sample += delta;
  }

  _data_coordinates[_npoints - 1].first = _frame.w - 2 * AXIS_WIDTH;
  calcMarks();
  _model->wav->seekStart(); // leave it as we got it!

  _min_y = -1.1;
  _max_y = 1.1;
  std::cout << "generated v of size: " << _data.size() << std::endl;
}

void Plotter::calcMarks() {

  int sampleRate = 44100; // TODO: get actual sample rate
  _marks[0].time->fromSeconds((double)_data[0].first / (double)sampleRate);
  _marks[NMARKS - 1].time->fromSeconds((double)_data[_npoints - 1].first /
                                       (double)sampleRate);
  TimeStamp::string_format format = _marks[NMARKS - 1].time->getDefaultFormat();
  double diff =
      (_marks[NMARKS - 1].time->toSeconds() - _marks[0].time->toSeconds()) *
      1000;
  int gap = 0;
  double n = 1;
  for (auto it = mark_gaps.end() - 1; it >= mark_gaps.begin(); --it) {
    n = diff / *it;
    if (n > NMARKS - 2) {
      gap = *it;
      break;
    }
  }

  if (n == 0) {
    std::cout << "Plotter render error, no gaps found" << std::endl;
    return;
  }

  double delta = (double)n / (double)(NMARKS - 2);
  // no * (gap+1) because of the 0 edge case
  int start_t = (((int)(_marks[0].time->toSeconds() * 1000) / gap) * gap) + gap;
  int end_t =
      (((int)(_marks[NMARKS - 1].time->toSeconds() * 1000) / gap) * gap);
  int curr_t = start_t;
  double j = 0;

  for (int i = 1; i < NMARKS - 1; ++i) {
    _marks[i].time->fromSeconds((double)curr_t / 1000.0);
    j += delta;
    /*
      sometimes curr_t == old(curr_t) and some marks could be in the same
      position and be rendered as one. Its not a problem and the graphic result
      is better (it's not a bug, it's a feature!)
     */
    curr_t = std::round(j) * gap;
  }

  for (int i = 0; i < NMARKS; ++i) {
    std::cout << _marks[i].time->toString(format) << " ";
    double p =
        (_marks[i].time->toSeconds() - _marks[0].time->toSeconds()) /
        (_marks[NMARKS - 1].time->toSeconds() - _marks[0].time->toSeconds());

    /*
    Text should be set before position calculation because text length affects
    component width
   */
    _marks[i].text->setText(_marks[i].time->toString(format));
    _marks[i].text->_renderArea.x = _frame.x + p * (double)(_frame.w) -
                                    (double)_marks[i].text->_renderArea.w / 2.0;
  }
  std::cout << std::endl;
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
double Plotter::scaleX(int i) {
  return ((double)(i) / (double)_npoints) * (_frame.w) + AXIS_WIDTH;
  // TODO, add logarithmic scale
  /*return ((x - _range.first + 1) / (_x_scale) * _frame.w) +
    AXIS_WIDTH;*/
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

  setColor(Color::BLUE);

  SDL_Rect down = {0, _frame.h - AXIS_WIDTH, _frame.w, AXIS_WIDTH};
  SDL_Rect left = {0, 0, AXIS_WIDTH, _frame.h - AXIS_WIDTH};
  SDL_Rect up = {0, 0, _frame.w, AXIS_WIDTH};
  SDL_Rect right = {_frame.w - AXIS_WIDTH, 0, AXIS_WIDTH, _frame.h};

  fillRect(&down);
  fillRect(&left);
  fillRect(&up);
  fillRect(&right);
  // draw function
  setColor(Color::ORANGE);
  for (auto it = _data_coordinates.begin(); it < _data_coordinates.end() - 1;
       ++it) {
    // std::cout << "original x : " << it->first << " scaled x : " <<
    //  scaleX(it->first) << std::endl;
    // std::cout << it->first << " " << it->second << std::endl;
    drawLineAA(it->first, it->second, (it + 1)->first, (it + 1)->second,
               Color::ORANGE);
  }

  for (auto m : _marks)
    m.text->render();
}

void Plotter::feedEvent(SDL_Event *e) {}

Plotter::~Plotter() {
  for (auto m : _marks)
    delete m.text;
}
