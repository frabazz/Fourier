#include "controller.hpp"
#include "model.hpp"
#include "view.hpp"
int main(int argc, char *argv[]) {
  /*
  RenderHandler handler = RenderHandler(WIDTH, HEIGHT);
  if(!handler.initSDL() || !handler.initWav(AUDIO_FILE) || !handler.initComponents())
    return -1;

  bool quit = false;
  while(!quit){
    handler.renderLoop(&quit);
  }
  
  return 0;
  */
  Model m = Model();
  View v = View(&m);
  Controller c = Controller(&v, &m);
  c.run();
}
