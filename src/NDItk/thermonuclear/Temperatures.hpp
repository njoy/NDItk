#ifndef NJOY_NDITK_THERMONUCLEAR_TEMPERATURES
#define NJOY_NDITK_THERMONUCLEAR_TEMPERATURES

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace thermonuclear {

/**
 *  @brief A temperature record for thermonuclear data
 */
class Temperatures : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  /**
   *  @brief Verify the temperature values
   *
   *  The following verification tests are performed:
   *    - there is at least one value
   *
   *  @param[in] values    the temperature values to be verified
   */
  template < typename Range >
  static void verify( const Range& values ) {

    if ( values.size() < 1 ) {

      Log::error( "Expected at least one temperature value, found {}",
                  values.size() );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor for the temperature record
   */
  Temperatures() : RealListRecord( base::Keyword( "temps" ) ) {}

  /**
   *  @brief Constructor for the temperature recor
   *
   *  @param[in] values    the temperature values
   */
  Temperatures( std::vector< double > values ) :
      RealListRecord( base::Keyword( "temps" ), std::move( values ) ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the number of temperatures defined by this record
   */
  unsigned int numberTemperatures() const { return this->size(); }

  using base::RealListRecord::keyword;
  using base::RealListRecord::particle;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;
  using base::RealListRecord::print;

  /**
   *  @brief Read the record data
   *
   *  This function overrides the base record read() function to enable
   *  verification of the read data.
   *
   *  @param[in,out] iter     an iterator to the current position in the input
   *  @param[in,out] end      an iterator to the end of the input
   *  @param[in,out] number   the number of kerma values
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t number ) {

    base::RealListRecord::read( iter, end, number );
    verify( this->values() );
  };
};

} // thermonuclear namespace
} // NDItk namespace
} // njoy namespace

#endif
