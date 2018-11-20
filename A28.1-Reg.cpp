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
  { // R stands for Registration / D for Database
    // V for vector / H for Hash / HD for Hash Database (comes from the database but hashed)
    string RName,
    Dname,
    RPasswd,
    HPasswd,
    HDpasswd,
    Perm,
    sbuf;

    vector <string> VNames;
    vector <string> VPass;
    vector <string> VPerm;

    ifstream ifl;
    ofstream ofl;

    cout << "Content-Type: text/plain\n\n";

// Getting info from the html
    getline(cin, RName);
    getline (cin, RPasswd);

//Hashing New Registration Password
    HPasswd = hashPassword(RPasswd);

//Getting passwords and usernames from text file
    ifl.open("/home/student2018/scp002/webdata/HashUsers.txt");
    if (!ifl)
    {
      cout << "w|Woooops. I could not find the password on the server." << endl;
      exit(0);
    }

//Creating Vectors holding Usernames, hashed Passwords, and Permissions
    while (getline(ifl, Dname, '|'))
    {
      VNames.push_back(Dname);
      //Creating Vector with existing Hashed Passwords
      getline (ifl, HDpasswd, '|');
      VPass.push_back(HDpasswd);
      getline (ifl, Perm);
      VPerm.push_back(Perm);
    }

//Verifying if the Inputs already exist.
    for (int i = 0; i < VNames.size(); i++)
    {
      if (RName == VNames[i])
      {
        cout << "-|This Username is already in use. Please select a different Username" << endl;
        exit(0);
      }
    }

//Opening file to append it with the new User info
    ofl.open("/home/student2018/scp002/webdata/HashUsers.txt", ios::out | ios::app);
    if (!ofl)
    {
      cout << "w|Woooops. I could not create the new account" << endl;
      exit(0);
    }
    ofl << RName << "|" << HPasswd << "|P[0" << endl;
    ofl.close();

//Notifying the html that the operation was succesful
    cout << "+|" << endl;

  }
