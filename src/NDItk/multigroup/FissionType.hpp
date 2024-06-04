#ifndef NJOY_NDITK_MULTIGROUP_FISSIONTYPE
#define NJOY_NDITK_MULTIGROUP_FISSIONTYPE

// system includes

// other includes

namespace njoy {
namespace NDItk {
namespace multigroup {

enum class FissionType : short {

  Prompt = 1,
  Delayed = 2,
  Total = 3
};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
