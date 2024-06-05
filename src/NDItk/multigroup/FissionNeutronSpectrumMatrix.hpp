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
 *  @brief A fission neutron spectrum matrix record for multigroup neutron and photon data
 */
class FissionNeutronSpectrumMatrix : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/FissionNeutronSpectrumMatrix/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/FissionNeutronSpectrumMatrix/src/ctor.hpp"

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

  #include "NDItk/multigroup/FissionNeutronSpectrumMatrix/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
