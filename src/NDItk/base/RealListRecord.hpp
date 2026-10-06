#ifndef NJOY_NDITK_REALLISTRECORD
#define NJOY_NDITK_REALLISTRECORD

// system includes
#include <vector>
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatReal.hpp"
#include "NDItk/base/ListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI base record with a list of real values
 */
class RealListRecord : protected ListRecord< RealListRecord, double > {

  friend class ListRecord< RealListRecord, double >;
  using Parent = ListRecord< RealListRecord, double >;

protected:

  /* auxiliary functions */

  /**
   *  @brief Write the record content
   *
   *  This assumes that the record is not empty.
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

      buffer << "    " << std::setprecision( 15 ) << x[0];
      buffer << ' ' << std::setprecision( 15 ) << x[1];
      buffer << ' ' << std::setprecision( 15 ) << x[2];
      buffer << ' ' << std::setprecision( 15 ) << x[3];
      buffer << ' ' << std::setprecision( 15 ) << x[4] << '\n';
      x += 5;
    }

    if ( partial ) {

      buffer << "   ";
      while ( partial-- ) {

        buffer << ' ' << std::setprecision( 15 ) << *x;
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
  RealListRecord( Keyword keyword ) :
      ListRecord( std::move( keyword ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  RealListRecord( Keyword keyword, std::vector< double > value ) :
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

    std::vector< double > data;
    data.reserve( size );
    while ( size-- ) {

      data.push_back( njoy::tools::disco::FreeFormatReal::read< double >( iter, end ) );
    }
    this->data() = data;
  }
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
