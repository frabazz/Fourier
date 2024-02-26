#include <iostream>
#ifndef FCOMPLEX_H
#define FCOMPLEX_H

namespace CustomComplex {

    class Complex{
        public:
            Complex conjugate();

            Complex operator+(Complex c){
                return Complex::fromCoord(getReal() + c.getReal(), _img + c.getImg());
            }

            Complex operator-(Complex c){
                return Complex::fromCoord(getReal() + c.getReal(), _img + c.getImg());
            }

            Complex operator*(Complex c){
                return Complex::fromPhase(getReal() * c.getReal(), getPhase() + c.getPhase());
            }

            double getPhase();
            double getMagnitude();
            double getReal();
            double getImg();

            static Complex fromPhase(double magnitude, double phase);
            static Complex fromCoord(double real, double img);
            friend std::ostream& operator<<(std::ostream& os, Complex& c)
            {
                os << "(" << c.getReal() << ", " << c.getImg() << "j)";
                return os;
            }


        private:
            Complex();

            void _setPhase(double phase);
            void _setMagnitude(double magnitude);
            void _setReal(double real);
            void _setImg(double img);

            void _switchToPhase();
            void _switchToCoord();

            double _real, _img, _magnitude, _phase;
            bool _isPhaseDef;
            bool _isCoordDef;
    };


}

#endif
