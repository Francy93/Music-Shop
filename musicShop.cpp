//#include "components.hpp"
#include "operations.cpp"
//#include "components.cpp"

//#include <iostream>
/* #include <string>
#include <memory>
#include <vector> */

using namespace std;


int main(){
    bool exit = false;
    cout << "Welcome to the Music-Shop Software" << endl;

    while(!exit){
        exit = userFirst(exit);
        if(!exit){ exit = menuSecond(exit); }
    }

    cout << "Before leaving, do you wanna save? Enter \"yes\" or \"no\"" << endl;
    string saving; cin >> saving;
    while(true){
        if (saving == "yes"){ Util util;  util.updater();  break; }
        else if(saving == "no"){ break; }
        else { cout << "Choice not contemplated" << endl; }
    }

    cout << "Successfully exited!" << endl;
    return 0;
}