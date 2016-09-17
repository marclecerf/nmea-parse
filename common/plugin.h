#ifndef PLUGIN_H_
#define PLUGIN_H_

#include <string>
#include <sstream>
#include <dlfcn.h>

#include "logger.h"

template< class T >
class Plugin
{
  public:
    
    Plugin( const std::string& filepath ):
      init_( false ),
      obj_(nullptr),
      lib_(nullptr),
      filepath_( filepath )
    {
      if( loadFromFile_() ) init_ = true;
    }

    ~Plugin()
    {
      static Logger log {__PRETTY_FUNCTION__};
      
      if( obj_ )
      {
        destroy_( obj_ );

//        TODO just avoid dlclose() for now, seg faults otherwise
//        dlclose( lib_ );
      }
    }

    bool isLoaded() { return init_; }

    const T* obj() const { return obj_; }
    T* mutable_obj() const { return obj_; }

  private:

    bool loadFromFile_()
    {
      static Logger log {__PRETTY_FUNCTION__};
      static std::ostringstream oss("");

      lib_ = dlopen( filepath_.c_str(), RTLD_LAZY );
      if( !lib_ )
      {
        oss << dlerror();
        log.print( oss.str() );
        oss.str("");
        return false;
      }

      const char* dlsym_error;

      create_ = (T* (*)()) dlsym( lib_, "create" );
      dlsym_error = dlerror();
      if( dlsym_error )
      {
        oss << dlsym_error;
        log.print( oss.str() );
        oss.str("");
        dlclose( lib_ );
        return false;
      }

      destroy_ = (void (*)(T*)) dlsym( lib_, "destroy" );
      dlsym_error = dlerror();
      if( dlsym_error )
      {
        oss << "can not load symbol destroy: " << dlsym_error;
        log.print( oss.str() );
        oss.str("");
        dlclose( lib_ );
        return false;
      }

      obj_ = create_();
      if( !obj_ )
      {
        oss << "can not create object from: " << filepath_;
        log.print( oss.str() );
        oss.str("");
        dlclose( lib_ );
        return false;
      }
      
      return true;
    }

    bool        init_           ;
    T*          obj_            ;
    void*       lib_            ;
    std::string filepath_       ;
    T*          (*create_)  ()  ;
    void        (*destroy_) (T*);

};

#endif
