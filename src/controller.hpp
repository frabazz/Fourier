#include <SDL2/SDL.h>

#include "utils/observer.hpp"
#include "view.hpp"
#include "model.hpp"

#ifndef F_CONTROLLER
#define F_CONTROLLER

class Controller : IListener<SDL_Event*> {
private:
  Model* model = NULL;
  View* view = NULL;
  bool loop;

public:
  Controller(View* view, Model* model);
  void update(SDL_Event* ev) override;
  void run();
};

#endif
