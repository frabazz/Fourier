#ifndef CUSTOM_EVENTZ_H
#define CUSTOM_EVENTZ_H

#include <SDL2/SDL.h>

namespace events{

  class Event{
    public:
      Event();
      Event(SDL_Event* e);
      bool isSDL();
      bool isCustom();

      ~Event();

      SDL_Event* sdl_event;
      static void pollEvent(events::Event*);
    private:
      bool _is_sdl;
      bool _is_custom;
    };

}

#endif
