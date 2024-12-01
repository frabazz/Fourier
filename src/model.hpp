#include "utils/observer.hpp"
#include "audio/wave.hpp"

using namespace Wave;

#ifndef F_MODEL
#define F_MODEL

class Model {
public:  
  WaveFile* wav;

  Model(WaveFile* wav);
};

#endif
