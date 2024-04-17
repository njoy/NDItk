#ifndef NJOY_NDITK_SINGLEREALRECORD
#define NJOY_NDITK_SINGLEREALRECORD

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatReal.hpp"
#include "NDItk/base/SingleValueRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief An NDI record with a single real value
 */
class SingleRealRecord : protected SingleValueRecord< SingleRealRecord, double > {

  friend class SingleValueRecord< SingleRealRecord, double >;
  using Parent = SingleValueRecord< SingleRealRecord, double >;

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
    buffer << std::setw( 20 ) << std::setprecision( 16 )
           << std::right << this->content().value();
    for ( auto c : buffer.str() ) { *iter++ = c; }
    *iter++ = '\n';
  };

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  SingleRealRecord( std::string keyword ) :
      SingleValueRecord( std::move( keyword ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the value of the record
   */
  SingleRealRecord( std::string keyword, double value ) :
      SingleValueRecord( std::move( keyword ), value ) {}

  /* methods */

  using Parent::keyword;
  using Parent::content;
  using Parent::print;

  /**
   *  @brief Read the record content
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    this->content() = njoy::tools::disco::FreeFormatReal::read< double >( iter, end );
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif