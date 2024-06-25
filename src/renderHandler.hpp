#ifndef RENDER_HANDLER_H
#define RENDER_HANDLER_H

#include "./audio/wave.hpp"
#include "./graphics/Plotter.hpp"
#include <SDL2/SDL.h>
#include <string>



class RenderHandler{
private:
  SDL_Renderer* _renderer = NULL;
  SDL_Window* _window = NULL;
  Wave::WaveFile* _wav = NULL;
  Component::Plotter* _signalPlotter = NULL;
  int _width, _heigth;
  SDL_Event _event;
public:
  RenderHandler(int width, int heigth);
  bool initSDL();
  bool initWav(std::string filename);
  bool initComponents();
  void renderLoop(bool *quit);
  void freeSDL();
  ~RenderHandler();
};

#endif
