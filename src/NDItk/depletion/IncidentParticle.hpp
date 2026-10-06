#ifndef NJOY_NDITK_DEPLETION_INCIDENTPARTICLE
#define NJOY_NDITK_DEPLETION_INCIDENTPARTICLE

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatCharacter.hpp"
#include "tools/disco/FreeFormatInteger.hpp"
#include "NDItk/base/Record.hpp"
#include "NDItk/depletion/Target.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief An incident particle record for depletion data
 */
class IncidentParticle : protected base::Record {

  /* auxiliary functions */

  /**
   *  @brief Verify the vector of depletion targets
   *
   *  The following verification tests are performed:
   *    - there is at least one target
   *
   *  @param[in] targets    the depletion target vector to be verified
   */
  template < typename Range >
  static void verify( const Range& targets ) {

    if ( targets.size() < 1 ) {

      Log::error( "Expected at least one target, found {}", targets.size() );
      throw std::exception();
    }
  }

public:

  /* fields */

  int identifier_;
  std::vector< Target > targets_;

  /* constructor */

  /**
   *  @brief Default constructor
   */
  IncidentParticle():
    Record( base::Keyword( "inc_part" ) ),
    identifier_(),
    targets_() {}

  /**
   *  @brief Constructor
   *
   *  @param[in] identifier   The incident particle identifier
   *  @param[in] targets      A vector of depletion targets
   */
  IncidentParticle( int identifier, std::vector< Target > targets ):
    Record( base::Keyword( "inc_part" ) ),
    identifier_( identifier ),
    targets_( std::move(targets) ) {

      verify( this->targets() );
    }

  /* methods */

  /**
   *  @brief Return the incident particle identifier
   */
  int incidentIdentifier() const { return this->identifier_; }

  /**
   *  @brief Return the number of targets for this incident particle
   */
  int numberTargets() const { return this->targets_.size(); }

  /**
   *  @brief Return the target data for this incident particle
   */
  const std::vector< Target >& targets() const { return this->targets_; }

  using base::Record::keyword;

  /*
   *  @brief Read the record data
   *
   *  @param[in,out] iter        an iterator to the current position in the input
   *  @param[in,out] end         an iterator to the end of the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    std::string keyword;

    // read in incident particle identifier
    this->identifier_ = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );

    // "num_targets" keyword (not stored of record)
    keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );
    if ( keyword != "num_targets" ) {
      Log::error( "Expected the 'num_targets' keyword as the second entry in an 'IncidentParticle' record" );
      Log::info( "Found {} as a keyword instead", keyword );
    }

    // read in number of targets
    auto numberTargets = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );
    if ( numberTargets <= 0 ) {
      Log::error( "Expected at least one 'Target' record in an 'IncidentParticle' record" );
    }

    // read in the vector of targets
    this->targets_.resize(numberTargets);
    for ( auto& entry : this->targets_ ) {

      // "target" keyword
      keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );

      if ( keyword != "target" ) {
        Log::error( "Expected the 'target' keyword as the next entry in an 'IncidentParticle' record" );
        Log::info( "Found {} as a keyword instead", keyword );
      }

      // read in target and add to the data
      entry.read( iter, end );
    }

    verify( this->targets() );
  }

  /**
  *   @brief Print the record (if it is not empty)
  *
  *   @param[in] iter           the current position in the output
  */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    if ( this->numberTargets() > 0 ) {

      auto indentLevel  = 0;
      auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

      std::ostringstream buffer;

      buffer << indentPrefix(indentLevel) << this->keyword() << "\n";

      buffer << indentPrefix(indentLevel+1) << this->incidentIdentifier() << "\n";

      buffer << indentPrefix(indentLevel+1) << "num_targets\n";
      buffer << indentPrefix(indentLevel+2) << this->numberTargets() << "\n";

      for (const auto& entry : this->targets() ) {

        std::string tmp;
        auto tmp_output = std::back_inserter(tmp);
        entry.print( tmp_output );
        buffer << tmp;
      }

      for ( auto c : buffer.str() ) { *iter++ = c; }
    }
  }

};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
