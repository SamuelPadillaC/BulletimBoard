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
  { time_t rawTime = system_clock::to_time_t(system_clock::now());
    struct tm *pTime = std::localtime(&rawTime);

    string Post,
    Name,
    Content,
    sbuf;


    ifstream ifl,
    ifl2;
    ofstream ofl;

    vector <string> VPost;
    vector <string> VNames;

    cout << "Content-Type: text/plain\n\n";

// Getting info from the html
    getline(cin, Name);
    getline(cin, Post);

//Opening and appending file with content and also the date and time
    ofl.open("/home/student2018/scp002/webdata/A27.txt", ios::out | ios::app);
    if (!ofl)
    {
      cout << "w|Woooops. I could not create or overwrite the bulleting." << endl;
      exit(0);
    }
    ofl << "<span class=\"dia\">" << std::put_time(pTime, "%A %D %R") << "</span><span class=\"UsName\"> Posted by "
    << Name << "</span><br> " << Post
    //Creating separator to enter the user who posted.
    << "|" << Name << endl;
    ofl.close();

//Opening content file again
    ifl2.open("/home/student2018/scp002/webdata/A27.txt");
    if (!ifl2)
    {
      cout << "w|Woooops. I could not find the bulleting on the server." << endl;
      exit(0);
    }
  //getting shit
    while (getline(ifl2, sbuf, '|'))
    {
      VPost.push_back(sbuf);
      getline(ifl2, sbuf);
      VNames.push_back(sbuf);
    }

//Output everything
  cout << "+|";
  for (int i = VPost.size() - 1; i > -1; i--)
    {
    cout << VPost[i] << " <br>" << endl;
    }
  }
