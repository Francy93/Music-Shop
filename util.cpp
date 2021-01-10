#include <string>
#include <iostream>
#include <sstream> //library for intoToString converter
#include <vector>

using namespace std;

class Util {

    private:
        vector<vector<string>> SessionDB;

        vector<vector<string>> dbQuery(bool IorO){
            
            vector<string> DVD;
            vector<string> CD;
            vector<string> Magazines;
            vector<string> Books;
            
            DVD.push_back("primo");
            CD.push_back("secondo");
            Magazines.push_back("terzo");
            Books.push_back("quarto");

            vector<vector<string>> category({DVD, CD, Magazines, Books});
            return category;
        }
        
    public:
        //constructor method
        Util(){ SessionDB = dbQuery(false); }

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

        //fetching imported data, from sessionDB (ram)
        vector<vector<string>> fetching(std::string category){
            if(category == "D"){

            }else if(category == "C"){

            }else if(category == "M"){

            }else if(category == "B"){

            }else{ cout << "System error: Fetching (Wrong category)" << endl; }
        }
};
