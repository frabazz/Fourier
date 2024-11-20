#include <SDL2/SDL.h>
#include "controller.hpp"

Controller::Controller(View* view, Model* model){
  this->view = view;
  this->model = model;
  view->addListener(this);
  loop = true;
}

void Controller::update(SDL_Event* ev) {
  
  if(ev->type == SDL_QUIT){
    loop = false;
  }
  // controller logic
}

void Controller::run(){
  while(loop)
    view->render();
  view->quit();
}
