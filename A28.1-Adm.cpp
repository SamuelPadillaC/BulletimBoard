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
{ // R stands for Registration / D fot Database
  // V for vector / H for Hash / HD for Hash Database (comes from the database but hashed)
    string AName,
    Dname,
    Action,
    APerm,
    Dperm,
    HDpasswd,
    sbuf;

    int Pointer;

    vector <string> VNames;
    vector <string> VPass;
    vector <string> VPerm;

    ifstream ifl;
    ofstream ofl;

    cout << "Content-Type: text/plain\n\n";

// Getting info from the html
    getline(cin, AName);
    getline (cin, Action);
    if (Action == "Change")
    {
      getline(cin, APerm);
    }

//Opening file with user info
    ifl.open("/home/student2018/scp002/webdata/HashUsers.txt");
    if (!ifl)
    {
      cout << "w|Woooops. I could not find the password on the server." << endl;
      exit(0);
    }

//Creating Vectors holding Usernames, Passwords, and Permissions
    while (getline(ifl, Dname, '|'))
    {
      VNames.push_back(Dname);
      //Creating Vector with Hashed Passwords
      getline (ifl, HDpasswd, '|');
      VPass.push_back(HDpasswd);
      getline (ifl, Dperm);
      VPerm.push_back(Dperm);
    }

/*************************************************
THE FOLLOWING ONLY VALID FOR CHANGING PERMISSION
**************************************************/
  if (Action == "Change")
  {
//Verifying if the Username exists.
    for (int i = 0; i < VNames.size(); i++)
    {
      //If Username exists, Replace correspondant permission
      if (AName == VNames[i])
      {
        if (VPerm[i] == "A")
        {
          cout << "-|You can't change the permissions of another administrator" << endl;
          exit(0);
        }
        VPerm[i] = APerm;
        break;
      }
      if (i == VNames.size() - 1)
      {
        cout << "-|This Username does not exist";
        exit(0);
      }
    }

//Rewriting file with new permission
    ofl.open("/home/student2018/scp002/webdata/HashUsers.txt");
    if (!ofl)
    {
      cout << "w|Woooops. I could not create the new file" << endl;
      exit(0);
    }
    for (int i = 0; i < VPerm.size(); i++)
    {
      ofl << VNames[i] << "|" << VPass[i] << "|" << VPerm[i] << endl;
    }
    ofl.close();

//Notifying the html that the operation was succesful
    cout << "+|" << AName << " now has permission " << APerm << endl;
  }


/*****************************
ONLY VALID FOR REMOVING USERS
******************************/
  if (Action == "Remove")
  {
//Verifying if the Username exists.
    for (int i = 0; i < VNames.size(); i++)
    {
      //If Username exists
      if (AName == VNames[i])
      {
        //You can't remove an admin
        if (VPerm[i] == "A")
        {
          cout << "-|You can't remove another administrator" << endl;
          exit(0);
        }
        //If not an admin, edit pointer
        else
        {
          Pointer = i;
          break;
        }
      }
      if (i == VNames.size() - 1)
      {
        cout << "-|This Username does not exist";
        exit(0);
      }
    }

//Rewriting file with new users
    ofl.open("/home/student2018/scp002/webdata/HashUsers.txt");
    if (!ofl)
    {
      cout << "w|Woooops. I could not create the new file" << endl;
      exit(0);
    }
    for (int i = 0; i < VPerm.size(); i++)
    {
      if (i == Pointer)
      {
        i++;
      }
      if (i == VPerm.size())
      {
        break;
      }
      ofl << VNames[i] << "|" << VPass[i] << "|" << VPerm[i] << endl;
    }
    ofl.close();

//Notifying the html that the operation was succesful
    cout << "+|" << AName << " was removed" << endl;
  }
}
