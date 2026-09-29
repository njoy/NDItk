#ifndef NJOY_NDITK_MULTIGROUP_OUTGOINGPARTICLETRANSPORTDATA
#define NJOY_NDITK_MULTIGROUP_OUTGOINGPARTICLETRANSPORTDATA

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/StringListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief An outgoing particle type record for multigroup neutron data
 */
class OutgoingParticleTransportData : protected base::StringListRecord {

  /* fields */

  /* auxiliary functions */

  /**
   *  @brief Verify the outgoing transport data
   *
   *  The following verification tests are performed:
   *    - there is at least one value
   *
   *  @param[in] values    the zaid values to be verified
   */
  template < typename Range >
  static void verify( const Range& values ) {

    if ( values.size() < 1 ) {

      Log::error( "Expected at least one zaid value, found {}",
                  values.size() );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  OutgoingParticleTransportData() : StringListRecord( base::Keyword( "sec_part_zaids" ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] values    the zaid values
   */
  OutgoingParticleTransportData( std::vector< std::string > values ) :
      StringListRecord( base::Keyword( "sec_part_zaids" ), std::move( values ) ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the number of outgoing particles defined by this record
   */
  unsigned int numberOutgoingParticles() const { return this->size(); }

  using base::StringListRecord::keyword;
  using base::StringListRecord::values;
  using base::StringListRecord::size;
  using base::StringListRecord::empty;
  using base::StringListRecord::begin;
  using base::StringListRecord::end;
  using base::StringListRecord::print;

  /**
   *  @brief Read the record data
   *
   *  This function overrides the base record read() function to enable
   *  verification of the read data.
   *
   *  @param[in,out] iter     an iterator to the current position in the input
   *  @param[in,out] end      an iterator to the end of the input
   *  @param[in,out] number   the number of zaid values
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t number ) {

    base::StringListRecord::read( iter, end, number );
    verify( this->values() );
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
