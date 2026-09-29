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

  #include "NDItk/multigroup/ReactionCrossSections/src/verify.hpp"
  #include "NDItk/multigroup/ReactionCrossSections/src/generateData.hpp"
  #include "NDItk/multigroup/ReactionCrossSections/src/generateBlocks.hpp"

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

  #include "NDItk/multigroup/ReactionCrossSections/src/read.hpp"
  #include "NDItk/multigroup/ReactionCrossSections/src/print.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
