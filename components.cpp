#include "components.hpp"

#include <string>
#include <iostream>
#include <ctime>   //library for data and time
#include <sstream> //library for intoToString converter

using namespace std;

string IntToString(int a){
    ostringstream temp;
    temp << a;
    return temp.str();
}

string dateGen(){
    time_t curr_time;
    curr_time = time(NULL);
    tm *tm_local = localtime(&curr_time);

    int H = tm_local->tm_hour;
    string h = IntToString(H);  //converting hour to string
    int MI = tm_local->tm_hour;
    string mi = IntToString(MI);//converting minutes to string
    int S = tm_local->tm_hour;
    string s = IntToString(S);  //converting seconds to string
    int D = tm_local->tm_mday;
    string d = IntToString(D);  //converting day to string
    int MO = tm_local->tm_mon;
    string mo = IntToString(MO);//converting month to string
    int Y = tm_local->tm_year;
    string y = IntToString(Y);  //converting year to string

    string time = h+":"+mi+":"+s;
    string date = d+":"+mo+":"+y;

    return date+"/"+time;
}

class Categories{

    private:
        string name;
        string date = dateGen();
        int price;
        int amount;


    protected:
        string idCalc(std::string cat){
            //reading the file DataBase
            int number = 0;
            return IntToString(number);
        }
            
    public:
        void setName(std::string n)  { name = n;   };
        void setPrice(int p) { price = p;  };
        void setAmount(int a){ amount = a; };

        string getName() { return name;   };
        int getPrice()   { return price;  };
        int getAmount()  { return amount; };
};

class DVD : public Categories {
    
    public:
        const string id = idGen();


    private:
        string idGen (){
            string cat = "D";
            string n = idCalc(cat);
            return cat+"00"+n;
        }
};

class CD : public Categories {

    public:
        const string id = idGen();

     private:
        string idGen (){
            string cat = "C";
            string n = idCalc(cat);
            return cat+"00"+n;
        }

};

class Magazine : public Categories {

    public:
        const string id = idGen();

    private:
        string idGen (){
            string cat = "M";
            string n = idCalc(cat);
            return cat+"00"+n;
        }
};

class Book : public Categories {

    public:
        string id = "0";

    private:
        string idGen (){
            string cat = "B";
            string n = idCalc(cat);
            return cat+"00"+n;
        }
};

class Logistic {

    public:
        bool update(){ 
            cout << "updating" << endl; 
            return false;
        }

        bool restock(){ 
            cout << "restocking" << endl;
            return false;
        }

        bool newItem(){ 
            cout << "adding newItem" << endl;
            return false;
        }

        bool sell(){
            cout << "selling" << endl;
            return false;    
        }

        bool report(){
            cout << "reporting" << endl;
            return false;    
        }

};

struct User {
    
    protected:
        Logistic logistic;

    public:
        virtual bool privileges(){ return false; }
        virtual string text(){ return "Sell,\r\nRestock,\r\n"; }
        
        virtual bool selection(std::string choice){
            bool exit = false;

            if(choice == "Sell"){
                exit =logistic.sell();
            }else if (choice == "Restock"){
                exit =logistic.restock();
            }else if (choice == "NewItem" || choice == "Update" || choice == "Report"){
                cout << "Access denied. User not allowed!\r\n" << endl;
            }else { cout << "Error user: wrong operation choice!\r\n" << endl; }

            return exit;
        }
        
        virtual ~User() = default; // to silence -Wall warnings
};

struct SuperUser : User{
        
    public:
        bool privileges() override { return true; }
        string text() override { 
            return "Sell,\r\nRestock,\r\nNewItem,\r\nUpdate,\r\nReport.\r\n";
        }
        
        bool selection(std::string choice) override{
            bool exit = false;

            if(choice == "Sell"){
                exit = logistic.sell();
            }else if (choice == "Restock"){
                exit = logistic.restock();
            }else if(choice == "NewItem"){
                exit = logistic.newItem();
            }else if (choice == "Update"){
                exit = logistic.update();
            }else if (choice == "Report"){
                exit = logistic.report();
            }else { cout << "Error sudo: wrong operation choice!\r\n"; }
        }
};