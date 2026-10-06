#ifndef NJOY_NDITK_MULTIGROUP_OUTGOINGPARTICLETYPES
#define NJOY_NDITK_MULTIGROUP_OUTGOINGPARTICLETYPES

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/IntegerListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief An outgoing particle type record for multigroup neutron data
 */
class OutgoingParticleTypes : protected base::IntegerListRecord {

  /* fields */

  /* auxiliary functions */

  /**
   *  @brief Verify the outgoing particle types
   *
   *  The following verification tests are performed:
   *    - there is at least one value
   *
   *  @param[in] values    the velocity values to be verified
   */
  template < typename Range >
  static void verify( const Range& values ) {

    if ( values.size() < 1 ) {

      Log::error( "Expected at least one outgoing particle type, found {}",
                  values.size() );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  OutgoingParticleTypes() : IntegerListRecord( base::Keyword( "sec_part_types" ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] values    the outgoing particle types
   */
  OutgoingParticleTypes( std::vector< int > values ) :
      IntegerListRecord( base::Keyword( "sec_part_types" ), std::move( values ) ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the number of outgoing particles defined by this record
   */
  unsigned int numberOutgoingParticles() const { return this->size(); }

  using base::IntegerListRecord::keyword;
  using base::IntegerListRecord::values;
  using base::IntegerListRecord::size;
  using base::IntegerListRecord::empty;
  using base::IntegerListRecord::begin;
  using base::IntegerListRecord::end;
  using base::IntegerListRecord::print;

  /**
   *  @brief Read the record data
   *
   *  This function overrides the base record read() function to enable
   *  verification of the read data.
   *
   *  @param[in,out] iter     an iterator to the current position in the input
   *  @param[in,out] end      an iterator to the end of the input
   *  @param[in,out] number   the number of particle types
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t number ) {

    base::IntegerListRecord::read( iter, end, number );
    verify( this->values() );
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
