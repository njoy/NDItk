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
 *  @brief A fission neutron multiplicity record for multigroup neutron and photon data
 */
class FissionNeutronMultiplicity : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/FissionNeutronMultiplicity/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/FissionNeutronMultiplicity/src/ctor.hpp"

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

  #include "NDItk/multigroup/FissionNeutronMultiplicity/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
