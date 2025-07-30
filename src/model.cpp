#include "model.hpp"
#include "audio/wave.hpp"

using namespace Wave;

Model::Model(WaveFile* wav){
  this->wav = wav;
}
