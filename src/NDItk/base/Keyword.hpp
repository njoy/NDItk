#ifndef NJOY_NDITK_BASE_KEYWORD
#define NJOY_NDITK_BASE_KEYWORD

// system includes
#include <optional>
#include <regex>
#include <string>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "NDItk/multigroup/FissionType.hpp"
#include "NDItk/multigroup/ReactionMultiplicityType.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief A class for NDI keywords
 *
 *  This class allows us to decompose
 */
class Keyword {

  /* fields */

  std::string keyword_;
  std::optional< std::string > subtype_ = std::nullopt;
  std::optional< unsigned int > particle_ = std::nullopt;
  std::optional< multigroup::ReactionMultiplicityType > multiplicity_ = std::nullopt;
  std::optional< multigroup::FissionType > fission_ = std::nullopt;

  /* auxiliary functions */

  #include "NDItk/base/Keyword/src/splitKeyword.hpp"

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   *
   *  @param[in] tuple   the keyword, subtype and particle identifier (if present)
   */
  Keyword( std::tuple< std::string,
                       std::optional< std::string >,
                       std::optional< int >,
                       std::optional< multigroup::ReactionMultiplicityType >,
                       std::optional< multigroup::FissionType > > tuple ) :
      keyword_( std::move( std::get< 0 >( tuple ) ) ),
      subtype_( std::move( std::get< 1 >( tuple ) ) ),
      particle_( std::move( std::get< 2 >( tuple ) ) ),
      multiplicity_( std::move( std::get< 3 >( tuple ) ) ),
      fission_( std::move( std::get< 4 >( tuple ) ) ) {}

public:

  /* constructor */

  Keyword() = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  Keyword( std::string keyword ) :
      Keyword( splitKeyword( std::move( keyword ) ) ) {}

  /**
   *  @brief Constructor for particle subtypes
   *
   *  @param[in] subtype    the subtype of the record
   *  @param[in] particle   the particle identifier
   */
  Keyword( std::string subtype, unsigned int particle ) :
      Keyword( subtype + "_" + std::to_string( particle ) ) {}

  /**
   *  @brief Constructor for multiplicity subtypes
   *
   *  @param[in] subtype    the subtype of the record
   *  @param[in] type       the multiplicity type
   */
  Keyword( std::string subtype, multigroup::ReactionMultiplicityType type ) :
      Keyword( subtype +
               ( type == multigroup::ReactionMultiplicityType::All
                 ? std::string( "_all" )
                 : type == multigroup::ReactionMultiplicityType::Few
                   ? std::string( "_few" )
                   : std::string( "_rmo" ) ) ) {}

  /**
   *  @brief Constructor for fission subtypes
   *
   *  @param[in] subtype    the subtype of the record
   *  @param[in] type       the fission type
   */
  Keyword( std::string subtype, multigroup::FissionType type ) :
      Keyword( subtype +
               ( type == multigroup::FissionType::Prompt
                 ? std::string( "_pr" )
                 : type == multigroup::FissionType::Delayed
                   ? std::string( "_del" )
                   : std::string( "_tot" ) ) ) {}

  /**
   *  @brief Return the keyword
   */
  const std::string& keyword() const { return this->keyword_; }

  /**
   *  @brief Return whether or not the keyword has a subtype
   */
  bool hasSubtype() const { return this->subtype_.has_value(); }

  /**
   *  @brief Return the subtype (if any)
   */
  const std::optional< std::string >& subtype() const { return this->subtype_; }

  /**
   *  @brief Return the particle identifier (if any)
   */
  const std::optional< unsigned int >& particle() const { return this->particle_; }

  /**
   *  @brief Return the multiplicity type (if any)
   */
  const std::optional< multigroup::ReactionMultiplicityType >& multiplicityType() const {

    return this->multiplicity_;
  }

  /**
   *  @brief Return the fission type (if any)
   */
  const std::optional< multigroup::FissionType >& fissionType() const {

    return this->fission_;
  }

  /**
   *  @brief Print the record keyword
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    for ( auto c : this->keyword() ) { *iter++ = c; }
    *iter++ = '\n';
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
