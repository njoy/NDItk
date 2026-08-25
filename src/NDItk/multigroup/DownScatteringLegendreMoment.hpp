#ifndef NJOY_NDITK_MULTIGROUP_DOWNSCATTERINGLEGENDREMOMENT
#define NJOY_NDITK_MULTIGROUP_DOWNSCATTERINGLEGENDREMOMENT

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A Legendre moment subrecord for multigroup neutron data using
 *         an upper triangular matrix (deprecated)
 */
class DownScatteringLegendreMoment :
    protected base::SubListRecord< DownScatteringLegendreMoment, double > {

  friend class base::SubListRecord< DownScatteringLegendreMoment, double >;
  using Parent = base::SubListRecord< DownScatteringLegendreMoment, double >;

  /* fields */

  unsigned int groups_;
  std::vector< double > matrix_;

  /* auxiliary functions */

  #include "NDItk/multigroup/DownScatteringLegendreMoment/src/verify.hpp"
  #include "NDItk/multigroup/DownScatteringLegendreMoment/src/generateData.hpp"
  #include "NDItk/multigroup/DownScatteringLegendreMoment/src/generateMatrix.hpp"
  #include "NDItk/multigroup/DownScatteringLegendreMoment/src/write.hpp"

public:

  /* constructor */

  #include "NDItk/multigroup/DownScatteringLegendreMoment/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the Legendre moment order
   */
  int order() const { return static_cast< int >( std::round( this->value( 0 ) ) ); }

  /**
   *  @brief Return the number of groups defined by this record
   */
  unsigned int numberGroups() const { return this->groups_; }

  /**
   *  @brief Return the number of incident groups defined by this record
   */
  unsigned int numberPrimaryGroups() const { return this->groups_; }

  /**
   *  @brief Return the number of outgoing groups defined by this record
   */
  unsigned int numberOutgoingGroups() const { return this->groups_; }

  /**
   *  @brief Return the full matrix defined by this record
   */
  auto matrix() const {

    return this->matrix_ | njoy::tools::std23::views::chunk( this->numberGroups() );
  }

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
