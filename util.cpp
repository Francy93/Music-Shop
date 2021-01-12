#include <string>   // strings library
#include <iostream> // general library
#include <sstream>  // library for intoToString converter
#include <ctime>    // library for data and time
#include <vector>   // vectors library
#include <fstream>  // file text scanner
#include <algorithm>// std::find

using namespace std;


class Util {

    public:
        //categories matrix
        vector<vector<string>> DVDs;
        vector<vector<string>> CDs;
        vector<vector<string>> Magazines;
        vector<vector<string>> Books;
        
        vector<vector<string>> SessionDB;

    private:
        string delimiter = " :: ";
        string fname = "DataBase.txt";

        //file reader
        vector<string> importer(std::string cat){
            vector<string> DB;
            
            ifstream file(fname);
            
            bool newOpen = false;
            while(true){
                if (file.is_open() || newOpen) {
                    string line;
                    while (std::getline(file, line)) {
                        line.c_str();
                        if(line != "" && line != "1" && line.at(0) == cat.at(0)){
                            DB.push_back(line);
                        }
                    }
                    file.close();
                    break;
                }else if(file.fail()){
                    cout << "DataBase missing. Creating one..." << endl;
                    fstream file;
                    file.open(fname, std::ios::out);
                    file << fflush;
                    file.close();
                    file.open(fname, std::ios::in);
                    if (file.is_open()) { cout << "Created!\r\n\r\n\r\n"; newOpen = true; }
                }
            }
            return DB;
        }

        //data exporter
        void exporter(){
            vector<vector<vector<string>>> all({DVDs, CDs, Magazines, Books});

            fstream file;
            file.open(fname, std::ios::out);
            //writing cicle
            for(vector<vector<string>> cat: all){
                for(vector<string> item: cat){
                    for(string data: item){
                        if(data != item[(item.size())-1]){ data += delimiter; }
                        file << data;
                    }
                    file << endl;
                }
            }
            //closing the file
            file.close();
        }

        //importing data from HardDisk
        vector<vector<string>> dbQuery(bool InOut){
            
            vector<vector<string>> categories;
            vector<string> cat = {"D", "C", "M", "B"};

            if(!InOut){   
                for(string c: cat){
                    categories.push_back(importer(c));
                }
            }else{ exporter(); }

            return categories;
        }

    public:
        //the holly strings splitter *.*
        vector<string> split(std::string s, std::string delim){
            vector<string> vec;
            
            size_t pos = 0;
            string token;
            while ((pos = s.find(delim)) != string::npos) {
                token = s.substr(0, pos);
                vec.push_back(token);
                s.erase(0, pos + delim.length());
            }
            vec.push_back(s);
            return vec;
        }

    private:
        //fetching imported data, from sessionDB (ram) and splitting into categories
        vector<vector<string>> catSplit(std::string category){
            vector<vector<string>> products;

            if(category == "D"){
                vector<string> DVDs ({SessionDB[0]});
                for (string item: DVDs){
                    products.push_back(split(item, delimiter));
                }
            }else if(category == "C"){
                vector<string> CDs ({SessionDB[1]});
                for (string item: CDs){
                    products.push_back(split(item, delimiter));
                }
            }else if(category == "M"){
                vector<string> Magazines ({SessionDB[2]});
                for (string item: Magazines){
                    products.push_back(split(item, delimiter));
                }
            }else if(category == "B"){
                vector<string> Books ({SessionDB[3]});
                for (string item: Books){
                    products.push_back(split(item, delimiter));
                }
            }else{ cout << "System error! Util::catSplit: (Wrong category)" << endl; }

            return products;
        }
        
    public:
        //constructor method to initialize DataBase vectors
        Util(){ 
            SessionDB = dbQuery(false); //selfrunnin dbQuery in output mode
            DVDs      = catSplit("D");
            CDs       = catSplit("C");
            Magazines = catSplit("M");
            Books     = catSplit("B");
        }

        void updater(){
            dbQuery(true); //runnin dbQuery in input mode
        }

        string IntToString(int a){
            ostringstream temp;
            temp << a;
            return temp.str();
        }

        //current date generator
        string dateGen(){
            time_t curr_time;
            curr_time = time(NULL);
            tm *tm_local = localtime(&curr_time);

            int H = tm_local->tm_hour;
            string h = IntToString(H);  //converting hour to string
            int MI = tm_local->tm_min;
            string mi = IntToString(MI);//converting minutes to string
            int S = tm_local->tm_sec;
            string s = IntToString(S);  //converting seconds to string
            
            int D = tm_local->tm_mday;
            string d = IntToString(D);  //converting day to string
            int MO = tm_local->tm_mon;
            string mo = IntToString(MO);//converting month to string
            int Y = tm_local->tm_year;
            string y = IntToString(Y);  //converting year to string
            mo += y.at(0);  string vs = ""; y = y.at(1) +vs+ y.at(2);

            string time = h+":"+mi+":"+s;
            string date = d+":"+mo+":"+y;

            return date+"/"+time;
        }

        // Function to print the index of an element
        int getIndex(int cat, std::string k){
            int index = -1;
            vector<vector<string>> category;
            string cat = ""+ k.at(0);

            switch(cat){
                case 0: category = DVDs;
                    break;
                case 1: category = CDs;  
                    break;
                case 2: category = Magazines;
                    break;
                case 3: category = Books;
                    break;
                default: cout << "System error! Util::getIndex(): wrong category.\r\n" << endl;
                    break;
            }

            for (int i = 0; i <= size(category); i++){
                if(category[i][0] == k){ index = i; }
            }

            return index;
        }

        vector<string> getById(std::string index){
            vector<vector<string>> cat;
            vector<string> data({"empty", "empty", "empty", "empty", "empty"});

            if     (id.at(0) == 'D'){ cat = DVDs;      }
            else if(id.at(0) == 'C'){ cat = CDs;       }
            else if(id.at(0) == 'M'){ cat = Magazines; }
            else if(id.at(0) == 'B'){ cat = Books;     }
            else{ cout << "System error! Util::getById(): not a valid id\r\n" << endl; }

            for(vector<string> c: cat){
                if(c[0] == id){
                    data = c;
                }
            }
            return data;
        }

        void print(int cat){
            if(cat > SessionDB.size()){
                cout << "System error! Util::print() wrong cateory.\r\n" << endl;
            }else{
                for (string product: SessionDB[cat]){
                    cout << product << endl;
                }
                cout << endl;
            }
        }
};
