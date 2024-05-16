#include "Event.hpp"

#include <iostream>
#include <SDL2/SDL.h>


using namespace events;

Event::Event(SDL_Event* e){
  sdl_event = e;
  _is_sdl = true;
  _is_custom = false;
}

Event::Event(){
  _is_sdl = false;
  _is_custom = false;
  sdl_event = new SDL_Event;
}

bool Event::isSDL(){
  return _is_sdl;
}

bool Event::isCustom(){
  return _is_custom;
}

Event::~Event(){
  if(sdl_event != NULL)
    delete sdl_event;
}

void Event::pollEvent(Event *e){

  if(SDL_PollEvent(e->sdl_event) > 0){
    e->_is_custom = false;
    e->_is_sdl = true;
    //std::cout << "getting sdl event" << std::endl;
  }

  else if(false){
    // handle custom logic
  }

  else{
    e->_is_custom = false;
    e->_is_sdl = false;
  }
}
