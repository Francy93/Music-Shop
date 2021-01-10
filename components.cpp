#include "components.hpp"
#include "util.cpp"

#include <string>
#include <iostream>
#include <ctime>   //library for data and time
#include <vector>

using namespace std;


class Categories{

    private:
        Util util;
        string name;
        string date = util.dateGen();
        int price;
        int amount;

    protected:
        string idCalc(std::string cat){
            //reading the file DataBase
            int number = 0;
            return util.IntToString(number);
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
        string cat = "D";
        string idGen (){
            string n = idCalc(cat);
            return cat+"00"+n;
        }
};

class CD : public Categories {

    public:
        const string id = idGen();

     private:
        string cat = "C";
        string idGen (){
            string n = idCalc(cat);
            return cat+"00"+n;
        }

};

class Magazine : public Categories {

    public:
        const string id = idGen();

    private:
        string cat = "M";
        string idGen (){
            string n = idCalc(cat);
            return cat+"00"+n;
        }
};

class Book : public Categories {

    public:
        string id = "0";

    private:
        string cat = "B";
        string idGen (){
            string n = idCalc(cat);
            return cat+"00"+n;
        }
};

class Logistic {
    private:
        Util util;
        int chooseCat(bool IorO){
            int nav = 0;
            cout << "Choose category by entering \"DVD\", \"CD\", \"Magazines\", or \"Books\"" << endl;
            cout << "Alternatively enter \"back\" to abort or \"exit\" to close the program.\r\n" << endl;

            while(nav == 0){
                string choice; cin >> choice;
                if     (choice == "exit"     ){ nav = 1; break; }
                else if(choice == "back"     ){ nav = 2; break; }
                else if(choice == "DVD"      ){ break; }
                else if(choice == "CD"       ){ break; }
                else if(choice == "Magazines"){ break; }
                else if(choice == "Books"    ){ break; }
                else { cout << "Choice not contemplated" << endl; }
            }
            return nav;
        }

    public:
        bool update(){
            //function to update
            cout << "UPDATED!" << endl; 
            return false;
        }

        bool restock(bool exit){
            bool back = false;
            cout << "RESTOCKING!\r\n"<< endl;
            
            int nav = chooseCat(false);
            if(nav == 1){ exit = true; }
            else if(nav == 2){ back = true; }
            else{
                cout << "\r\nNow enter an ID followed by the amount to be summed like \"-2\", \"5\" up to 2147483647"<< endl;
                cout << "Alternatively enter \"back\" to abort or \"exit\" to close the program.\r\n" << endl;
            }
            
            while(!exit && !back){
                string amount; cin >> amount;
                if(amount == "exit"){
                    exit = true;
                    break;
                }else if(amount == "back"){
                    back = true;
                    exit = restock(exit);
                    break;
                }else try{
                    int num = stoi( amount );
                    // function to summ restock amount
                    cout << "Stock updated!" << endl;
                    cout << "Restoking one more product? Enter \"yes\" or \"no\".\r\n" << endl;
                    string choice; cin >> choice;

                    while(true){
                        if(choice == "yes"){
                            exit = restock(exit);
                            break;
                        }else if(choice == "no"){
                            break;
                        }else { cout << "Choice not contemplated" << endl; }
                    }
                    break;
                }catch (...) {
                    cout << "Wrong input. Try again!\r\n" << endl;
                }
            }
            return exit;
        }

        bool newItem(bool exit){
            bool back = false;
            cout << "ADDING A NEW PRODUCT\r\n" << endl;

            int nav = chooseCat(true);
            if(nav == 1){ exit = true; }
            else if(nav == 2){ back = true; }
            else{
                cout << "Please, enter a Name, a Price and a Quantity" << endl;
                cout << "Alternatively enter \"back\" to abort or \"exit\" to close the program.\r\n" << endl;
            }
            
            return false;
        }

        bool sell(bool exit){
            bool back = false;
            cout << "SELLING\r\n";

            int nav = chooseCat(false);
            if(nav == 1){ exit = true; }
            else if(nav == 2){ back = true; }

            while(!exit && !back){
                cout << "Now enter the ID of the product to be sold.\r\n" << endl;
                string id; cin >> id;
                bool idCheck = false; //checking existence id

                if(idCheck){
                    //displaying product details

                }
                else if(id == "exit"){ exit = true; }
                else if(id == "back"){ back = true; }
                else{ cout << "Wrong id!" << endl; }

            }
            if(back){ exit = sell(exit); }
            return exit;    
        }

        bool report(){
            bool exit = false;
            bool back = false;
            cout << "REPORT LIST" << endl;
            cout << "Enter \"back\" to abort or \"exit\" to close the program.\r\n" << endl;
            //function displaying the report list           
            
            while(!exit){
                cout << "Enter \"back\" to abort or \"exit\" to close the program.\r\n" << endl;
                string choice; cin >> choice;

                if(choice == "back"){ break; }
                else if(choice == "exit"){ exit = true; }
                else { cout << "Choice not contemplated" << endl; }
            }

            return exit;    
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
                exit =logistic.sell(exit);
            }else if (choice == "Restock"){
                exit =logistic.restock(exit);
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
                exit = logistic.sell(exit);
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