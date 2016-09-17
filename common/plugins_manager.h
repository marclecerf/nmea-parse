#ifndef PLUGINS_MANAGER_H_
#define PLUGINS_MANAGER_H_

#include <string>
#include <map>
#include <fstream>
#include <memory>

#include "plugin.h"
#include "logger.h"

template< class T >
using PluginsMap = std::map< std::string, std::shared_ptr<Plugin<T> > >;

template< class T >
class PluginsManager
{
  public:

    static PluginsMap<T>
    load( const std::string& myPluginDir,
          const std::string& pluginIdxFile )
    {
      static Logger log {__func__};
      static std::ostringstream oss("");

      PluginsMap<T> plm;

      std::ifstream ifs ( myPluginDir + "/" + pluginIdxFile );
      if( ifs.is_open() )
      {
        std::string line;
        while( getline( ifs, line ) )
        {
          const std::string str = myPluginDir + "/" + line;

          auto ptr = std::make_shared<Plugin<T> >( str );

          if( ptr->isLoaded() )
          {
            const std::string& pname = ptr->obj()->name();

            oss << "Loaded Plugin[" << pname << "] from path: " << str;
            log.print( oss.str() ); oss.str("");

            auto result = plm.emplace( pname, ptr );
            if( !result.second )
            {
              oss << "WARNING: duplicate Plugin[" << pname << "], "
                << "keeping the first one and unloading the second.";
              log.print( oss.str() ); oss.str("");
            }
          }
          else
          {
            oss << "failed to load plugin from: " << str;
            log.print( oss.str() ); oss.str("");
          }
        }
        ifs.close();
      }
      else
      {
        std::ostringstream oss;
        oss << "cannot find " << pluginIdxFile << " in " << myPluginDir << ".";
        log.print( oss.str() );
        oss.str("");
        exit(1);
      }

      return std::move(plm);
    }

};

#endif
