#ifndef NJOY_NDITK_BASE_INFORMATIONRECORD
#define NJOY_NDITK_BASE_INFORMATIONRECORD

// system includes
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

// other includes
#include "NDItk/base/SingleValueRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI record with a line of information
 */
class InformationRecord : protected SingleValueRecord< InformationRecord, std::string > {

  friend class SingleValueRecord< InformationRecord, std::string >;
  using Parent = SingleValueRecord< InformationRecord, std::string >;

protected:

  /**
   *  @brief Write the record data
   *
   *  This assumes that the record is not empty.
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void write( OutputIterator& iter ) const {

    unsigned int indent = 4;
    while ( indent-- ) { *iter++ = ' '; }
    for ( auto c : this->data().value() ) { *iter++ = c; }
    *iter++ = '\n';
  };

  using Parent::key;

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  InformationRecord() :
      SingleValueRecord( Keyword( "info" ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  InformationRecord( std::string value ) :
      SingleValueRecord( Keyword( "info" ), value ) {}

  /* methods */

  using Parent::keyword;
  using Parent::data;
  using Parent::empty;
  using Parent::print;

  /**
   *  @brief Read the record data
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    // move over the first endline
    while ( ( iter != end ) && std::isspace( *iter ) && ( *iter != '\n' ) ) {

      ++iter;
    }
    if ( *iter != '\n' ) {

      Log::error( "The table information line should start on a new line" );
      throw std::exception();
    }
    ++iter;
    // move over initial white space
    while ( ( iter != end ) && std::isspace( *iter ) && ( *iter != '\n' ) ) {

      ++iter;
    }
    auto pos = std::find_if( iter, end, [] ( auto&& character )
                                           { return character == '\n'; } );
    if ( pos == iter ) {

      Log::error( "There appears to be no table information line" );
      throw std::exception();
    }
    this->data() = std::string( iter, pos );

    // trim initial and trailing white space
    auto compare = []( auto&& character ) { return !std::isspace( character ); };
    auto start = std::find_if( this->data()->begin(), this->data()->end(), compare );
    auto stop = std::find_if( this->data()->rbegin(), this->data()->rend(), compare ).base();
    this->data() = std::string( start, stop );

    if ( pos != end ) {

      iter = pos + 1;
    }
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
