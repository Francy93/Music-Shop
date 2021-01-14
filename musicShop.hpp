#ifndef _MUSICSHOP_H_
#define _MUSICSHOP_H_


#include <iostream>
#include <string>  //library for string variables
#include <ctime>   //library for data and time
#include <sstream> //library for intoToString converter
#include <vector> //library for intoToString converter

#include <fstream>  // file text scanner
#include <algorithm>// std::find
#include <cctype>   // remove white spaces

#include <regex>    // regular expressions

#include <memory>

using namespace std;
//declaring all the classes that I are going to use


//____________________________File util.cpp_____________________________

class Util {

    public:
        bool saved = true;
        //categories matrix
        vector<vector<string> > DVDs;
        vector<vector<string> > CDs;
        vector<vector<string> > Magazines;
        vector<vector<string> > Books;
        
        vector<vector<string> > SessionDB;
        vector<string> reportVec;

    private:
        string delimiter = " :: ";
        string fname = "DataBase.txt";

        //file reader
        vector<string> importer(std::string cat);

        //data exporter
        void exporter();

        //importing data from HardDisk
        vector<vector<string> > dbQuery(bool InOut);

    public:
        bool reportDisplay();

        string reporting(std::string id, int qty, std::string user);

        //the holly strings splitter *.*
        vector<string> split(std::string s, std::string delim);

    private:
        //fetching imported data, from sessionDB (ram) and splitting into categories
        vector<vector<string> > catSplit(std::string category);
        
    public:
        //constructor method to initialize DataBase vectors
        Util(){ 
            SessionDB = dbQuery(false); //selfrunnin dbQuery in output mode
            DVDs      = catSplit("D");
            CDs       = catSplit("C");
            Magazines = catSplit("M");
            Books     = catSplit("B");
        }

        void updater();
        string IntToString(int a);

        //current date generator
        string dateGen();
        vector<vector<string> > catSelector(std::string id);

        // Function to print the index of an element
        int getIndex(int cat, std::string k);
        vector<string> getById(std::string id);
        bool print(int cat);
};


//____________________________File components.cpp_____________________________

//Making the dataBase object/truct
Util util;

class Categories{

    private:
        string name = "";
        string date;
        string price = "";
        int amount  = -1;

    protected:
        string id;
        int catIndex;
        string idCalc(int cat);
        void dataToVec();
            
    public:
        void setName(std::string n);
        void setPrice(std::string p);
        void setAmount(int a);

        string getID();

        string getName();
        string getPrice();
        int getAmount();

        void propSetter();
        //constructor
        Categories(){
            date = util.dateGen();
        }
};

class DVD : public Categories {

    private:
        string cat = "D";
        int index = 0;
    public:
        DVD(std::string ID){ id = ID;  catIndex = index;  propSetter(); }
        DVD(){
            string n = idCalc(index);
            id = cat+"00"+n;
        }
};

class CD : public Categories {

     private:
        string cat = "C";
        int index = 1;
    public:
        CD(std::string ID){ id = ID;  catIndex = index;  propSetter(); }
        CD(){
            string n = idCalc(index);
            id = cat+"00"+n;
        }
};

class Magazine : public Categories {

    private:
        string cat = "M";
        int index = 2;
    public:
        Magazine(std::string ID){ id = ID;  catIndex = index;  propSetter(); }
        Magazine(){
            string n = idCalc(index);
            id = cat+"00"+n;
        }
};

class Book : public Categories {

    private:
        string cat = "B";
        int index = 3;
    public:
        Book(std::string ID){ id = ID;  catIndex = index;  propSetter(); }
        Book(){
            string n = idCalc(index);
            id = cat+"00"+n;
        }
};

class Logistic {
    private:
        //Util util;
        int chooseCat(bool IorO);
        bool amountEditing(std::string id, int num);

        vector<char> catChar = {'D', 'C', 'M', 'B'};

    public:
        string user; //this variable shows in the report which user operated

        bool update();
        bool restock(bool exit);
        bool newItem(bool exit);
        bool sale(bool exit);
        bool report();

};
/* 
struct User {
    
    protected:
        Logistic logistic;

    public:
        public:
        User(){
            logistic.user = "Employee";
        }
        virtual bool privileges(){ return false; }
        virtual string text(){ return "Sale,\r\nRestock,\r\n"; }
        
        virtual bool selection(std::string choice){
            bool exit = false;

            if(choice == "Sale"){
                exit =logistic.sale(exit);
            }else if (choice == "Restock"){
                exit =logistic.restock(exit);
            }else if (choice == "NewItem" || choice == "Update" || choice == "Report"){
                cout << "Access denied. User not allowed!\r\n" << endl;
            }else { cout << "Error user: wrong operation choice!\r\n" << endl; }

            return exit;
        }
};

struct SuperUser : User{
        
    public:
        SuperUser(){
            logistic.user = "Manager";
        }
        bool privileges() override { return true; }
        string text() override { 
            return "Sale,\r\nRestock,\r\nNewItem,\r\nUpdate,\r\nReport.\r\n";
        }
        
        bool selection(std::string choice) override {
            bool exit = false;

            if(choice == "Sale"){
                exit = logistic.sale(exit);
            }else if (choice == "Restock"){
                exit = logistic.restock(exit);
            }else if(choice == "NewItem"){
                exit = logistic.newItem(exit);
            }else if (choice == "Update"){
                exit = logistic.update();
            }else if (choice == "Report"){
                exit = logistic.report();
            }else { cout << "Error sudo: wrong operation choice!\r\n"; }

            return exit;
        }
};
 */

//____________________________File operation.cpp_____________________________

/* vector<shared_ptr<User> > usrVec; // access Derived via shared_ptr to Base
auto user = make_shared<User>();
auto sudo = make_shared<SuperUser>();

bool userFirst(bool exit);
bool menuSecond(bool exit); */


#endif