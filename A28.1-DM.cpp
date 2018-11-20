  /****************
  Created by Samuelito Perro
  A program that sends a personal message
  *****************/
  #include <iostream>
  #include <string>
  #include <fstream>
  #include <cstdlib>
  #include <iomanip>
  #include <ctime>
  #include <chrono>
  #include <vector>
  #include <sstream>
  #include <istream>

  using std::cin;
  using std::cout;
  using std::endl;
  using std::string;
  using std::ifstream;
  using std::ofstream;
  using std::istringstream;
  using std::ios;
  using std::chrono::system_clock;
  using std::time_t;
  using std::tm;
  using std::vector;

  int main ()
  { time_t rawTime = system_clock::to_time_t(system_clock::now());
    struct tm *pTime = std::localtime(&rawTime);

    string Sender,
    Recepient,
    Message,
    Path,
    Path2,
    strDms,
    sbuf;

    int PathPoint,
    ibuf;
    char *ep;

    ifstream ifl,
    ifl2,
    ifldata,
    iflfinal;
    ofstream ofl;
    istringstream iss;

    vector <string> VPost;
    vector <string> VNames;
    vector <string> VTrash;
    vector <string> VSenders;
    vector <string> VstrDms;
    vector <int> VDms;

    cout << "Content-Type: text/plain\n\n";

// Getting info from the html
    getline(cin, Sender);
    getline(cin, Recepient);
    getline(cin, Message);

//Creating Paths
    Path = "/home/student2018/scp002/webdata/DM" + Sender + "-" + Recepient + ".txt";
    Path2 = "/home/student2018/scp002/webdata/DM" + Recepient + "-" + Sender + ".txt";

// Getting info from the Users file
    ifldata.open("/home/student2018/scp002/webdata/HashUsers.txt");
    if (!ifldata)
    {
      cout << "w|Wooops I could not find the database." << endl;
      exit(0);
    }
// Creting vectors holding usernames and Dms
    while (getline(ifldata, sbuf, '|'))
    {
      VNames.push_back(sbuf);
      // This is all trash (password and permissions)
      getline(ifldata, sbuf, '[');
      VTrash.push_back(sbuf);
      //
      getline(ifldata, strDms);
      if (strDms != "0")
      {
        strDms += "\n";
        iss.str(strDms);
        getline(iss, sbuf, '|');
        VstrDms.push_back(sbuf);
        getline(iss, sbuf);
        VSenders.push_back(sbuf);
      }
      else if (strDms == "0")
      {
        VstrDms.push_back(strDms);
        VSenders.push_back("x");
      }
    }

    //Converting strings on VstrDms to ints
    for (int i = 0; i < VstrDms.size(); i++)
    {
      VDms.push_back(strtol(VstrDms[i].c_str(), &ep, 10));
      if (*ep != '\0')
      {
        cout << "w|The VstrDms was not a valid string number" << endl;
        exit(0);
      }
    }

// Checking if any conversation already exists
    ifl.open(Path);
    ifl2.open(Path2);

    //If none exist - create
    if ((!ifl) && (!ifl2))
    {
      ofl.open(Path);
      if (!ofl)
      {
        cout << "w|Wooops. I could not send the message." << endl;
        exit(0);
      }
      //Sending Message
      ofl << "<span class=\"dia\">" << std::put_time(pTime, "%A %D %R") << "</span><span class=\"DMName\"> Sent by "
      << Sender << "</span><br> " << Message << endl;
      ofl.close();
      //Notifying receiver of new message
      for (int i = 0; i < VNames.size(); i++)
      {
        if (VNames[i] == Recepient)
        {
          VDms[i]++;
          break;
        }
      }
      // Indicating correct version of path
      PathPoint = 1;
    }

    //If exist - append the existing one
    else
    {

      if (!ifl)
      {
        ofl.open(Path2, ios::app);
        if (!ofl)
        {
          cout << "w|Wooops. I could not send the message." << endl;
          exit(0);
        }
        //Sending Message
        ofl << "<span class=\"dia\">" << std::put_time(pTime, "%A %D %R") << "</span><span class=\"DMName\"> Sent by "
        << Sender << "</span><br> " << Message << endl;
        ofl.close();
        // Indicating which version exists
        PathPoint = 2;
        //Notifying receiver of new message
        for (int i = 0; i < VNames.size(); i++)
        {
          if (VNames[i] == Recepient)
          {
            VDms[i]++;
            break;
          }
        }
      }
      else if (!ifl2)
      {
        ofl.open(Path, ios::app);
        if (!ofl)
        {
          cout << "w|Wooops. I could not send the message." << endl;
          exit(0);
        }
        //Sending Message
        ofl << "<span class=\"dia\">" << std::put_time(pTime, "%A %D %R") << "</span><span class=\"DMName\"> Sent by "
        << Sender << "</span><br> " << Message << endl;
        ofl.close();
        // Indicating which version exists
        PathPoint = 1;
        //Notifying receiver of new message
        for (int i = 0; i < VNames.size(); i++)
        {
          if (VNames[i] == Recepient)
          {
            VDms[i]++;
            break;
          }
        }
      }
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
      if (VNames[i] == Recepient)
      {
        if (VSenders[i] == "x")
        {
        ofl << VNames[i] << "|" << VTrash[i] << "[" << VDms[i] << "|" << Sender << endl;
        }
        else
        {
          ofl << VNames[i] << "|" << VTrash[i] << "[" << VDms[i] << "|" << VSenders[i] << "|" << Sender << endl;
        }
      }
      else if (VSenders[i] != "x")
      {
        ofl << VNames[i] << "|" << VTrash[i] << "[" << VDms[i] << "|" << VSenders[i] << endl;
      }
      else
      ofl << VNames[i] << "|" << VTrash[i] << "[" << VDms[i] << endl;
    }
    ofl.close();

//Opening content file to post
    if (PathPoint == 2)
    {
    iflfinal.open(Path2);
    if (!iflfinal)
    {
      cout << "w|Did not open the file path2 and path2 was: " << Path2 << endl;
      exit(0);
    }
    //getting shit
      while (getline(iflfinal, sbuf))
      {
        VPost.push_back(sbuf);
      }
    }
    else if (PathPoint == 1)
    {
      iflfinal.open(Path);
      if (!iflfinal)
      {
        cout << "w|Did not open the file path1 and path1 was: " << Path << endl;
        exit(0);
      }
    //getting shit
      while (getline(iflfinal, sbuf))
      {
        VPost.push_back(sbuf);
      }
    }

//Output everything
  cout << "+|";
  for (int i = VPost.size() - 1; i > -1; i--)
    {
      cout << VPost[i] << " <br>" << endl;
    }

}
