#ifndef NJOY_NDITK_DOSIMETRY
#define NJOY_NDITK_DOSIMETRY

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/dosimetry/Metadata.hpp"
#include "NDItk/multigroup/ReactionMultiplicities.hpp"
#include "NDItk/multigroup/EnergyGroupStructure.hpp"
#include "NDItk/multigroup/FluxWeights.hpp"
#include "NDItk/multigroup/ReactionCrossSections.hpp"
#include "NDItk/multigroup/TotalCrossSection.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A multigroup neutron and photon table
 */
class DosimetryTable {

  /* fields */

  dosimetry::Metadata metadata_;
  multigroup::EnergyGroupStructure primary_structure_;
  multigroup::FluxWeights weights_;
  multigroup::TotalCrossSection total_;
  multigroup::ReactionCrossSections xs_;
  multigroup::ReactionMultiplicities product_multiplicities_all_;
  multigroup::ReactionMultiplicities product_multiplicities_few_;
  multigroup::ReactionMultiplicities product_multiplicities_rmo_;

  /* auxiliary functions */

  // code blatantly taken from MultigroupTable

  /**
   *  @brief A helper function to read a data record
   */
  template < typename Record, typename Iterator, typename... Arguments >
  static void readRecord( Record& record, Iterator& iter, const Iterator& end,
                          Arguments... arguments ) {

    if ( ! record.empty() ) {

      Log::error( "Duplicate keyword found: \'{}\'", record.keyword() );
      throw std::exception();
    }
    record.read( iter, end, arguments... );
  }

  template< typename Iterator >
  void readPrimaryStructure( Iterator& iter, const Iterator& end ) {

    if ( this->metadata_.numberGroups().has_value() ) {

      readRecord( this->primary_structure_, iter, end,
                  this->metadata_.numberGroups().value() + 1 );
    }
    else {

      Log::error( "Metadata required for the \'{}\' record was not found", this->primary_structure_.keyword() );
      Log::info( "Required metadata is missing: number of groups in the primary group structure" );
      throw std::exception();
    }
  }

  template< typename Record, typename Iterator >
  void readPrimaryData( Record& record, Iterator& iter, const Iterator& end ) {

    if ( this->metadata_.numberGroups().has_value() ) {

      readRecord( record, iter, end,
                  this->metadata_.numberGroups().value() );
    }
    else {

      Log::error( "Metadata required for the \'{}\' record was not found", record.keyword() );
      Log::info( "Required metadata is missing: number of groups in the primary group structure" );
      throw std::exception();
    }
  }

  /**
   *  @brief Verify the multigroup data
   *
   *  The following verification tests are performed:
   *    - the number of groups across the data is consistent
   */
  void verify() {

    // required records
    if ( this->primaryGroupBoundaries().empty() ||
         this->fluxWeights().empty() ||
         this->totalCrossSection().empty() ||
         this->reactionCrossSections().empty() ) {

      Log::error( "One or more required records are not found in the table" );
      Log::info( "Primary group structure record: {}",
                 this->primaryGroupBoundaries().empty() ? "absent" : "present" );
      Log::info( "Flux weight record: {}",
                 this->fluxWeights().empty() ? "absent" : "present" );
      Log::info( "Total cross section record: {}",
                 this->totalCrossSection().empty() ? "absent" : "present" );
      Log::info( "Reaction cross sections record: {}",
                 this->reactionCrossSections().empty() ? "absent" : "present" );
      throw std::exception();
    }

    // consistent group structure: primary
    const auto groups = this->metadata().numberGroups().value();
    if ( ( this->primaryGroupBoundaries().numberGroups() != groups ) ||
         ( this->fluxWeights().numberGroups() != groups ) ||
         ( ( ! this->totalCrossSection().empty() )
           && this->totalCrossSection().numberGroups() != groups ) ||
         ( this->reactionCrossSections().numberGroups() != groups ) ) {

      Log::error( "Found inconsistent number of primary groups across the table" );
      Log::info( "Number of primary groups in the metadata: {}",
                 this->metadata().numberGroups().value() );
      Log::info( "Number of primary groups in the primary group structure: {}",
                 this->primaryGroupBoundaries().numberGroups() );
      Log::info( "Number of primary groups in the flux weights: {}",
                 this->fluxWeights().numberGroups() );
      if ( ! this->totalCrossSection().empty() ) {

        Log::info( "Number of primary groups in the total cross section: {}",
                   this->totalCrossSection().numberGroups() );
      }
      Log::info( "Number of primary groups in the reaction cross section data: {}",
                 this->reactionCrossSections().numberGroups() );
      throw std::exception();
    }
  };

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  DosimetryTable() :
      metadata_(), primary_structure_(),
      weights_(), total_(), xs_(),
      product_multiplicities_all_( multigroup::ReactionMultiplicityType::All ),
      product_multiplicities_few_( multigroup::ReactionMultiplicityType::Few ),
      product_multiplicities_rmo_( multigroup::ReactionMultiplicityType::RMO ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] zaid              the zaid of the table
   *  @param[in] libname           the library name
   *  @param[in] process           the processing date
   *  @param[in] awr               the atomic weight ratio of the target
   *                               (with respect to the neutron mass)
   *  @param[in] temperature       the temperature of the target
   *  @param[in] dilution          the dilution (aka sigma0)
   *  @param[in] structure         the primary group structure
   *  @param[in] outgoing          the outgoing particle group structures
   *  @param[in] weights           the flux weights
   *  @param[in] total_xs          the total cross section
   *  @param[in] reaction_xs       the reaction cross section data
   *  @param[in] information       the table information line (optional)
   *  @param[in] source            the source date (optional)
   *  @param[in] weight            the atomic weight of the target (optional)
   */
  DosimetryTable( std::string zaid, std::string libname,
                  std::string process, double awr, double temperature,
                  double dilution,
                  multigroup::EnergyGroupStructure structure,
                  multigroup::FluxWeights weights,
                  multigroup::TotalCrossSection total_xs,
                  multigroup::ReactionCrossSections reaction_xs,
                  std::optional< std::string > information = std::nullopt,
                  std::optional< std::string > source = std::nullopt,
                  std::optional< double > weight = std::nullopt ) :
      metadata_( std::move( zaid ), std::move( libname ),
                 std::move( process ), awr, temperature, dilution,
                 structure.numberGroups(), reaction_xs.numberReactions(),
                 std::move( information ), std::move( source ), std::move( weight ),
                 std::nullopt, std::nullopt ),
      primary_structure_( std::move( structure ) ),
      weights_( std::move( weights ) ),
      total_( std::move( total_xs ) ),
      xs_( std::move( reaction_xs ) ) {

    this->verify();
  }

