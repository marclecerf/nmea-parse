#include <google/protobuf/text_format.h>

#include "common/nmea_parser.h"
#include "common/sentence.h"
#include "common/logger.h"
#include "common/event.h"

#include "common/gpgll.pb.h"

class GpgllParser : public Gps::NmeaParser
{
 
  public:

    GpgllParser() {}
    ~GpgllParser() {}

    std::string name() const { return "GPGLL"; }

    void parse( const Gps::Sentence& s )
    {
      static Logger log{__PRETTY_FUNCTION__};
      log.print("Parsing...");
      Gps::gpgll g;

      if( !sanityChecks_(s) ) return;

      parseUtcTime_(s,g);
      parseLatLon_(s,g);

      std::string str;
      google::protobuf::TextFormat::PrintToString(g, &str);
      log.print( "\n" + str );

      Event<Gps::gpgll>::fire(g);
    }

  private:

    bool sanityChecks_( const Gps::Sentence& s )
    {
      if( s.size() != 7 ) return false;

      return true;
    }

    // FIELD 5: HHMMSS[.SSS]
    void parseUtcTime_(const Gps::Sentence& s, Gps::gpgll& g)
    {
      static Logger log{__PRETTY_FUNCTION__};

      std::string str = std::move(s.at(5).first);

      log.print( str );

      if( str.size() >= 6 )
      {
        const auto utc_hr = std::strtoul(str.substr(0,2).c_str(),nullptr,10);
        const auto utc_min = std::strtoul(str.substr(2,2).c_str(),nullptr,10);

        uint32_t utc_msec =
          std::strtoul(str.substr(4,2).c_str(),nullptr,10) * 1000;

        utc_msec += (utc_hr*60 + utc_min)*60*1000;

        if( str.size() > 7 )
        {
          auto num_msec_digits = std::min<int>(str.size() - 7,3);
          uint32_t tmp = std::strtoul(str.substr(7,3).c_str(),nullptr,10);
          for( auto i=num_msec_digits; i<3; i++ ) tmp *= 10;

          utc_msec += tmp;
        }
        g.set_utc_msec( utc_msec );
      }
    }

    // FIELD 1,2,3,4 : DDMM[.MMMM],N|S,DDDMM[.MMMM],E|W
    void parseLatLon_( const Gps::Sentence& s, Gps::gpgll& g)
    {
      if( s.size() >= 6 )
      {
        auto str = std::move(s.at(1).first);
        if( str.size() >= 4 )
        {
          const auto deg = std::strtoul(str.substr(0,2).c_str(),nullptr,10);
          const auto min = std::strtoul(str.substr(2,2).c_str(),nullptr,10);
          auto  min_e4 = (deg*60 + min)*1e4;
          if( str.size() > 5 )
          {
            auto num_decimal_digits = std::min<int>(str.size() - 5,4);
            auto tmp = std::strtoul(str.substr(5,4).c_str(),nullptr,10);
            for( auto i = num_decimal_digits; i<4; i++ ) tmp *= 10;
            min_e4 += tmp;
          }
          if( s.at(2).first.front() == 'S' ) min_e4 *= -1;
          g.set_lat_min_e4( min_e4 );
        }
        str = std::move(s.at(3).first);
        if( str.size() >= 5 )
        {
          const auto deg = std::strtoul(str.substr(0,3).c_str(),nullptr,10);
          const auto min = std::strtoul(str.substr(3,2).c_str(),nullptr,10);
          auto  min_e4 = (deg*60 + min)*1e4;
          if( str.size() > 6 )
          {
            auto num_decimal_digits = std::min<int>(str.size() - 6,4);
            auto tmp = std::strtoul(str.substr(6,4).c_str(),nullptr,10);
            for( auto i = num_decimal_digits; i<4; i++ ) tmp *= 10;
            min_e4 += tmp;
          }
          if( s.at(4).first.front() == 'W' ) min_e4 *= -1;
          g.set_lon_min_e4( min_e4 );
        }
      }
    }
};

extern "C" Gps::NmeaParser* create()
{
  return new GpgllParser;
}

extern "C" void destroy( Gps::NmeaParser* t )
{
  delete t;
}
