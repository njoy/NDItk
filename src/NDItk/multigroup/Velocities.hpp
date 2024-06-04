#ifndef NJOY_NDITK_MULTIGROUP_VELOCITIES
#define NJOY_NDITK_MULTIGROUP_VELOCITIES

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A velocity record for multigroup neutron and photon data
 */
class Velocities : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

  #include "NDItk/multigroup/Velocities/src/verify.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/Velocities/src/ctor.hpp"

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

  #include "NDItk/multigroup/Velocities/src/read.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
