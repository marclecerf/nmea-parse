#include <sstream>

#include "logger.h"

#include "sentence.h"

namespace Gps
{

  Sentence::Ptr Sentence::nextFromIstream( std::istream& is )
  {
    static Logger log {__PRETTY_FUNCTION__};

    std::string line;
    if( std::getline( is, line ) )
    {
      log.print( "\n" + line );
      // $ sign and checksum
      if( line.size() < 2 )
        return nullptr;

      if( line.front() != '$' )
        return nullptr;
      else line.erase(0,1);

      if( !Sentence::checkSum_(line) )
        return nullptr;

      auto mySentence = Sentence::Ptr(new Sentence);

      std::istringstream iss( line );
      std::string token("");
      while( std::getline( iss, token, ',' ) )
        mySentence->fields_.push_back( token );

      return mySentence;
    }
    else return nullptr;
  }

  std::pair<std::string,bool> Sentence::at( uint32_t idx ) const
  {
    if( idx < fields_.size() )
      return std::make_pair( fields_.at(idx), true );
    else
      return std::make_pair( "", false );
  }

  bool Sentence::checkSum_( const std::string& line )
  {
    std::istringstream iss( line );

    std::string checksumLine;
    std::string reportedChecksumStr;

    std::getline( iss, checksumLine, '*' );
    std::getline( iss, reportedChecksumStr );

    auto reportedChecksum =
      std::strtol( reportedChecksumStr.c_str(), nullptr, 16 );

    int8_t checksum = 0;
    for( const int8_t c: checksumLine )
      checksum = static_cast<int8_t>( checksum ^ c );

    if( checksum == reportedChecksum ) return true;
    else return false;
  }

}
