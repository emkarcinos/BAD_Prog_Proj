#include <iostream>
#include <iomanip>
#include <pqxx/pqxx> 
#include <sstream>
#include <string>

#define HOST "127.0.0.1"
#define DATABASE "fabryka_sprzetu_it"
#define SQL "SELECT * FROM PC;"

#define COL_W 15 //if some table contetnts have too many characters/numbers in it, change this value.

using namespace std;
using namespace pqxx;

int main() {
    //welcome message & prompt
    cout << "Welcome to MySQL connector. \nYou are trying to connect to host: " << HOST << "\nType your credentials to connect:\n";
    string username, password;
    cout << "User: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    //prases the text to match the connection typedef input arg
    stringstream stream;
    stream << "dbname = " << DATABASE << " user = " << username << " password = " << password << " \
        hostaddr = " << HOST << " port = 5432";
    
    try {
        connection C(stream.str());
        if (!C.is_open()) return 1; //closes the program if there's an issue with connection
        
        nontransaction N(C);
        result R(N.exec(SQL));

        //print result of last used query
        cout << SQL << endl;

        //print column names
        for(int i=0; i<(int)R[0].size(); i++)
            cout << right << setw(COL_W) << R.column_name(i);
        cout << endl;
        //print table contents
        for (result::const_iterator r = R.begin(); r!=R.end(); r++){
            for(int i=0; i<(int)R[0].size(); i++)
                cout << right << setw(COL_W) << r[i].as<string>();
            cout << endl;    
        }

        //end connection
        C.disconnect();
    } catch (const exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }
}