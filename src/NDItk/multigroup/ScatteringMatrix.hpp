#ifndef NJOY_NDITK_MULTIGROUP_SCATTERINGMATRICES
#define NJOY_NDITK_MULTIGROUP_SCATTERINGMATRICES

// system includes
#include <algorithm>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"
#include "NDItk/multigroup/LegendreMoment.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A scattering matrix record for multigroup neutron data
 */
class ScatteringMatrix : protected base::RealListRecord {

  /* fields */

  std::vector< LegendreMoment > moments_;
  unsigned int incident_;
  unsigned int outgoing_;
  unsigned int number_moments_;

  /* auxiliary functions */

  #include "NDItk/multigroup/ScatteringMatrix/src/verify.hpp"
  #include "NDItk/multigroup/ScatteringMatrix/src/generateData.hpp"
  #include "NDItk/multigroup/ScatteringMatrix/src/generateBlocks.hpp"

  using base::RealListRecord::key;

public:

  /* constructor */

  #include "NDItk/multigroup/ScatteringMatrix/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of primary groups defined in this record
   */
  unsigned int numberPrimaryGroups() const {

      return this->incident_;
  }

  /**
   *  @brief Return the number of outgoing groups defined in this record
   */
  unsigned int numberOutgoingGroups() const {

      return this->outgoing_;
  }

  /**
   *  @brief Return the number of moments defined in this record
   */
  unsigned int numberLegendreMoments() const {

      return this->number_moments_;
  }

  /**
   *  @brief Return the Legendre moments
   */
  const std::vector< LegendreMoment >& moments() const {

    return this->moments_;
  }

  /**
   *  @brief Verify whether or not a given moment is present
   *
   *  @param[in] order   the order to look for
   */
  bool hasMoment( int order ) const {

    auto iter = std::find_if( this->moments().begin(), this->moments().end(),
                              [order] ( const auto& entry )
                                      { return entry.order() == order; } );
    return iter != this->moments().end();
  }

  /**
   *  @brief Return the cross section data for a given reaction
   *
   *  @param[in] reaction   the reaction to look for
   */
  const LegendreMoment& moment( int order ) const {

    auto iter = std::find_if( this->moments().begin(), this->moments().end(),
                              [order] ( const auto& entry )
                                      { return entry.order() == order; } );
    if ( iter != this->moments().end() ){

      return *iter;
    }
    else {

      Log::error( "Moment with order \'{}\' is not present", order );
      throw std::exception();
    }
  }

  using base::RealListRecord::keyword;
  using base::RealListRecord::particle;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;

  #include "NDItk/multigroup/ScatteringMatrix/src/read.hpp"
  #include "NDItk/multigroup/ScatteringMatrix/src/print.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
