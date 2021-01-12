#include "components.hpp"
#include "util.cpp"

#include <regex>    // regular expressions
/* #include <string>
#include <iostream>
#include <ctime>   //library for data and time
#include <vector> */

using namespace std;

Util util;


class Categories{

    private:
        //Util util;
        string name = "";
        string date = util.dateGen();
        string price = "";
        int amount  = -1;

    protected:
        string id;
        int catIndex;
        string idCalc(int cat){
            int number = util.SessionDB[cat].size();  //reading the file DataBase
            catIndex = cat;
            return util.IntToString(number);
        }
        void dataToVec(){ //storing data to vector only after complete collection of data
            if(price != "" && amount >= 0 && name != ""){
                vector<string> newItem({id, name, price, util.IntToString(amount), date});
                bool found = util.getById(id)[0] == id? true : false;
                int index = util.getIndex(catIndex, id);

                switch(catIndex){
                    case 0: 
                        if(found){
                            util.DVDs[index] = newItem;
                        }else{ util.DVDs.push_back(newItem); }
                        //util.updater(); // auto updating the database
                        break;
                    case 1:  
                        if(found){
                            util.CDs[index] = newItem;
                        }else{ util.CDs.push_back(newItem); }
                        //util.updater(); //auto updating the database
                        break;
                    case 2:  
                        if(found){
                            util.Magazines[index] = newItem;
                        }else{ util.Magazines.push_back(newItem); }
                        //util.updater(); //auto updating the database
                        break;
                    case 3: if(found){
                            util.Books[index] = newItem;
                        }else{ util.Books.push_back(newItem); }
                        //util.updater(); //auto updating the database
                        break;
                }
            }
        }
            
    public:
        void setName(std::string n) { name = n;   dataToVec(); }
        void setPrice(std::string p){ price = p;  dataToVec(); }
        void setAmount(int a)       { amount = a; dataToVec(); }

        string getID(){ return id; }

        string getName(){ 
            if (name == ""){
                name = util.getById(id)[1];
            }
            return name;
        }
        string getPrice(){ 
            if (price == ""){
                price = util.getById(id)[2];
            }
            return price;
        }
        int getAmount(){
            if (amount == -1){
                amount = stoi(util.getById(id)[3]);
            }
            return amount; 
        }
};

class DVD : public Categories {

    private:
        string cat = "D";
        int index = 0;

    public:        
        DVD(std::string ID){ id = ID;}
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
        CD(std::string ID){ id = ID;}
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
        Magazine(std::string ID){ id = ID;}
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
        Book(std::string ID){ id = ID;}
        Book(){
            string n = idCalc(index);
            id = cat+"00"+n;
        }
};

class Logistic {
    private:
        //Util util;
        int chooseCat(bool IorO){
            int nav = 0;
            cout << "Choose category by entering \"DVD\", \"CD\", \"Magazines\", or \"Books\"" << endl;
            cout << "Alternatively enter \"back\" to abort or \"exit\" to close the program.\r\n" << endl;

            while(nav == 0){
                string choice; cin >> choice;
                if     (choice == "exit"     ){ nav = -2; break; }
                else if(choice == "back"     ){ nav = -1; break; }
                else if(choice == "DVD"      ){ nav =  0;  util.print(nav);  break; }
                else if(choice == "CD"       ){ nav =  1;  util.print(nav);  break; }
                else if(choice == "Magazines"){ nav =  2;  util.print(nav);  break; }
                else if(choice == "Books"    ){ nav =  3;  util.print(nav);  break; }
                else {  cout << "Choice not contemplated" << endl; }
            }
            return nav;
        }

    public:
        bool update(){
            //function to update
            util.updater();

            cout << "UPDATED!" << endl;
            return false;
        }

        bool restock(bool exit){
            bool back = false;
            cout << "RESTOCKING!\r\n"<< endl;
            
            int nav = chooseCat(false);  //this will print the product list
            if(nav == -2){ exit = true; }
            else if(nav == -1){ back = true; }
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

            int amount;
            string price;
            string name;

            int nav = chooseCat(true); //this will print the product list
            if(nav == -2){ exit = true; }
            else if(nav == -1){ back = true; }
            else{
                cout << "Please, enter a Name, a Price and a Quantity (e.g \"name\" \"10.90\" \"30\")" << endl;
                cout << "Alternatively enter \"back\" to abort or \"exit\" to close the program.\r\n" << endl;
                
                regex price_expr("-?[0-9]+([.][0-9]+)?"); //price regular expression validation
                regex amount_expr("-?[0-9]+([0-9]+)?");   //amount regular expression validation
                while(nav != -1 || nav != -2){
                    string amInt;
                    cin >> name;
                    if     (name == "exit"){ nav = -2;  exit = true;  break; }
                    else if(name == "back"){ nav = -1; break; }
                    cin >> price;
                    cin >> amInt;
                    if(regex_match(price, price_expr) && regex_match(amInt, amount_expr)){
                        amount = stoi(amInt);
                        price += "$"; 
                        break;
                    }else{
                        cout << "Wrong input! Make sure \"price\" and \"amount\" are numbers." << endl;
                        cout << "Try again!\r\n" << endl;
                    }
                }
            }

            DVD dvd;
            CD cd;
            Magazine magazine;
            Book book;

            switch(nav){
                case -2: exit = true;
                    break;
                case -1:
                    break;
                case  0: 
                    dvd.setName(name);
                    dvd.setPrice(price);
                    dvd.setAmount(amount);
                    cout << "Item successfully added!\r\n" << endl;
                    back = true;
                    break; 
                case  1: 
                    cd.setName(name);
                    cd.setPrice(price);
                    cd.setAmount(amount);
                    cout << "Item successfully added!\r\n" << endl;
                    back = true;
                    break;
                case  2: 
                    magazine.setName(name);
                    magazine.setPrice(price);
                    magazine.setAmount(amount);
                    cout << "Item successfully added!\r\n" << endl;
                    back = true;
                    break;
                case  3:
                    book.setName(name);
                    book.setPrice(price);
                    book.setAmount(amount);
                    cout << "Item successfully added!\r\n" << endl;
                    back = true;
                    break;
                default: cout << "System error: Wrong output from chooseCat()\r\n" << endl;
                    break;
            }

            if(!back){ exit = newItem(exit); }
            return exit;
        }

        bool sell(bool exit){
            bool back = false;
            cout << "SELLING\r\n";

            int nav = chooseCat(false);
            if(nav == -2){ exit = true; }
            else if(nav == -1){ back = true; }

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