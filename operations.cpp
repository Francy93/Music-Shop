#include "components.hpp"
#include "components.cpp"

#include <string>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;


vector<shared_ptr<User>> usrVec; // access Derived via shared_ptr to Base
auto user = make_shared<User>();
auto sudo = make_shared<SuperUser>();

bool userFirst(bool exit){
    cout << "Welcome to the Music-Shop Software" << endl;    
    //selecting a user
    cout << "\r\nPlease select a user.\r\nEnter here \"employee\" or \"manager\" to access." << endl;
    cout << "Alternatively enter \"exit\" to close the program.\r\n" << endl;
    string choice; cin >> choice;

    if (choice == "exit"){
        exit = true;
    }else if(choice == "manager"){
        usrVec.push_back(sudo);
    }else if(choice == "employee"){
        usrVec.push_back(user);
    }else{ 
        cout << "Choice not contemplated!\r\nTry again!" << endl;
        userFirst(exit);
    }
    return exit;
}
    
bool menuSecond(bool exit){
    cout << "\r\nType one of the options below." << endl;
    cout << "Alternatively enter \"exit\" to close the program.\r\n" << endl;
    cout << usrVec.front()->text() << endl;
    string choice; cin >> choice;
    
    if(choice == "exit"){
        exit = true;
    }else if(choice == "Sell"   || choice == "Restock"||
                choice == "NewItem"|| choice == "Update" || choice == "Report"){
        exit = usrVec.front()->selection(choice);
    }else{ 
        cout << "Choice not contemplated!\r\nTry again!" << endl;
        menuSecond(exit);
    }
    return exit;
}