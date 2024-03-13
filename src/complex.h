#include <iomanip>
#include <iostream>
#ifndef FCOMPLEX_H
#define FCOMPLEX_H

typedef long double ld;

namespace CustomComplex {

    class Complex{
        public:
            Complex conjugate();

            Complex operator+(Complex c){
                return Complex::fromCoord(getReal() + c.getReal(), getImg() + c.getImg());
            }

            Complex operator-(Complex c){
                return Complex::fromCoord(getReal() + c.getReal(), getImg() + c.getImg());
            }

            Complex operator*(Complex c){
                return Complex::fromPhase(getMagnitude() * c.getMagnitude(), getPhase() + c.getPhase());
            }

            ld getPhase();
            ld getMagnitude();
            ld getReal();
            ld getImg();

            static Complex fromPhase(ld magnitude, ld phase);
            static Complex fromCoord(ld real, ld img);
            friend std::ostream& operator<<(std::ostream& os, Complex& c)
            {
                os << std::setprecision(3) << "(" << c.getReal() << ", " << c.getImg() << "j)";
                return os;
            }


        private:
            Complex();

            void _setPhase(ld phase);
            void _setMagnitude(ld magnitude);
            void _setReal(ld real);
            void _setImg(ld img);

            void _switchToPhase();
            void _switchToCoord();

            ld _real, _img, _magnitude, _phase;
            bool _isPhaseDef;
            bool _isCoordDef;
    };


}

#endif
