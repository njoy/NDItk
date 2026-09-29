#ifndef NJOY_NDITK_MULTIGROUP_KERMA
#define NJOY_NDITK_MULTIGROUP_KERMA

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A kerma record for multigroup neutron data
 */
class Kerma : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  /**
   *  @brief Verify the kerma values
   *
   *  The following verification tests are performed:
   *    - there is at least one value
   *
   *  @param[in] values    the kerma values to be verified
   */
  template < typename Range >
  static void verify( const Range& values ) {

    if ( values.size() < 1 ) {

      Log::error( "Expected at least one kerma value, found {}",
                  values.size() );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor for the primary kerma
   */
  Kerma() : RealListRecord( base::Keyword( "kerma" ) ) {}

  /**
   *  @brief Default constructor for a secondary particle's kerma
   *
   *  @param[in] particle    the secondary particle identifier
   */
  Kerma( unsigned int particle ) :
      RealListRecord( base::Keyword( "kerma", particle ) ) {}

  /**
   *  @brief Constructor for the primary kerma
   *
   *  @param[in] values    the kerma values
   */
  Kerma( std::vector< double > values ) :
      RealListRecord( base::Keyword( "kerma" ), std::move( values ) ) {

    verify( this->values() );
  }

  /**
   *  @brief Constructor for a secondary particle's kerma
   *
   *  @param[in] particle    the secondary particle identifier
   *  @param[in] values      the kerma values
   */
  Kerma( unsigned int particle, std::vector< double > values ) :
      RealListRecord( base::Keyword( "kerma", particle ),
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
   *  @param[in,out] number   the number of kerma values
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
