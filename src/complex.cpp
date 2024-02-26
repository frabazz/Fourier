#include "complex.h"
#include <cmath>

using namespace CustomComplex;


Complex::Complex(){
    _isCoordDef = false;
    _isPhaseDef = false;
}


void Complex::_setPhase(double phase){ _phase = phase; }
void Complex::_setMagnitude(double magnitude){ _magnitude = magnitude; }
void Complex::_setReal(double real){ _real = real; }
void Complex::_setImg(double img){ _img = img; }

double Complex::getPhase(){
    _switchToPhase();
    return _phase;
}

double Complex::getMagnitude() {
    _switchToPhase();
    return _magnitude;
}

double Complex::getReal() {
    _switchToCoord();
    return _real;
}

double Complex::getImg()  {
    _switchToCoord();
    return _img;
}



void Complex::_switchToCoord(){
    if(_isCoordDef)
        return;
    if(!_isPhaseDef)
        throw "Complex must be phase defined to switch to coord";
    _setReal(_magnitude * std::cos(_phase));
    _setImg(_magnitude * std::sin(_phase));
}

void Complex::_switchToPhase(){
    if(_isPhaseDef)
        return;
    if(!_isCoordDef)
        throw "Complex must be coord defined to switch to phase";
    _setPhase(std::atan2(_img, _real));
    _setMagnitude(std::sqrt((_real * _real) + (_img * _img)));

}

Complex Complex::fromCoord(double real, double img){
    Complex c = Complex();
    c._real = real;
    c._img = img;
    c._isCoordDef = true;

    return c;
}

Complex Complex::fromPhase(double magnitude, double phase){
    Complex c = Complex();
    c._phase = phase;
    c._magnitude = magnitude;
    c._isPhaseDef = true;

    return c;
}
