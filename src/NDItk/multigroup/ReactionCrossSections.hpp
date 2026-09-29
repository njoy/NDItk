#ifndef NJOY_NDITK_MULTIGROUP_REACTIONCROSSSECTIONS
#define NJOY_NDITK_MULTIGROUP_REACTIONCROSSSECTIONS

// system includes
#include <algorithm>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"
#include "NDItk/multigroup/CrossSection.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A reaction cross section record for multigroup neutron data
 */
class ReactionCrossSections : protected base::RealListRecord {

  /* fields */

  std::vector< CrossSection > xs_;
  unsigned int groups_;
  unsigned int reactions_;

  /* auxiliary functions */

  /**
   *  @brief Verify the reaction cross section information
   *
   *  The following verification tests are performed:
   *    - there is at least one reaction
   *    - the number of groups for each reaction is the same
   *
   *  @param[in] reactions    the reactions to be verified
   */
  template < typename Range >
  static void verify( const Range& reactions ) {

    if ( reactions.size() < 1 ) {

      Log::error( "Expected at least one reaction, found {}", reactions.size() );
      throw std::exception();
    }

    const auto groups = reactions.front().numberGroups();
    for ( unsigned int i = 0; i < reactions.size(); ++i ) {

      if ( reactions[i].numberGroups() != groups ) {

        Log::error( "Inconsistent number of groups detected for reaction "
                    "with identifier \'{}\'", reactions[i].identifier() );
        Log::info( "Expected number of groups: {}", groups );
        Log::info( "Found number of groups: {}", reactions[i].numberGroups() );
        throw std::exception();
      }
    }
  }

  /**
   *  @brief Generate the record's data vector
   *
   *  @param[in] xs    the cross section data
   */
  static std::vector< double > generateData( std::vector< CrossSection > xs ) {

    // verify the data
    verify( xs );

    // generate the data vector
    std::vector< double > data;
    const auto groups = xs.front().numberGroups();
    data.reserve( xs.size() * ( 2 + groups ) );
    for ( unsigned int i = 0; i < xs.size(); ++i ) {

      data.insert( data.end(), xs[i].begin(), xs[i].end() );
    }
    return data;
  }

  /**
   *  @brief Generate the subrecords for this record
   */
  void generateBlocks() {

    if ( ! this->empty() ) {

      this->xs_.clear();
      for ( unsigned int index = 0; index < this->numberReactions(); ++index ) {

        const auto left = this->values().begin() + index * ( 2 + this->numberGroups() );
        const auto right = left + 2 + this->numberGroups();
        this->xs_.emplace_back( left, right );
      }
    }
  }

  using base::RealListRecord::key;

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  ReactionCrossSections( std::vector< CrossSection >&& xs,
                         std::size_t reactions, std::size_t groups ) :
      RealListRecord( base::Keyword( "sig_reac" ), generateData( std::move( xs ) ) ),
      reactions_( reactions ), groups_( groups ) {

    this->generateBlocks();
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  ReactionCrossSections() : RealListRecord( base::Keyword( "sig_reac" ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] xs    the cross section data
   */
  ReactionCrossSections( std::vector< CrossSection > xs ) :
      ReactionCrossSections( std::move( xs ), xs.size(),
                             xs.size() == 0 ? 0 : xs.front().numberGroups() ) {}

  /**
   *  @brief Copy constructor
   */
  ReactionCrossSections( const ReactionCrossSections& base ) :
      RealListRecord( base ), reactions_( base.reactions_ ), groups_( base.groups_ ) {

    this->generateBlocks();
  }

  /**
   *  @brief Move constructor
   */
  ReactionCrossSections( ReactionCrossSections&& base ) :
      RealListRecord( std::move( base ) ), reactions_( base.reactions_ ), groups_( base.groups_ ) {

    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment
   */
  ReactionCrossSections& operator=( const ReactionCrossSections& base ) {

    if ( this != &base ) {

      base::RealListRecord::operator=( base );
      this->groups_ = base.groups_;
      this->reactions_ = base.reactions_;
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Move assignment
   */
  ReactionCrossSections& operator=( ReactionCrossSections&& base ) {

    if ( this != &base ) {

      base::RealListRecord::operator=( std::move( base ) );
      this->groups_ = base.groups_;
      this->reactions_ = base.reactions_;
      this->generateBlocks();
    }
    return *this;
  }

  /* methods */

  /**
   *  @brief Return the number of groups defined in this record
   */
  std::size_t numberGroups() const {

      return this->groups_;
  }

  /**
   *  @brief Return the number of reactions defined in this record
   */
  std::size_t numberReactions() const {

    return this->reactions_;
  }

  /**
   *  @brief Return the cross section data for all reactions
   */
  const std::vector< CrossSection >& reactions() const {

    return this->xs_;
  }

  /**
   *  @brief Verify whether or not a given reaction is present
   *
   *  @param[in] reaction   the reaction to look for
   */
  bool hasReaction( int reaction ) const {

    auto iter = std::find_if( this->reactions().begin(), this->reactions().end(),
                              [reaction] ( const auto& entry ) {

                                return entry.identifier() == reaction; } );
    return iter != this->reactions().end();
  }

  /**
   *  @brief Return the cross section data for a given reaction
   *
   *  @param[in] reaction   the reaction to look for
   */
  const CrossSection& reaction( int reaction ) const {

    auto iter = std::find_if( this->reactions().begin(), this->reactions().end(),
                              [reaction] ( const auto& entry ) {

                                return entry.identifier() == reaction; } );
    if ( iter != this->reactions().end() ){

      return *iter;
    }
    else {

      Log::error( "Reaction with identifier \'{}\' is not present", reaction );
      throw std::exception();
    }
  }

  using base::RealListRecord::keyword;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;

    /**
     *  @brief Read the record data
     *
   *  @param[in,out] iter        an iterator to the current position in the input
   *  @param[in,out] end         an iterator to the end of the input
   *  @param[in,out] reactions   the number of reactions
   *  @param[in,out] groups      the number of groups
     */
    template< typename Iterator >
    void read( Iterator& iter, const Iterator& end, std::size_t reactions, std::size_t groups ) {

      // read in the data
      this->reactions_ = reactions;
      this->groups_ = groups;
      base::RealListRecord::read( iter, end, reactions * ( 2 + groups ) );
      this->generateBlocks();

      // verify
      verify( this->reactions() );
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
      for ( const auto& entry : this->xs_ ) {

        entry.print( iter );
      }
    }
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
