#ifndef NJOY_NDITK_DEPLETION_MULTIPLICITIES
#define NJOY_NDITK_DEPLETION_MULTIPLICITIES

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief A reaction product multiplicity subrecord for depletion data
 */
class Multiplicities : protected base::SubListRecord< Multiplicities, int > {

  friend class base::SubListRecord< Multiplicities, int >;
  using Parent = base::SubListRecord< Multiplicities, int >;

  /* auxiliary functions */

  #include "NDItk/depletion/Multiplicities/src/verify.hpp"
  #include "NDItk/depletion/Multiplicities/src/generateData.hpp"
  #include "NDItk/depletion/Multiplicities/src/write.hpp"

public:

  /* constructor */

  #include "NDItk/depletion/Multiplicities/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the reaction identifier
   */
  int identifier() const { return this->value( 0 ); }

  /**
   *  @brief Return the number of reaction products
   */
  int numberReactionProducts() const { return this->value( 1 ); }

  /**
   *  @brief Return the reaction product identifiers
   */
  auto reactionProducts() const {

    using namespace njoy::tools;
    return this->values( 2, 2 * this->numberReactionProducts() )
               | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the reaction product multiplicities
   */
  auto multiplicities() const {

    using namespace njoy::tools;
    return this->values( 3, 2 * this->numberReactionProducts() )
               | std23::views::stride( 2 );
  }

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;
};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
