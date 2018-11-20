  /****************
  Created by Samuelito Perro
  A program that refeshes a personal conversation.
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
  using std::vector;

  int main ()
  {
    string Sender,
    Receiver,
    Path,
    Path2,
    sbuf;

    ifstream ifl,
    ifl2;

    vector <string> Content;

    cout << "Content-Type: text/plain\n\n";

// Getting stuff from html
    getline(cin, Sender);
    getline(cin, Receiver);

// Creating possible paths
    Path = "/home/student2018/scp002/webdata/DM" + Sender + "-" + Receiver + ".txt";
    Path2 = "/home/student2018/scp002/webdata/DM" + Receiver + "-" + Sender + ".txt";

//Opening content file
    ifl.open(Path);
    ifl2.open(Path2);

    //If none exist, conversation does not exist.
    if ((!ifl) && (!ifl2))
    {
      cout << "w|You don't have a conversation with this user.\n Start one by saying hi!" << endl;
      exit(0);
    }

    //If !ifl - ifl2 exists
    else if (!ifl)
    {
      while (getline(ifl2, sbuf))
      {
        Content.push_back(sbuf);
      }
    }
    else if (!ifl2)
    {
      while (getline(ifl, sbuf))
      {
        Content.push_back(sbuf);
      }
    }

//Output everything
    cout << "+|";
    for (int i = Content.size() - 1; i > -1; i--)
    {
      cout << Content[i] << " <br>" << endl;
    }
  }
