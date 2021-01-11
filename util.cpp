#include <string>  // strings library
#include <iostream>// general library
#include <sstream> // library for intoToString converter
#include <vector>  // vectors library
#include <fstream> // file text scanner

using namespace std;


class Util {

    private:
        string delimiter = " :: ";
        vector<vector<string>> SessionDB;

        //file reader
        vector<string> importer(std::string cat){
            vector<string> DB;
            
            string fname = "DataBase.txt";
            ifstream file(fname);
            
            while(true){
                if (file.is_open()) {
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
                    cout << "DataBase missing. Creating one!\r\n\r\n\r\n" << endl;
                    fstream file;
                    file.open(fname, std::ios::out);
                    file << fflush;
                    file.close();
                }
            }
            return DB;
        }

        //importing data from HardDisk
        vector<vector<string>> dbQuery(bool IorO){
            
            vector<string> DVD;
            vector<string> CD;
            vector<string> Magazines;
            vector<string> Books;
            
            DVD       = importer("D");
            CD        = importer("C");
            Magazines = importer("M");
            Books     = importer("B");

            vector<vector<string>> category({DVD, CD, Magazines, Books});
            return category;
        }

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
        //categories matrix
        vector<vector<string>> DVDs;
        vector<vector<string>> CDs;
        vector<vector<string>> Magazines;
        vector<vector<string>> Books;

        //constructor method to initialize DataBase vectors
        Util(){ 
            SessionDB = dbQuery(false); 
            DVDs      = catSplit("D");
            CDs       = catSplit("C");
            Magazines = catSplit("M");
            Books     = catSplit("B");
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
