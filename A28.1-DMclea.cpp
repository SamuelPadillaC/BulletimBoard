  /****************
  Created by Samuelito Perro
  A program that sends a personal message
  *****************/
  #include <iostream>
  #include <string>
  #include <fstream>
  #include <cstdlib>
  #include <vector>

  using std::cin;
  using std::cout;
  using std::endl;
  using std::string;
  using std::ifstream;
  using std::ofstream;
  using std::istringstream;
  using std::ios;
  using std::vector;

  int main ()
  {
    string Sender,
    sbuf;

    ifstream ifl;
    ofstream ofl;

    vector <string> VNames;
    vector <string> VTrash;
    vector <string> VstrDms;

    cout << "Content-Type: text/plain\n\n";

//Getting info from the html
    getline(cin, Sender);

//Getting info from the datafile
    ifl.open("/home/student2018/scp002/webdata/HashUsers.txt");
    if (!ifl)
    {
      cout << "w|Wooops I could not find the database." << endl;
      exit(0);
    }

//Creting vectors holding usernames and Dms
    while (getline(ifl, sbuf, '|'))
    {
      VNames.push_back(sbuf);
      // This is all trash (password and permissions)
      getline(ifl, sbuf, '[');
      VTrash.push_back(sbuf);
      // Doen't matter what comes after, i will delete it all
      getline(ifl, sbuf);
      VstrDms.push_back(sbuf);
    }

//Overwriting HashUsers
    ofl.open("/home/student2018/scp002/webdata/HashUsers.txt");
    if (!ofl)
    {
      cout << "w|Wooops. I could not send the message." << endl;
      exit(0);
    }

    for (int i = 0; i < VNames.size(); i++)
    {
      if (Sender == VNames[i])
      {
        ofl << VNames[i] << "|" << VTrash[i] << "[0" << endl;
      }
      else
      {
        ofl << VNames[i] << "|" << VTrash[i] << "[" << VstrDms[i] << endl;
      }
    }
    ofl.close();

//Notifying Succesful Operation
  cout << "+|";

  }
