#ifndef NJOY_NDITK_MULTIGROUP_FISSIONNEUTRONSPECTRUMVECTOR
#define NJOY_NDITK_MULTIGROUP_FISSIONNEUTRONSPECTRUMVECTOR

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"
#include "NDItk/multigroup/FissionType.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A fission neutron spectrum vector record for multigroup neutron and photon data
 */
class FissionNeutronSpectrumVector : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/FissionNeutronSpectrumVector/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/FissionNeutronSpectrumVector/src/ctor.hpp"

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

  #include "NDItk/multigroup/FissionNeutronSpectrumVector/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
