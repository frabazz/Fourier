#include <iostream>
#include "Component.hpp"

#ifndef F_BOX
#define F_BOX

class Box : public Component {
private:
  SDL_Color _on_color;
  SDL_Color _off_color;
  bool focused;
  
  void componentRender() override {
    setColor(focused ? _on_color : _off_color);
    SDL_Rect rect = {0, 0, _renderArea.w, _renderArea.h};
    fillRect(&rect);
  }

  void feedEvent(SDL_Event *ev) override {
    if (ev->type == SDL_MOUSEMOTION) {
      
      int x = ev->motion.x;
      int y = ev->motion.y;
      
      if (x < _renderArea.x || x > _renderArea.x + _renderArea.w ||
          y < _renderArea.y || y > _renderArea.y + _renderArea.h)
        focused = false;
      else
	focused = true;
      //std::cout << focused << std::endl;
    }
  }
  
public:
  Box(SDL_Rect renderArea , SDL_Color on_color,
      SDL_Color off_color)
      : Component(renderArea) {
    focused = false;
    _on_color = on_color;
    _off_color = off_color;
  }

};

  
#endif
