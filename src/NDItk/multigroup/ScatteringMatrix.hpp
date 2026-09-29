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

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  ScatteringMatrix( std::vector< LegendreMoment >&& moments,
                    unsigned int incident,
                    unsigned int number ) :
      RealListRecord( base::Keyword( "pn_full" ), generateData( moments ) ),
      incident_( incident ), outgoing_( incident ), number_moments_( number ) {

    this->generateBlocks();
  }

  /**
   *  @brief Private intermediate constructor
   */
  ScatteringMatrix( unsigned int particle,
                    std::vector< LegendreMoment >&& moments,
                    unsigned int incident,
                    unsigned int outgoing,
                    unsigned int number ) :
      RealListRecord( base::Keyword( "pn_prod_full", particle ),
                      generateData( std::move( moments ) ) ),
      incident_( incident ), outgoing_( outgoing ), number_moments_( number ) {

    this->generateBlocks();
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor for the scattering matrix
   */
  ScatteringMatrix() : RealListRecord( base::Keyword( "pn_full" ) ) {}

  /**
   *  @brief Default constructor for a secondary particle's production matrix
   *
   *  @param[in] particle    the secondary particle identifier
   */
  ScatteringMatrix( unsigned int particle ) :
      RealListRecord( base::Keyword( "pn_prod_full", particle ) ) {}

  /**
   *  @brief Constructor for the scattering matrix
   *
   *  @param[in] moments   the Legendre moments of the scattering matrix
   */
  ScatteringMatrix( std::vector< LegendreMoment > moments ) :
      ScatteringMatrix( std::move( moments ),
                        moments.size() == 0 ? 0 : moments.front().numberPrimaryGroups(),
                        moments.size() ) {}

  /**
   *  @brief Constructor for a secondary particle's production matrix
   *
   *  @param[in] particle   the secondary particle identifier
   *  @param[in] moments    the Legendre moments of the production matrix
   */
  ScatteringMatrix( unsigned int particle,
                    std::vector< LegendreMoment > moments ) :
      ScatteringMatrix( particle,
                        std::move( moments ),
                        moments.size() == 0 ? 0 : moments.front().numberPrimaryGroups(),
                        moments.size() == 0 ? 0 : moments.front().numberOutgoingGroups(),
                        moments.size() ) {}

  /**
   *  @brief Copy constructor
   */
  ScatteringMatrix( const ScatteringMatrix& base ) :
      RealListRecord( base ), incident_( base.incident_ ), outgoing_( base.outgoing_ ),
      number_moments_( base.number_moments_ ) {

    this->generateBlocks();
  }

  /**
   *  @brief Move constructor
   */
  ScatteringMatrix( ScatteringMatrix&& base ) :
      RealListRecord( std::move( base ) ), incident_( base.incident_ ), outgoing_( base.outgoing_ ),
      number_moments_( base.number_moments_ ) {

    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment
   */
  ScatteringMatrix& operator=( const ScatteringMatrix& base ) {

    if ( this != &base ) {

      base::RealListRecord::operator=( base );
      this->incident_ = base.incident_;
      this->outgoing_ = base.outgoing_;
      this->number_moments_ = base.number_moments_;
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Move assignment
   */
  ScatteringMatrix& operator=( ScatteringMatrix&& base ) {

    if ( this != &base ) {

      base::RealListRecord::operator=( std::move( base ) );
      this->incident_ = base.incident_;
      this->outgoing_ = base.outgoing_;
      this->number_moments_ = base.number_moments_;
      this->generateBlocks();
    }
    return *this;
  }

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
