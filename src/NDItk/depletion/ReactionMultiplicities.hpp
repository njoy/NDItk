#ifndef NJOY_NDITK_DEPLETION_REACTIONPRODUCTMULTIPLICITIES
#define NJOY_NDITK_DEPLETION_REACTIONPRODUCTMULTIPLICITIES

// system includes
#include <algorithm>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/IntegerListRecord.hpp"
#include "NDItk/depletion/ReactionMultiplicityType.hpp"
#include "NDItk/depletion/Multiplicities.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief A reaction product multiplicity record for depletion data
 */
class ReactionMultiplicities : protected base::IntegerListRecord {

  /* fields */

  std::vector< Multiplicities > multiplicities_;
  unsigned int reactions_;

  /* auxiliary functions */

  #include "NDItk/depletion/ReactionMultiplicities/src/verify.hpp"
  #include "NDItk/depletion/ReactionMultiplicities/src/generateData.hpp"
  #include "NDItk/depletion/ReactionMultiplicities/src/generateBlocks.hpp"

  using base::IntegerListRecord::key;

public:

  /* constructor */

  #include "NDItk/depletion/ReactionMultiplicities/src/ctor.hpp"

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

  #include "NDItk/depletion/ReactionMultiplicities/src/read.hpp"
  #include "NDItk/depletion/ReactionMultiplicities/src/print.hpp"
};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
