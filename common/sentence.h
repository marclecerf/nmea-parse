#ifndef GPS_SENTENCE_H_
#define GPS_SENTENCE_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace Gps
{

  class Sentence
  {

    public:

      typedef std::vector<std::string> StrVec;
      typedef std::shared_ptr<Sentence> Ptr;

      static Ptr nextFromIstream( std::istream& );

      inline const std::string& data_type() const { return fields_.at(0); }

      inline StrVec::const_iterator begin() const { return fields_.begin(); }

      inline StrVec::const_iterator end() const { return fields_.end(); }

      inline size_t size() const { return fields_.size(); }

      std::pair<std::string,bool> at( uint32_t ) const;

      ~Sentence() {}

    private:

      static bool checkSum_( const std::string& );

      Sentence() {}

      std::vector<std::string> fields_;

  };

}

#endif
