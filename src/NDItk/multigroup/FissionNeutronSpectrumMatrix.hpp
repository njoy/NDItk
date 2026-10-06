#ifndef NJOY_NDITK_MULTIGROUP_FISSIONNEUTRONSPECTRUMMATRIX
#define NJOY_NDITK_MULTIGROUP_FISSIONNEUTRONSPECTRUMMATRIX

// system includes

// other includes
#include "tools/Log.hpp"
#include "tools/std23/views.hpp"
#include "NDItk/base/RealListRecord.hpp"
#include "NDItk/multigroup/FissionType.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A fission neutron spectrum matrix record for multigroup neutron data
 */
class FissionNeutronSpectrumMatrix : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  /**
   *  @brief Verify the fission neutron spectrum vector values
   *
   *  The following verification tests are performed:
   *    - there is at least one value
   *    - verify matrix size
   *
   *  @param[in] values    the production values to be verified
   */
  template < typename Range >
  static void verify( const Range& values ) {

    if ( values.size() < 1 ) {

      Log::error( "Expected at least one fission neutron spectrum matrix value, found {}",
                  values.size() );
      throw std::exception();
    }
    unsigned int size = std::sqrt( values.size() );
    if ( values.size() != size * size ) {

      Log::error( "Expected an array of size {} but found {} whoich does not represent a matrix",
                  size * size, values.size() );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  FissionNeutronSpectrumMatrix() : RealListRecord( base::Keyword( "chi_mat" ) ) {}

  /**
   *  @brief Constructor for a fission type
   *
   *  @param[in] type    the fission type (prompt, delayed or total)
   */
  FissionNeutronSpectrumMatrix( FissionType type ) : RealListRecord( base::Keyword( "chi_mat", type ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] type      the fission type (prompt, delayed or total)
   *  @param[in] values    the fission neutron spectrum matrix values
   */
  FissionNeutronSpectrumMatrix( FissionType type,
                                std::vector< double > values ) :
      RealListRecord( base::Keyword( "chi_mat", type ), std::move( values ) ) {

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
  unsigned int numberGroups() const { return std::sqrt( this->size() ); }

  /**
   *  @brief Return the matrix defined by this record
   */
  auto matrix() const {

    using namespace njoy::tools;
    return this->values()
               | std23::views::chunk( this->numberGroups() );
  }

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
   *  @param[in,out] number   the number of groups
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t number ) {

    base::RealListRecord::read( iter, end, number * number );
    verify( this->values() );
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
