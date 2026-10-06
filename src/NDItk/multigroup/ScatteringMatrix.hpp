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

  /**
   *  @brief Verify the scattering matrix information
   *
   *  The following verification tests are performed:
   *    - there is at least one Legendre moment
   *    - the number of groups for each moment is the same
   *    - the moments are unique
   *
   *  @param[in] moments   the moments to be verified
   */
  template < typename Range >
  static void verify( const Range& moments ) {

    if ( moments.size() < 1 ) {

      Log::error( "Expected at least one moment, found {}", moments.size() );
      throw std::exception();
    }

    const auto incident = moments.front().numberPrimaryGroups();
    const auto outgoing = moments.front().numberOutgoingGroups();
    for ( unsigned int i = 0; i < moments.size(); ++i ) {

      if ( moments[i].numberPrimaryGroups() != incident ) {

        Log::error( "Inconsistent number of groups detected for moment "
                    "with order \'{}\'", moments[i].order() );
        Log::info( "Expected number of primary groups: {}", incident );
        Log::info( "Found number of primary groups: {}", moments[i].numberPrimaryGroups() );
        throw std::exception();
      }
      if ( moments[i].numberOutgoingGroups() != outgoing ) {

        Log::error( "Inconsistent number of groups detected for moment "
                    "with order \'{}\'", moments[i].order() );
        Log::info( "Expected number of outgoing groups: {}", outgoing );
        Log::info( "Found number of outgoing groups: {}", moments[i].numberOutgoingGroups() );
        throw std::exception();
      }
    }
  }

  /**
   *  @brief Generate the record's data vector
   *
   *  @param[in] moments    the Legendre moments
   */
  static std::vector< double > generateData( const std::vector< LegendreMoment >& moments ) {

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

        const auto size = 1 + this->numberPrimaryGroups() * this->numberOutgoingGroups();
        const auto left = this->values().begin() + index * size;
        const auto right = left + size;
        this->moments_.emplace_back( left, right,
                                     this->numberPrimaryGroups(),
                                     this->numberOutgoingGroups() );
      }
    }
  }

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

  /**
   *  @brief Read the record data (secondary particle production matrix)
   *
   *  @param[in,out] iter        an iterator to the current position in the input
   *  @param[in,out] end         an iterator to the end of the input
   *  @param[in,out] incident    the number of incident energy groups
   *  @param[in,out] outgoing    the number of outgoing energy groups
   *  @param[in,out] number      the number of moments
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, unsigned int incident,
             unsigned int outgoing, unsigned int number ) {

    // read in the data
    this->incident_ = incident;
    this->outgoing_ = outgoing;
    this->number_moments_ = number;
    base::RealListRecord::read( iter, end, number * ( 1 + incident * outgoing ) );
    this->generateBlocks();

    // verify
    verify( this->moments() );
  };

  /**
   *  @brief Read the record data (scattering matrix)
   *
   *  @param[in,out] iter        an iterator to the current position in the input
   *  @param[in,out] end         an iterator to the end of the input
   *  @param[in,out] incident    the number of incident energy groups
   *  @param[in,out] number      the number of moments
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, unsigned int incident,
             unsigned int number ) {

    read( iter, end, incident, incident, number );
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
