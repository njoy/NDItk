#ifndef NJOY_NDITK_MULTIGROUP_HEATING
#define NJOY_NDITK_MULTIGROUP_HEATING

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A heating numbers record for multigroup neutron data
 */
class HeatingNumbers : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  /**
   *  @brief Verify the heating numbers
   *
   *  The following verification tests are performed:
   *    - there is at least one value
   *
   *  @param[in] values    the heating numbers to be verified
   */
  template < typename Range >
  static void verify( const Range& values ) {

    if ( values.size() < 1 ) {

      Log::error( "Expected at least one heating number, found {}",
                  values.size() );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor for the primary heating numbers
   */
  HeatingNumbers() : RealListRecord( base::Keyword( "heating" ) ) {}

  /**
   *  @brief Default constructor for a secondary particle's heating numbers
   *
   *  @param[in] particle    the secondary particle identifier
   */
  HeatingNumbers( unsigned int particle ) :
      RealListRecord( base::Keyword( "heating", particle ) ) {}

  /**
   *  @brief Constructor for the primary heating numbers
   *
   *  @param[in] values    the heating numbers
   */
  HeatingNumbers( std::vector< double > values ) :
      RealListRecord( base::Keyword( "heating" ), std::move( values ) ) {

    verify( this->values() );
  }

  /**
   *  @brief Constructor for a secondary particle's heating numbers
   *
   *  @param[in] particle    the secondary particle identifier
   *  @param[in] values      the heating numbers
   */
  HeatingNumbers( unsigned int particle, std::vector< double > values ) :
      RealListRecord( base::Keyword( "heating", particle ),
                      std::move( values ) ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the number of groups defined by this record
   */
  unsigned int numberGroups() const { return this->size(); }

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
   *  @param[in,out] number   the number of heating number values
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t number ) {

    base::RealListRecord::read( iter, end, number );
    verify( this->values() );
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