  /* methods */

  /**
   *  @brief Return the metadata of the table
   */
  const dosimetry::Metadata& metadata() const { return this->metadata_; }

  /**
   *  @brief Return the primary group structure record
   */
  const multigroup::EnergyGroupStructure& primaryGroupBoundaries() const {

    return this->primary_structure_;
  }

  /**
   *  @brief Return the flux weight record
   */
  const multigroup::FluxWeights& fluxWeights() const { return this->weights_; }

  /**
   *  @brief Return the total cross section record
   */
  const multigroup::TotalCrossSection& totalCrossSection() const {

    return this->total_;
  }

  /**
   *  @brief Return the reaction cross section record
   */
  const multigroup::ReactionCrossSections& reactionCrossSections() const {

    return this->xs_;
  }

  /**
   *  @brief Return the reaction product multiplicities record for the requested multiplicity type
   */
  const multigroup::ReactionMultiplicities&
  reactionProductMultiplicities( const multigroup::ReactionMultiplicityType& type ) const {

    switch ( type ) {

      case multigroup::ReactionMultiplicityType::All  : return this->product_multiplicities_all_;
      case multigroup::ReactionMultiplicityType::Few  : return this->product_multiplicities_few_;
      case multigroup::ReactionMultiplicityType::RMO  : return this->product_multiplicities_rmo_;
      default : {

        throw std::runtime_error( "This code is unreachable, contact a developer" );
      }
    }
  }

  /**
   *  @brief Read the table data
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    std::string keyword;
    while ( ( keyword != "end" ) && ( iter != end ) ) {

      keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );

      // metadata
      if ( this->metadata_.isMetadataKey( keyword ) ) {

        this->metadata_.read( keyword, iter, end );
      }
      // primary and outgoing group structure keyword
      else if ( keyword == this->primary_structure_.keyword() ) {

        readPrimaryStructure( iter, end );
      }
      // flux weights
      else if ( keyword == this->weights_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->weights_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // total cross section
      else if ( keyword == this->total_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->total_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // reaction cross sections
      else if ( keyword == this->xs_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() &&
             this->metadata_.numberReactions().has_value() ) {

          readRecord( this->xs_, iter, end,
                      this->metadata_.numberReactions().value(),
                      this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          if ( ! this->metadata_.numberGroups().has_value() ) {

            Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          }
          if ( ! this->metadata_.numberReactions().has_value() ) {

            Log::info( "Required metadata is missing: number of reactions" );
          }
          throw std::exception();
        }
      }
      // reaction product multiplicities: all
      else if ( keyword == this->product_multiplicities_all_.keyword() ) {

        if ( this->metadata_.numberReactions().has_value() ) {

          readRecord( this->product_multiplicities_all_, iter, end,
                      this->metadata_.numberReactions().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of reactions" );
          throw std::exception();
        }
      }
      // reaction product multiplicities: few
      else if ( keyword == this->product_multiplicities_few_.keyword() ) {

        if ( this->metadata_.numberReactions().has_value() ) {

          readRecord( this->product_multiplicities_few_, iter, end,
                      this->metadata_.numberReactions().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of reactions" );
          throw std::exception();
        }
      }
      // reaction product multiplicities: rmo
      else if ( keyword == this->product_multiplicities_rmo_.keyword() ) {

        if ( this->metadata_.numberReactions().has_value() ) {

          readRecord( this->product_multiplicities_rmo_, iter, end,
                      this->metadata_.numberReactions().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of reactions" );
          throw std::exception();
        }
      }
      // unknown or end keyword
      else {

        if ( keyword != "end" ) {

          Log::error( "Unknown keyword found: \'{}\'", keyword );
          throw std::exception();
        }
      }

      // read over whitespace or until the end
      while ( std::isspace( *iter ) && iter != end ) {

        ++iter;
      }
    }
    this->verify();
  };

  /**
   *  @brief Print the NDI table
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->metadata_.print( iter );
    this->primary_structure_.print( iter );
    this->weights_.print( iter );
    this->total_.print( iter );
    this->xs_.print( iter );
    this->product_multiplicities_all_.print( iter );
    this->product_multiplicities_few_.print( iter );
    this->product_multiplicities_rmo_.print( iter );
    base::Keyword( "end" ).print( iter );
  };
};

} // NDItk namespace
} // njoy namespace

#endif
