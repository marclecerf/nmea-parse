#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <chrono>
#include <ctime>

class Logger
{
  public:

    Logger( const std::string& prefix = "Logger",
            std::ostream& os = std::cout ):
      prefix_( prefix ),
      os_( os )
    {
    }

    void print( const std::string& msg )
    {
      auto t = std::chrono::system_clock::to_time_t(
          std::chrono::system_clock::now() );

      char tstr[100];

      if( std::strftime(tstr, sizeof(tstr), "%T", std::localtime(&t) ) )
      {
        os_
          << tstr << " - "
          << prefix_ << ": " << msg << std::endl;
      }
    }
    
  private:

    std::string prefix_;
    std::ostream& os_;

};

#endif // LOGGER_H_
