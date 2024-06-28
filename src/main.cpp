#include "renderHandler.hpp"
#include "audio/workers.hpp"
#include "audio/FileVector.hpp"

#define WIDTH 1200
#define HEIGHT 500
#define AUDIO_FILE "../assets/sin.wav"

int main(int argc, char *argv[]) {
  
  RenderHandler handler = RenderHandler(WIDTH, HEIGHT);
  if(!handler.initSDL() || !handler.initWav(AUDIO_FILE) || !handler.initComponents())
    return -1;

  bool quit = false;
  while(!quit){
    handler.renderLoop(&quit);
  }
  
  return 0;
}
