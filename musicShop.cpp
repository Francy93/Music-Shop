//#include "components.hpp"
#include "operations.cpp"
//#include "components.cpp"

#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;


int main(){
    bool exit = false;

    while(!exit){
        exit = userFirst(exit);
        if(!exit){ exit = menuSecond(exit); }
    }

    cout << "Successfully exited!" << endl;
    return 0;
}