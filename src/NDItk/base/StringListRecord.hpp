#ifndef NJOY_NDITK_STRINGLISTRECORD
#define NJOY_NDITK_STRINGLISTRECORD

// system includes
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatCharacter.hpp"
#include "NDItk/base/ListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI base record with a list of string values
 */
class StringListRecord : protected ListRecord< StringListRecord, std::string > {

  friend class ListRecord< StringListRecord, std::string >;
  using Parent = ListRecord< StringListRecord, std::string >;

protected:

  /**
   *  @brief Write the record content
   *
   *  This assumes that the content is defined.
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void write( OutputIterator& iter ) const {

    std::ostringstream buffer;

    auto full = this->data().size() / 5;
    auto partial = this->data().size() % 5;
    auto x = this->data().begin();

    while ( full-- ) {

      buffer << "    " << x[0] << ' ' << x[1] << ' ' << x[2]
             << ' ' << x[3] << ' ' << x[4] << '\n';
      x += 5;
    }

    if ( partial ) {

      buffer << "   ";
      while ( partial-- ) {

        buffer << ' ' << *x;
        ++x;
      }
      buffer << '\n';
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  };

  using Parent::key;

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  StringListRecord( Keyword keyword ) :
      ListRecord( std::move( keyword ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  StringListRecord( Keyword keyword, std::vector< std::string > value ) :
      ListRecord( std::move( keyword ), std::move( value ) ) {}

  /* methods */

  using Parent::keyword;
  using Parent::subtype;
  using Parent::particle;
  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;

  /**
   *  @brief Read the record data
   *
   *  @param[in] iter    the current position in the input
   *  @param[in] end     the end position in the input
   *  @param[in] size    the number of values to be read
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t size ) {

    std::vector< std::string > data;
    data.reserve( size );
    while ( size-- ) {

      data.push_back( njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end ) );
    }
    this->data() = data;
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
