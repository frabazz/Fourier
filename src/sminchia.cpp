#include <iostream>

using std::string;

int main(int argc, char* argv[]){
    string str = "gianni";
    for(auto &c : str)
        c++;
    std::cout << str << std::endl;
    return 0;
}
