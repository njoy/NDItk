#ifndef NJOY_NDITK_MULTIGROUP_DOWNSCATTERINGMATRIX
#define NJOY_NDITK_MULTIGROUP_DOWNSCATTERINGMATRIX

// system includes
#include <algorithm>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"
#include "NDItk/multigroup/DownScatteringLegendreMoment.hpp"
#include "NDItk/multigroup/ScatteringMatrix.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A scattering matrix record for multigroup neutron data using
 *         upper triangular matrices (deprecated)
 */
class DownScatteringMatrix : protected base::RealListRecord {

  /* fields */

  std::vector< DownScatteringLegendreMoment > moments_;
  unsigned int groups_;
  unsigned int number_moments_;

  /* auxiliary functions */

  #include "NDItk/multigroup/DownScatteringMatrix/src/verify.hpp"
  #include "NDItk/multigroup/DownScatteringMatrix/src/generateData.hpp"
  #include "NDItk/multigroup/DownScatteringMatrix/src/generateBlocks.hpp"

  using base::RealListRecord::key;

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  DownScatteringMatrix( std::vector< DownScatteringLegendreMoment >&& moments,
                        unsigned int groups,
                        unsigned int number ) :
      RealListRecord( base::Keyword( "pn_down_full" ), generateData( moments ) ),
      groups_( groups ), number_moments_( number ) {

    this->generateBlocks();
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor for the scattering matrix
   */
  DownScatteringMatrix() : RealListRecord( base::Keyword( "pn_down_full" ) ) {}

  /**
   *  @brief Constructor for the scattering matrix
   *
   *  @param[in] moments   the Legendre moments of the scattering matrix
   */
  DownScatteringMatrix( std::vector< DownScatteringLegendreMoment > moments ) :
      DownScatteringMatrix( std::move( moments ),
                            moments.size() == 0 ? 0 : moments.front().numberGroups(),
                            moments.size() ) {}

  /**
   *  @brief Copy constructor
   */
  DownScatteringMatrix( const DownScatteringMatrix& base ) :
      RealListRecord( base ), groups_( base.groups_ ),
      number_moments_( base.number_moments_ ) {

    this->generateBlocks();
  }

  /**
   *  @brief Move constructor
   */
  DownScatteringMatrix( DownScatteringMatrix&& base ) :
      RealListRecord( std::move( base ) ), groups_( base.groups_ ),
      number_moments_( base.number_moments_ ) {

    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment
   */
  DownScatteringMatrix& operator=( const DownScatteringMatrix& base ) {

    if ( this != &base ) {

      base::RealListRecord::operator=( base );
      this->groups_ = base.groups_;
      this->number_moments_ = base.number_moments_;
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Move assignment
   */
  DownScatteringMatrix& operator=( DownScatteringMatrix&& base ) {

    if ( this != &base ) {

      base::RealListRecord::operator=( std::move( base ) );
      this->groups_ = base.groups_;
      this->number_moments_ = base.number_moments_;
      this->generateBlocks();
    }
    return *this;
  }

  /* methods */

  /**
   *  @brief Return the number of groups defined in this record
   */
  unsigned int numberGroups() const {

    return this->groups_;
  }

  /**
   *  @brief Return the number of primary groups defined in this record
   */
  unsigned int numberPrimaryGroups() const {

    return this->numberGroups();
  }

  /**
   *  @brief Return the number of outgoing groups defined in this record
   */
  unsigned int numberOutgoingGroups() const {

    return this->numberGroups();
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
  const std::vector< DownScatteringLegendreMoment >& moments() const {

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
   *  @brief Return the Legendre moment for a given order
   *
   *  @param[in] order   the order to look for
   */
  const DownScatteringLegendreMoment& moment( int order ) const {

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

  #include "NDItk/multigroup/DownScatteringMatrix/src/toScatteringMatrix.hpp"

  using base::RealListRecord::keyword;
  using base::RealListRecord::particle;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;

  #include "NDItk/multigroup/DownScatteringMatrix/src/read.hpp"
  #include "NDItk/multigroup/DownScatteringMatrix/src/print.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
