  /****************
  Created by Samuelito Perro
  A program that updates a
  bulletin board
  *****************/
  #include <iostream>
  #include <string>
  #include <fstream>
  #include <cstdlib>
  #include <iomanip>
  #include <ctime>
  #include <chrono>
  #include <vector>

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
  {
    string Filt,
    sbuf;

    ifstream ifl;

    vector <string> VPost;
    vector <string> VNames;
    vector <int> VPointers;

    cout << "Content-Type: text/plain\n\n";

// Getting info from the html
    getline(cin, Filt);

//Opening content file
    ifl.open("/home/student2018/scp002/webdata/A27.txt");
    if (!ifl)
    {
      cout << "w|Woooops. I could not find the bulleting on the server." << endl;
      exit(0);
    }
  //getting shit
    while (getline(ifl, sbuf, '|'))
    {
      VPost.push_back(sbuf);
      getline(ifl, sbuf);
      VNames.push_back(sbuf);
    }

//Cehcking usernames with wanted Username
    for (int i = 0; i < VNames.size(); i++)
    {
      if (VNames[i] == Filt)
      {
        VPointers.push_back(i);
      }
    }

//Output only the requested posts by certain usernames
    cout << "+|";
    for (int i = VPointers.size() - 1; i > -1; i--)
      {
        cout << VPost[VPointers[i]] << " <br>" << endl;
      }
  }
