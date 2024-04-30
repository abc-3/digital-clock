
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

// Everything related to UI
namespace View
{
  class Display
  {   
    public:
      void showTime(std::string location, std::vector<int> time)
      { // write location and H:M:S time to terminal
        std::string ampm = (time[0] >= 12) ? "PM" : "AM"; // get AM / PM
        int hour = (time[0] % 12)>0 ? time[0] % 12 : 12; // 12hr time
        std::cout << "\033[1;37m" << location; 
        std::cout << "\033[0m:\n"; // display location in white
        std::cout << "\033[1;34m" << std::to_string(hour); 
        std::cout << "\033[0m:"; // hour display in blue
        std::cout << "\033[1;33m" << std::to_string(time[1]); 
        std::cout << "\033[0m:"; // minute display in yellow
        std::cout << "\033[1;32m" << std::to_string(time[2]);
        std::cout << "\033[0m "; // second display in green
        std::cout << "\033[1;31m" << ampm;
        std::cout << "\033[0m\n"; // AM/PM display in red
      }
  };
};

// Everything related to information (data storage)
namespace Model
{
  class Time
  { // model to hold a time vector and timezone information
    private:
      // create a pair (int, string) to hold timezone information
      // int is number of hours from UTC (O)
      std::pair<int, std::string> timezone(std::string zone)
      {
        if (zone=="MST")
          return std::make_pair(-6, "Laramie, WY (USA)");
        else if (zone=="UTC")
          return std::make_pair(0, "Reykjavik (Iceland)");
        else if (zone=="CST")
          return std::make_pair(8, "Beijing (China)");
        else // default EST
          return std::make_pair(-4, "New York, NY (USA)");
      }
      // clear the time vector, update with the current time
      std::vector<int> update(int hour, int min, int sec)
      {
        time.clear();
        time.push_back(hour);
        time.push_back(min);
        time.push_back(sec);
        return time;
      }

    public:
      // publicly accessible information is time and location
      std::vector<int> time; 
      std::string location;

      void getTime(std::string zone)
      /* getting the system time in hour, min, sec
         reference: https://cplusplus.com/reference/ctime/gmtime */
      {
        std::time_t rawtime;
        struct tm * calendar_time;
        std::time ( &rawtime );
        calendar_time = std::gmtime ( &rawtime );
        std::pair<int, std::string> tmz = timezone(zone);
        // timezone-adjusted hour needs to be a positive modulo 24
        int hour = ((calendar_time->tm_hour+tmz.first) % 24 + 24) % 24;
        int min = calendar_time->tm_min;
        int sec = calendar_time->tm_sec;
        update(hour, min, sec);
        location = tmz.second;
      }
  };
};

// Everything related to operation (logic)
namespace Controller
{
  class Clock
  {
    View::Display* d; // pointer for the Display
    Model::Time* t; // pointer for the Time

  public:
    Clock(View::Display* d, Model::Time* t, std::string tz)
    {
      t->getTime(tz); // call on the Model, get/set the Time
      d->showTime(t->location, t->time); // call on the View, show the Display
    }
  };
};

/* main() executes the script */
int main()
{
    // user location information (request)
    std::string timezone = "CST";

    // MVC generated view (response)
    View::Display d;
    Model::Time t;
    Controller::Clock clk(&d, &t, timezone);

    return 0;
}
