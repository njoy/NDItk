#ifndef NJOY_NDITK_MULTIGROUP_FISSIONNEUTRONMULTIPLICITY
#define NJOY_NDITK_MULTIGROUP_FISSIONNEUTRONMULTIPLICITY

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"
#include "NDItk/multigroup/FissionType.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A fission neutron multiplicity record for multigroup neutron data
 */
class FissionNeutronMultiplicity : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  /**
   *  @brief Verify the nu values
   *
   *  The following verification tests are performed:
   *    - there is at least one value
   *
   *  @param[in] values    the fission neutron multiplicity values to be verified
   */
  template < typename Range >
  static void verify( const Range& values ) {

    if ( values.size() < 1 ) {

      Log::error( "Expected at least one fission neutron multiplicity value, found {}",
                  values.size() );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  FissionNeutronMultiplicity() : RealListRecord( base::Keyword( "nu" ) ) {}

  /**
   *  @brief Constructor for a fission type
   *
   *  @param[in] type    the fission type (prompt, delayed or total)
   */
  FissionNeutronMultiplicity( FissionType type ) : RealListRecord( base::Keyword( "nu", type ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] type      the fission type (prompt, delayed or total)
   *  @param[in] values    the fission neutron multiplicity values
   */
  FissionNeutronMultiplicity( FissionType type,
                              std::vector< double > values ) :
      RealListRecord( base::Keyword( "nu", type ), std::move( values ) ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the fission type defined by this record
   */
  FissionType type() const { return this->key().fissionType().value(); }

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
   *  @param[in,out] number   the number of fission neutron multiplicity values
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
