#include <string>  // strings library
#include <iostream>// general library
#include <sstream> // library for intoToString converter
#include <ctime>   //library for data and time
#include <vector>  // vectors library
#include <fstream> // file text scanner

using namespace std;


class Util {

    public:
        //categories matrix
        vector<vector<string>> DVDs;
        vector<vector<string>> CDs;
        vector<vector<string>> Magazines;
        vector<vector<string>> Books;

    private:
        string delimiter = " :: ";
        string fname = "DataBase.txt";
        vector<vector<string>> SessionDB;

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
                        file << data;
                    }
                    file << "\r\n";
                }
            }
            //closing the file
            file.close();
        }

        //importing data from HardDisk
        vector<vector<string>> dbQuery(bool InOut){
            
                vector<string> DVD;
                vector<string> CD;
                vector<string> Magazine;
                vector<string> Book;

            if(!InOut){    
                DVD      = importer("D");
                CD       = importer("C");
                Magazine = importer("M");
                Book     = importer("B");
            }else{
                exporter();
            }

            vector<vector<string>> category({DVD, CD, Magazine, Book});
            return category;
        }

    public:
        //the holly strings splitter *.*
        vector<string> split(std::string s, std::string delimiter){
            vector<string> vec;
            
            size_t pos = 0;
            string token;
            while ((pos = s.find(delimiter)) != string::npos) {
                token = s.substr(0, pos);
                vec.push_back(token);
                s.erase(0, pos + delimiter.length());
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
            }else{ cout << "System error: Fetching (Wrong category)" << endl; }

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

};
