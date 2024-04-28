#include <cmath>
#include <iostream>
using namespace std;

double function(double x){
    return cos(x);
}

int main(int argc, char *argv[]) {
    double a = 0, b = 3.14/2.0, x;
    double delta = 0.002;
    double integral = 0.0;
    for(x = a+delta; x < b; x += delta)
        integral += function(x)*delta;

    integral += (b-x)*function(b);

    cout << "result : " << integral << endl;
    return 0;
}
