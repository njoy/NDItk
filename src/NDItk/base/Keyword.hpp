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

  /**
   *  @brief Utility function to extract the particle id from a keyword
   *
   *  Some NDI records use keywords that include a particle id at the end of
   *  the keyword. These are basically of the form xxxxxxxx_yyyyy where yyyyy
   *  are digits that represent the particle id (e.g. 0 for gammas and 1001 for
   *  protons).
   *
   *  @param[in] keyword   the keyword
   */
  static std::tuple< std::string,
                     std::optional< std::string >,
                     std::optional< int >,
                     std::optional< multigroup::ReactionMultiplicityType >,
                     std::optional< multigroup::FissionType > >
  splitKeyword( std::string keyword ) {

    // special cases: sig_0
    if ( "sig_0" == keyword ) {

      return { std::move( keyword ), std::nullopt, std::nullopt, std::nullopt, std::nullopt };
    }
    else {

      // A regex that we will use to detect keywords with trailing particle types.
      // A key is basically xxx_yyy with an optional particle type at the end (the
      // full keyword would be xxx_yyy_0 for the xxx_yyy subtype keyword for gammas).
      // "([a-z]+(?:_[a-z]+)*)" captures the subtype part of the key, i.e. 'xxx_yyy'
      // and "([0-9]+)" captures an optional particle type that must end the string.
      const std::regex key{ "^([a-z]+(?:_[a-z]+)*)(?:_([0-9]+))?$" };

      std::smatch match;
      if ( std::regex_match( keyword, match, key ) ) {

        if ( match[1] == keyword ) {

          const std::array< std::string, 6 > suffixes = { "_all", "_few", "_rmo", "_pr", "_del", "_tot" };
          for ( unsigned int i = 0; i < suffixes.size(); ++i ) {

            if ( keyword.size() >= suffixes[i].size() &&
                 keyword.compare( keyword.size() - suffixes[i].size(), suffixes[i].size(), suffixes[i] ) == 0 ) {

              std::string subtype = keyword.substr( 0, keyword.size() - suffixes[i].size() );
              switch ( i ) {

                case 0 : return { std::move( keyword ), std::move( subtype ), std::nullopt, multigroup::ReactionMultiplicityType::All, std::nullopt };
                case 1 : return { std::move( keyword ), std::move( subtype ), std::nullopt, multigroup::ReactionMultiplicityType::Few, std::nullopt };
                case 2 : return { std::move( keyword ), std::move( subtype ), std::nullopt, multigroup::ReactionMultiplicityType::RMO, std::nullopt };
                case 3 : return { std::move( keyword ), std::move( subtype ), std::nullopt, std::nullopt, multigroup::FissionType::Prompt };
                case 4 : return { std::move( keyword ), std::move( subtype ), std::nullopt, std::nullopt, multigroup::FissionType::Delayed };
                case 5 : return { std::move( keyword ), std::move( subtype ), std::nullopt, std::nullopt, multigroup::FissionType::Total };
              }
            }
          }

          return { std::move( keyword ), std::nullopt, std::nullopt, std::nullopt, std::nullopt };
        }
        else {

          return { std::move( keyword ),
                   std::make_optional( std::string( match[1] ) ),
                   std::make_optional( std::stoi( match[2] ) ),
                   std::nullopt ,
                   std::nullopt};
        }
      }

      Log::error( "Unknown keyword found: \'{}\'", keyword );
      throw std::exception();
    }
  }

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
