  /****************
  Created by Samuelito Perro
  A program that checks the login
  of a User.
  *****************/
  #include <iostream>
  #include <string>
  #include <fstream>
  #include <cstdlib>
  #include <iomanip>
  #include <ctime>
  #include <chrono>
  #include <vector>
  #include "randStrHash.hpp"

  using std::cin;
  using std::cout;
  using std::endl;
  using std::string;
  using std::ifstream;
  using std::ofstream;
  using std::ios;
  using std::chrono::system_clock;
  using std::time_t;
  using std::tm;
  using std::vector;

  int main ()
  { // D stands for database / H for Hash / HD for Hash Database
    string Name,
    Dname,
    Passwd,
    HDpasswd,
    Perm,
    Dms,
    sbuf;


    vector <string> VNames;
    vector <string> VPass;
    vector <string> VPerm;
    vector <string> VDms;

    ifstream ifl;
    ofstream ofl;

    cout << "Content-Type: text/plain\n\n";

// Getting info from the html
    getline(cin, Name);
    getline (cin, Passwd);

//Opening text file
    ifl.open("/home/student2018/scp002/webdata/HashUsers.txt");
    if (!ifl)
    {
      cout << "w[Woooops. I could not find the password on the server." << endl;
      exit(0);
    }

//Creating Vectors holding Usernames, Passwords, and Permissions
    while (getline(ifl, Dname, '|'))
    {
      VNames.push_back(Dname);
      //Creating a vector of hashed passwords
      getline (ifl, HDpasswd, '|');
      VPass.push_back(HDpasswd);
      getline (ifl, Perm, '[');
      VPerm.push_back(Perm);
      getline(ifl, Dms);
      VDms.push_back(Dms);
    }

//Matching Input with data in vectors
    for (int i = 0; i < VNames.size(); i++)
    {
      if (VNames[i] == Name)
      {
        //Checking password
        if (checkPassword(Passwd, VPass[i]))
        {
          cout << VPerm[i] << "[" << VDms[i];
          exit(0);
        }
        else
        cout << "-[Incorrect Password" << endl;
        exit(0);
      }
      if (i == VNames.size() - 1)
      {
        cout << "-[This Username doeees not exist" << endl;
      }
    }
  }
