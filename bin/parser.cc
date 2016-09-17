#include <iostream>

#include "common/plugin.h"
#include "common/plugins_manager.h"
#include "common/nmea_parser.h"
#include "common/logger.h"
//#include "common/event.h"

int main()
{
  static Logger log {__func__};
  static std::ostringstream oss;

  auto plugins = PluginsManager<Gps::NmeaParser>::load( "plugins/nmea_parser", "list.idx" );

  while( 1 )
  {
    auto s = Gps::Sentence::nextFromIstream( std::cin );
    if( s )
    {
      auto p = plugins.find( s->data_type() );
      if( p != plugins.end() ) p->second->mutable_obj()->parse( *s );
      else
      {
        oss << "No parser for NMEA data type: " << s->data_type();
        log.print( oss.str() ); oss.str("");
      }
    }
    else
    {
      log.print( "No more valid GPS data." );
      break;
    }
  }

  log.print( "Done." );

  return 0;
}
