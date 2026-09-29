#ifndef NJOY_NDITK_MULTIGROUP_ENERGYGROUPSTRUCTURE
#define NJOY_NDITK_MULTIGROUP_ENERGYGROUPSTRUCTURE

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief An energy group structure record for multigroup neutron data
 *
 *  This corresponds to an e_bounds or e_bounds_x record for the primary
 *  energy boundaries or outgoing particle energy boundaries.
 *
 *  The boundary values are given in MeV and must in be descending order.
 *  The number of values is equal to the number of groups plus 1 (the
 *  corresponding num_grps or num_grps_x metadata records must be given
 *  before the energy group structure record can be read).
 */
class EnergyGroupStructure : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  /**
   *  @brief Verify the group structure
   *
   *  The following verification tests are performed:
   *    - there are at least two values
   *    - the boundaries are unique and in descending order
   *
   *  @param[in] boundaries    the boundary values to be verified
   */
  template < typename Range >
  static void verify( const Range& boundaries ) {

    using namespace njoy::tools;

    if ( boundaries.size() < 2 ) {

      Log::error( "Expected at least two group structure boundary values, "
                  "found {}", boundaries.size() );
      throw std::exception();
    }

    if ( ! std::is_sorted( std20::ranges::rbegin( boundaries ),
                           std20::ranges::rend( boundaries ) ) ) {

      Log::error( "The boundaries of the group structure do not appear "
                  "to be in descending order" );
      throw std::exception();
    }
    if ( std::adjacent_find( std20::ranges::rbegin( boundaries ),
                             std20::ranges::rend( boundaries ) ) !=
         std20::ranges::rend( boundaries ) ) {

      Log::error( "The boundaries of the group structure do not appear "
                  "to be unique" );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor for the primary group structure
   */
  EnergyGroupStructure() : RealListRecord( base::Keyword( "e_bounds" ) ) {}

  /**
   *  @brief Default constructor for a secondary particle group structure
   *
   *  @param[in] particle    the secondary particle identifier
   */
  EnergyGroupStructure( unsigned int particle ) :
      RealListRecord( base::Keyword( "e_bounds", particle ) ) {}

  /**
   *  @brief Constructor for the primary group structure
   *
   *  @param[in] boundaries    the group structure boundary values
   */
  EnergyGroupStructure( std::vector< double > values ) :
      RealListRecord( base::Keyword( "e_bounds" ), std::move( values ) ) {

    verify( this->values() );
  }

  /**
   *  @brief Constructor for a secondary particle group structure
   *
   *  @param[in] particle    the secondary particle identifier
   *  @param[in] values      the group structure boundary values
   */
  EnergyGroupStructure( unsigned int particle, std::vector< double > values ) :
      RealListRecord( base::Keyword( "e_bounds", particle ),
                      std::move( values ) ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the number of groups defined by this record
   */
  unsigned int numberGroups() const {

    return this->empty() ? 0 : this->size() - 1;
  }

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
   *  @param[in,out] number   the number of boundary values
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
