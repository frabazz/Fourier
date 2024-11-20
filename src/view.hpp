#include "utils/observer.hpp"
#include "model.hpp"
#include <SDL2/SDL.h>

#ifndef F_VIEW
#define F_VIEW

class View : public IEmitter<SDL_Event*> {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Model* model;
public:
  View(Model* model);
  void render();
  void quit();
};

#endif
