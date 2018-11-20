  /****************
  Created by Samuelito Perro
  A program that outputs a story
  with input from the user.
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
  using std::ios;
  using std::vector;

  int main ()
  {
    string sbuf;

    ifstream ifl;

    vector <string> Content;
    vector <string> VNames;

    cout << "Content-Type: text/plain\n\n";

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
    Content.push_back(sbuf);
    getline(ifl, sbuf);
    VNames.push_back(sbuf);
  }

  //output everything
    cout << "+|";
    for (int i = Content.size() - 1; i > -1; i--)
    {
      cout << Content[i] << "<br>" << endl;
    }
  }
