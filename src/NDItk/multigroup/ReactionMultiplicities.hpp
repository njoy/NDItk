#ifndef NJOY_NDITK_MULTIGROUP_REACTIONMULTIPLICITIES
#define NJOY_NDITK_MULTIGROUP_REACTIONMULTIPLICITIES

// system includes
#include <algorithm>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/IntegerListRecord.hpp"
#include "NDItk/multigroup/ReactionMultiplicityType.hpp"
#include "NDItk/multigroup/Multiplicities.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A reaction product multiplicity record for multigroup data
 */
class ReactionMultiplicities : protected base::IntegerListRecord {

  /* fields */

  std::vector< Multiplicities > multiplicities_;
  unsigned int reactions_;

  /* auxiliary functions */

  #include "NDItk/multigroup/ReactionMultiplicities/src/verify.hpp"
  #include "NDItk/multigroup/ReactionMultiplicities/src/generateData.hpp"
  #include "NDItk/multigroup/ReactionMultiplicities/src/generateBlocks.hpp"

  using base::IntegerListRecord::key;

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  ReactionMultiplicities( std::vector< Multiplicities >&& multiplicities,
                          std::size_t reactions ) :
      IntegerListRecord( base::Keyword( "rprod" ),
                         generateData( std::move( multiplicities ) ) ),
      reactions_( reactions ) {

    this->generateBlocks();
  }

  /**
   *  @brief Private intermediate constructor
   */
  ReactionMultiplicities( ReactionMultiplicityType type,
                          std::vector< Multiplicities >&& multiplicities,
                          std::size_t reactions ) :
      IntegerListRecord( base::Keyword( "rprod", type ),
                         generateData( std::move( multiplicities ) ) ),
      reactions_( reactions ) {

    this->generateBlocks();
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  ReactionMultiplicities() : IntegerListRecord( base::Keyword( "rprod" ) ) {}

  /**
   *  @brief Constructor for a multiplicity type
   *
   *  @param[in] type    the multiplicity type (all, few or rmo)
   */
  ReactionMultiplicities( ReactionMultiplicityType type ) :
      IntegerListRecord( base::Keyword( "rprod", type ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] type              the multiplicity type (all, few or rmo)
   *  @param[in] multiplicities    the multiplicity data
   */
  ReactionMultiplicities( std::vector< Multiplicities > multiplicities ) :
      ReactionMultiplicities( std::move( multiplicities ),
                              multiplicities.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] type              the multiplicity type (all, few or rmo)
   *  @param[in] multiplicities    the multiplicity data
   */
  ReactionMultiplicities( ReactionMultiplicityType type,
                          std::vector< Multiplicities > multiplicities ) :
      ReactionMultiplicities( type,
                              std::move( multiplicities ),
                              multiplicities.size() ) {}

  /**
   *  @brief Copy constructor
   */
  ReactionMultiplicities( const ReactionMultiplicities& base ) :
      IntegerListRecord( base ), reactions_( base.reactions_ ) {

    this->generateBlocks();
  }

  /**
   *  @brief Move constructor
   */
  ReactionMultiplicities( ReactionMultiplicities&& base ) :
      IntegerListRecord( std::move( base ) ), reactions_( base.reactions_ ) {

    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment
   */
  ReactionMultiplicities& operator=( const ReactionMultiplicities& base ) {

    if ( this != &base ) {

      base::IntegerListRecord::operator=( base );
      this->reactions_ = base.reactions_;
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Move assignment
   */
  ReactionMultiplicities& operator=( ReactionMultiplicities&& base ) {

    if ( this != &base ) {

      base::IntegerListRecord::operator=( std::move( base ) );
      this->reactions_ = base.reactions_;
      this->generateBlocks();
    }
    return *this;
  }

  /* methods */

  /**
   *  @brief Return the multiplicity type defined by this record
   */
  decltype(auto) type() const { return this->key().multiplicityType(); }

  /**
   *  @brief Return the number of reactions defined in this record
   */
  std::size_t numberReactions() const {

    return this->reactions_;
  }

  /**
   *  @brief Return the multiplicity data for all reactions
   */
  const std::vector< Multiplicities >& reactions() const {

    return this->multiplicities_;
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
  const Multiplicities& reaction( int reaction ) const {

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

  using base::IntegerListRecord::keyword;
  using base::IntegerListRecord::values;
  using base::IntegerListRecord::size;
  using base::IntegerListRecord::empty;
  using base::IntegerListRecord::begin;
  using base::IntegerListRecord::end;

  #include "NDItk/multigroup/ReactionMultiplicities/src/read.hpp"
  #include "NDItk/multigroup/ReactionMultiplicities/src/print.hpp"
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
