#ifndef GPS_NMEAPARSER_H_
#define GPS_NMEAPARSER_H_

#include "sentence.h"

namespace Gps
{

  class Sentence;

  class NmeaParser
  {
    public:

      virtual ~NmeaParser() {}

      virtual std::string name() const = 0;

      virtual void parse( const Sentence& ) = 0;

  };

}

#endif
