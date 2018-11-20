  /****************
  Created by Samuelito Perro
  A program that clears a
  bulletin file.
  *****************/
  #include <iostream>
  #include <string>
  #include <fstream>
  #include <cstdlib>

  using std::cin;
  using std::cout;
  using std::endl;
  using std::string;
  using std::ifstream;
  using std::ofstream;
  using std::ios;

  int main ()
  {
    ifstream ifl,
    ifl2;
    ofstream ofl;

    cout << "Content-Type: text/plain\n\n";

//Clearing file (Open and close)
    ofl.open("/home/student2018/scp002/webdata/A27.txt");
    if (!ofl)
    {
      cout << "w|Woooops. I could not find the bulleting on the server." << endl;
      exit(0);
    }
    ofl.close();

//Output signal to clear bulletin on the HTML
    cout << "0|";
  }
