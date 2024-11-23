#include <SDL2/SDL.h>
#include <iostream>
#include "Plotter.hpp"
#include "graphics/Box.hpp"
#include "graphics/Text.hpp"
#include <SDL_ttf.h>
#include "view.hpp"
#include <map>

View::View(Model *model) {
  this->model = model;
  
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    std::cout << "error init" << std::endl;
  window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 900, 700, 0);
  if (!window)
    std::cout << "failed to open window" << std::endl;
  renderer = SDL_CreateRenderer(window, -1, 0);

  if(TTF_Init() < 0)
    std::cout << "failed to initialize TTF" << std::endl;
  
  //static declarations
  Component::_model = model; 
  Component::_renderer = renderer; 
  Text::font_cache = new std::map<int, TTF_Font*>();
  
  //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  components = std::vector<Component*>();
  SDL_Rect renderArea = {0, 0, 50, 50};
  SDL_Color green = {0, 255, 0, 255}; // on color
  SDL_Color blue = {0, 0, 255, 255}; // off color
  //Box* b = new Box(renderArea, green, blue);
  Plotter* plotter = new Plotter({100, 100, 500, 200}, {0, model->wav->sampleSize});
  Text* text = new Text(renderArea, "Test", 40, blue);
  Text* text2 = new Text(renderArea, "Io sono PDOR, figlio di KMER", 40, blue);
  components = {text2, plotter};

  for(auto c : components)
    this->addListener(c);
}

void View::render(){
  SDL_Event ev;
  while(SDL_PollEvent(&ev) > 0)
    this->emit(&ev);
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  for(auto c : components)
    c->render();
  
  SDL_RenderPresent(renderer);
}

void View::quit(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  Text::freeFonts();
  TTF_Quit();
  for(auto c : components)
    delete c;
}
