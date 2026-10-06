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

  /**
   *  @brief Verify the down scattering matrix information
   *
   *  The following verification tests are performed:
   *    - there is at least one Legendre moment
   *    - the number of groups for each moment is the same
   *
   *  @param[in] moments   the moments to be verified
   */
  template < typename Range >
  static void verify( const Range& moments ) {

    if ( moments.size() < 1 ) {

      Log::error( "Expected at least one moment, found {}", moments.size() );
      throw std::exception();
    }

    const auto groups = moments.front().numberGroups();
    for ( unsigned int i = 0; i < moments.size(); ++i ) {

      if ( moments[i].numberGroups() != groups ) {

        Log::error( "Inconsistent number of groups detected for moment "
                    "with order \'{}\'", moments[i].order() );
        Log::info( "Expected number of groups: {}", groups );
        Log::info( "Found number of groups: {}", moments[i].numberGroups() );
        throw std::exception();
      }
    }
  }

  /**
   *  @brief Generate the record's data vector
   *
   *  @param[in] moments    the Legendre moments
   */
  static std::vector< double > generateData( const std::vector< DownScatteringLegendreMoment >& moments ) {

    // verify the data
    verify( moments );

    // generate the data vector
    std::vector< double > data;
    const auto size = moments.front().size();
    data.reserve( moments.size() * size );
    for ( unsigned int i = 0; i < moments.size(); ++i ) {

      data.insert( data.end(), moments[i].begin(), moments[i].end() );
    }
    return data;
  }

  /**
   *  @brief Generate the subrecords for this record
   */
  void generateBlocks() {

    if ( ! this->empty() ) {

      this->moments_.clear();
      for ( unsigned int index = 0; index < this->numberLegendreMoments(); ++index ) {

        const auto size = 1 + this->numberGroups() * ( this->numberGroups() + 1 ) / 2;
        const auto left = this->values().begin() + index * size;
        const auto right = left + size;
        this->moments_.emplace_back( left, right, this->numberGroups() );
      }
    }
  }

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

  /**
   *  @brief Convert this deprecated record to a ScatteringMatrix instance
   */
  ScatteringMatrix toScatteringMatrix() const {

    if ( this->empty() ) {

      return ScatteringMatrix();
    }

    std::vector< LegendreMoment > moments;
    moments.reserve( this->moments_.size() );
    for ( const auto& moment : this->moments_ ) {

      std::vector< double > matrix;
      matrix.reserve( this->numberGroups() * this->numberGroups() );
      for ( const auto& row : moment.matrix() ) {

        matrix.insert( matrix.end(), row.begin(), row.end() );
      }
      moments.emplace_back( moment.order(), std::move( matrix ),
                            this->numberGroups(), this->numberGroups() );
    }
    return ScatteringMatrix( std::move( moments ) );
  }

  using base::RealListRecord::keyword;
  using base::RealListRecord::particle;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;

  /**
   *  @brief Read the record data (down scattering matrix)
   *
   *  @param[in,out] iter        an iterator to the current position in the input
   *  @param[in,out] end         an iterator to the end of the input
   *  @param[in,out] groups      the number of energy groups
   *  @param[in,out] number      the number of moments
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, unsigned int groups,
             unsigned int number ) {

    // read in the data
    this->groups_ = groups;
    this->number_moments_ = number;
    base::RealListRecord::read( iter, end, number * ( 1 + groups * ( groups + 1 ) / 2 ) );
    this->generateBlocks();

    // verify
    verify( this->moments() );
  };

  /**
   *  @brief Print the record (if it is not empty)
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    if ( ! this->empty() ) {

      this->key().print( iter );
      for ( const auto& entry : this->moments_ ) {

        entry.print( iter );
      }
    }
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
