#include "utils/observer.hpp"
#include "graphics/Component.hpp"
#include "model.hpp"
#include <vector>
#include <SDL2/SDL.h>


#ifndef F_VIEW
#define F_VIEW

class View : public IEmitter<SDL_Event*> {
private:
  std::vector<Component*> components;
  SDL_Window* window;
  SDL_Renderer* renderer;
  Model* model;
public:
  View(Model* model);
  void render();
  void quit();
};

#endif
