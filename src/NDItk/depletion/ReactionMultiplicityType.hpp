#ifndef NJOY_NDITK_DEPLETION_REACTIONMULTIPLICITYTYPE
#define NJOY_NDITK_DEPLETION_REACTIONMULTIPLICITYTYPE

// system includes

// other includes

namespace njoy {
namespace NDItk {
namespace depletion {

enum class ReactionMultiplicityType : short {

  All = 1,
  Few = 2,
  RMO = 3 //! @todo change this name to be more understandable
};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
