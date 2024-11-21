#include <iostream>
#include "controller.hpp"
#include "model.hpp"
#include "view.hpp"
#include "audio/wave.hpp"

int main(int argc, char *argv[]) {
  
  if(argc < 2){
    std::cout << "No wav file argument provided" << std::endl;
    return -1;
  }

  Wave::WaveFile wav = Wave::WaveFile(argv[1]);
  if(!wav.open()){
    std::cout << "error opening wav file" << std::endl;
    return -1;
  }
  
  Model m = Model(&wav);
  View v = View(&m);
  Controller c = Controller(&v, &m);
  c.run();
  return 0;
}
