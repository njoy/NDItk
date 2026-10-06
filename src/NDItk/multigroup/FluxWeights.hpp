#ifndef NJOY_NDITK_MULTIGROUP_FLUXWEIGHTS
#define NJOY_NDITK_MULTIGROUP_FLUXWEIGHTS

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A flux weight record for multigroup neutron data
 */
class FluxWeights : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  /**
   *  @brief Verify the weights
   *
   *  The following verification tests are performed:
   *    - there is at least one value
   *
   *  @param[in] weights    the weight values to be verified
   */
  template < typename Range >
  static void verify( const Range& weights ) {

    if ( weights.size() < 1 ) {

      Log::error( "Expected at least one flux weight value, found {}",
                  weights.size() );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  FluxWeights() : RealListRecord( base::Keyword( "wgts" ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] values    the flux weight values
   */
  FluxWeights( std::vector< double > values ) :
      RealListRecord( base::Keyword( "wgts" ), std::move( values ) ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the number of groups defined by this record
   */
  unsigned int numberGroups() const { return this->size(); }

  using base::RealListRecord::keyword;
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
   *  @param[in,out] number   the number of weight values
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
