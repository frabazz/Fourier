#ifndef GRAPHIC_COMPONENT_H
#define GRAPHIC_COMPONENT_H

#define F_BOUNDARIES 0 // plot renderArea boundaries for debug

#include "../utils/observer.hpp"
#include "../model.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>

#include "Event.hpp"

class Component : public IListener<SDL_Event *> {
public:
  SDL_Rect _renderArea;
  static Model* _model;
  static SDL_Renderer *_renderer;

  SDL_Rect getRenderArea();
  
  Component(SDL_Rect renderArea);
  void render();
  virtual ~Component() = default;
private:
  void update(SDL_Event* ev) override;
protected:
  SDL_Color _draw_color;
  TTF_Font *_default_font;

  // rendering primitives
  void fillRect(SDL_Rect *rect);
  void drawRect(SDL_Rect *rect);
  void drawLine(float x1, float y1, float x2, float y2);
  void drawPoint(float x, float y);
  void drawLineAA(float x1, float y1, float x2, float y2, SDL_Color color);
  void setColor(SDL_Color c);
  void drawToolTip(std::string text, SDL_Rect *area, SDL_Color bgcolor);

  // implemented specifically by components
  virtual void componentRender() = 0;
  virtual void feedEvent(SDL_Event *e) = 0;

  
};
#endif
