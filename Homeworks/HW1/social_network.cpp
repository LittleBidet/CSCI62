#include <iostream>
#include <string>
#include <sstream>
#include "user.h"
#include "network.h"
#include <ostream>

using namespace std;

int main(int argc, char* argv[]) {
    //check for arguments
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    Network net;
    net.readUsers(argv[1]);

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add user\n";
        cout << "2. Add friend connection\n";
        cout << "3. Delete friend connection\n";
        cout << "4. Write to file\n";
        cout << "Enter any other number to exit\n";

        string myline;
        if (!getline(cin, myline)) {
            break;
        }
        stringstream ss(myline);
        int option;
        
        if (!(ss >> option)) {
            cout << "Invalid command." << endl;
            break;
        }

        if (option == 1) {
            string firstName, lastName;
            int year, zip;
            if (ss >> firstName >> lastName >> year >> zip) {
                string fullName = firstName + " " + lastName;
                User* newUser = new User(net.numUsers(), fullName, year, zip, {});
                net.addUser(newUser);
                cout << "User '" << fullName << "' added" << endl;
            } else {
                cerr << "Error: Invalid input format for adding a user." << endl;
            }
        } else if (option == 2) {
            string fn1, ln1, fn2, ln2;
            if (ss >> fn1 >> ln1 >> fn2 >> ln2) {
                string name1 = fn1 + " " + ln1;
                string name2 = fn2 + " " + ln2;
                if (net.addConnection(name1, name2) != 0) {
                    cerr << "Error: Connection failed. One or both users may not exist." << endl;
                } else {
                    cout << "Connection added between '" << name1 << "' and '" << name2 << endl;
                }
            } else {
                cerr << "Error: Invalid input" << endl;
            }
        } else if (option == 3) {
            string fn1, ln1, fn2, ln2;
            if (ss >> fn1 >> ln1 >> fn2 >> ln2) {
                string name1 = fn1 + " " + ln1;
                string name2 = fn2 + " " + ln2;
                if (net.deleteConnection(name1, name2) != 0) {
                    cerr << "Error: Users may not exist or are not friends." << endl;
                } else {
                    cout << "Connection deleted between '" << name1 << "' and '" << name2 << endl;
                }
            } else {
                cerr << "Error: Invalid input" << endl;
            }
        } else if (option == 4) {
            string filename;
            if (ss >> filename) {
                net.writeUsers(filename.c_str());
                cout << "Wrote " << net.numUsers() << " users to file '" << filename << endl;
            } else {
                cerr << "Error: Please provide a valid filename" << endl;
            }
        } else {
            break;
        }
        cout << "\n";
    }
    cout << "Exiting..." << endl;
    return 0;
}

