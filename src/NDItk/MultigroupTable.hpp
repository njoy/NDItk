#ifndef NJOY_NDITK_MULTIGROUP
#define NJOY_NDITK_MULTIGROUP

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/multigroup/ReactionMultiplicities.hpp"
#include "NDItk/multigroup/FissionType.hpp"
#include "NDItk/multigroup/Metadata.hpp"
#include "NDItk/multigroup/EnergyGroupStructure.hpp"
#include "NDItk/multigroup/Velocities.hpp"
#include "NDItk/multigroup/FluxWeights.hpp"
#include "NDItk/multigroup/ReactionCrossSections.hpp"
#include "NDItk/multigroup/TotalCrossSection.hpp"
#include "NDItk/multigroup/AverageFissionEnergyRelease.hpp"
#include "NDItk/multigroup/FissionNeutronMultiplicity.hpp"
#include "NDItk/multigroup/FissionNeutronProduction.hpp"
#include "NDItk/multigroup/FissionNeutronSpectrumVector.hpp"
#include "NDItk/multigroup/FissionNeutronSpectrumMatrix.hpp"
#include "NDItk/multigroup/OutgoingParticleTypes.hpp"
#include "NDItk/multigroup/OutgoingParticleTransportData.hpp"
#include "NDItk/multigroup/HeatingNumbers.hpp"
#include "NDItk/multigroup/Kerma.hpp"
#include "NDItk/multigroup/ScatteringMatrix.hpp"
#include "NDItk/multigroup/DownScatteringMatrix.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A multigroup neutron and photon table
 */
class MultigroupTable {

  /* fields */

  multigroup::Metadata metadata_;
  multigroup::EnergyGroupStructure primary_structure_;
  multigroup::Velocities velocities_;
  multigroup::FluxWeights weights_;
  multigroup::TotalCrossSection total_;
  multigroup::ReactionCrossSections xs_;
  multigroup::ScatteringMatrix scattering_;
  multigroup::AverageFissionEnergyRelease release_;
  multigroup::FissionNeutronMultiplicity nubar_prompt_;
  multigroup::FissionNeutronMultiplicity nubar_delayed_;
  multigroup::FissionNeutronMultiplicity nubar_total_;
  multigroup::FissionNeutronProduction production_prompt_;
  multigroup::FissionNeutronProduction production_delayed_;
  multigroup::FissionNeutronProduction production_total_;
  multigroup::FissionNeutronSpectrumVector chi_vector_prompt_;
  multigroup::FissionNeutronSpectrumVector chi_vector_delayed_;
  multigroup::FissionNeutronSpectrumVector chi_vector_total_;
  multigroup::FissionNeutronSpectrumMatrix chi_matrix_prompt_;
  multigroup::FissionNeutronSpectrumMatrix chi_matrix_delayed_;
  multigroup::FissionNeutronSpectrumMatrix chi_matrix_total_;
  multigroup::HeatingNumbers primary_heating_;
  multigroup::Kerma primary_kerma_;
  multigroup::ReactionMultiplicities product_multiplicities_all_;
  multigroup::ReactionMultiplicities product_multiplicities_few_;
  multigroup::ReactionMultiplicities product_multiplicities_rmo_;
  multigroup::OutgoingParticleTypes outgoing_particles_;
  multigroup::OutgoingParticleTransportData outgoing_zaids_;
  std::vector< multigroup::EnergyGroupStructure > outgoing_structure_;
  std::vector< multigroup::ScatteringMatrix > outgoing_production_;
  std::vector< multigroup::HeatingNumbers > outgoing_heating_;
  std::vector< multigroup::Kerma > outgoing_kerma_;

  /* auxiliary functions */

  static std::map< unsigned int, unsigned int >
  generateOutgoingStructureMetadata( const std::vector< multigroup::EnergyGroupStructure >& outgoing ) {

    std::map< unsigned int, unsigned int > metadata;
    for ( const auto& entry : outgoing ) {

      unsigned int particle = entry.particle().value();
      if ( metadata.find( particle ) != metadata.end() ) {

        Log::error( "Found duplicate outgoing group structure for particle \'{}\'", particle );
        throw std::exception();
      }
      metadata[ particle ] = entry.numberGroups();
    }
    return metadata;
  }

  static std::map< unsigned int, unsigned int >
  generateOutgoingLegendreOrderMetadata( const std::vector< multigroup::ScatteringMatrix >& production ) {

    std::map< unsigned int, unsigned int > metadata;
    for ( const auto& entry : production ) {

      unsigned int particle = entry.particle().value();
      if ( metadata.find( particle ) != metadata.end() ) {

        Log::error( "Found duplicate number of Legendre moments for outgoing particle \'{}\'", particle );
        throw std::exception();
      }
      metadata[ particle ] = entry.numberLegendreMoments();
    }
    return metadata;
  }

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

  template< typename Iterator >
  void readOutgoingStructure( const std::string& key, Iterator& iter, const Iterator& end ) {

    base::Keyword secondary( key );
    unsigned int particle = secondary.particle().value();
    if ( this->metadata_.numberOutgoingGroups( particle ).has_value() ) {

      auto pos = std::lower_bound( this->outgoing_structure_.begin(),
                                   this->outgoing_structure_.end(),
                                   particle,
                                   [] ( auto&& left, auto&& right ) {

                                     return left.particle() < right;
                                   } );
      if ( pos != this->outgoing_structure_.end() ) {

        if ( pos->particle() == particle ) {

          Log::error( "Duplicate keyword found: \'{}\'", secondary.keyword() );
          throw std::exception();
        }
      }
      pos = this->outgoing_structure_.insert( pos, multigroup::EnergyGroupStructure( particle ) );
      readRecord( *pos, iter, end, this->metadata_.numberOutgoingGroups( particle ).value() + 1 );
    }
    else {

      Log::error( "Metadata required for the \'{}\' record was not found", secondary.keyword() );
      Log::info( "Required metadata is missing: number of groups in the outgoing group structure" );
      throw std::exception();
    }
  }

  template< typename Iterator >
  void readOutgoingProductionMatrix( const std::string& key, Iterator& iter, const Iterator& end ) {

    base::Keyword secondary( key );
    unsigned int particle = secondary.particle().value();
    if ( this->metadata_.numberGroups().has_value() &&
         this->metadata_.numberOutgoingGroups( particle ).has_value() &&
         this->metadata_.numberOutgoingLegendreMoments( particle ).has_value() ) {

      auto pos = std::lower_bound( this->outgoing_production_.begin(),
                                   this->outgoing_production_.end(),
                                   particle,
                                   [] ( auto&& left, auto&& right ) {

                                     return left.particle() < right;
                                   } );
      if ( pos != this->outgoing_production_.end() ) {

        if ( pos->particle() == particle ) {

          Log::error( "Duplicate keyword found: \'{}\'", secondary.keyword() );
          throw std::exception();
        }
      }
      pos = this->outgoing_production_.insert( pos, multigroup::ScatteringMatrix( particle ) );
      readRecord( *pos, iter, end,
                  this->metadata_.numberGroups().value(),
                  this->metadata_.numberOutgoingGroups( particle ).value(),
                  this->metadata_.numberOutgoingLegendreMoments( particle ).value() );
    }
    else {

      Log::error( "Metadata required for the \'{}\' record was not found", secondary.keyword() );
      if ( ! this->metadata_.numberGroups().has_value() ) {

        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
      }
      if ( ! this->metadata_.numberOutgoingGroups( particle ).has_value() ) {

        Log::info( "Required metadata is missing: number of groups in the outgoing group structure" );
      }
      if ( ! this->metadata_.numberOutgoingLegendreMoments( particle ).has_value() ) {

        Log::info( "Required metadata is missing: number of Legendre moments for the outgoing particle" );
      }
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

  template< typename Record, typename Iterator >
  void readOutgoingData( const std::string& key, std::vector< Record >& vector,
                         Iterator& iter, const Iterator& end ) {

    base::Keyword secondary( key );
    unsigned int particle = secondary.particle().value();
    if ( this->metadata_.numberGroups().has_value() ) {

      auto pos = std::lower_bound( vector.begin(),
                                   vector.end(),
                                   particle,
                                   [] ( auto&& left, auto&& right ) {

                                     return left.particle() < right;
                                   } );
      if ( pos != vector.end() ) {

        if ( pos->particle() == particle ) {

          Log::error( "Duplicate keyword found: \'{}\'", secondary.keyword() );
          throw std::exception();
        }
      }
      pos = vector.insert( pos, Record( particle ) );
      readRecord( *pos, iter, end, this->metadata_.numberGroups().value() );
    }
    else {

      Log::error( "Metadata required for the \'{}\' record was not found", secondary.keyword() );
      Log::info( "Required metadata is missing: number of groups in the primary group structure" );
      throw std::exception();
    }
  }

  /**
   *  @brief Resolve deprecated records
   *
   *  @param[in] downScattering   the deprecated DownScatteringMatrix
   */
  void resolveDeprecation( const multigroup::DownScatteringMatrix& downScattering ) {

    if ( ! downScattering.empty() ) {

      if ( ! this->scattering_.empty() ) {

        Log::error( "A \'{}\' and a \'{}\' keyword cannot both be used in a multigroup table",
                    downScattering.keyword(), this->scattering_.keyword() );
        throw std::exception();
      }
      this->scattering_ = downScattering.toScatteringMatrix();
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
         this->velocities().empty() ||
         this->fluxWeights().empty() ||
         this->totalCrossSection().empty() ||
         this->reactionCrossSections().empty() ||
         this->scatteringMatrix().empty() ) {

      Log::error( "One or more required records are not found in the table" );
      Log::info( "Primary group structure record: {}",
                 this->primaryGroupBoundaries().empty() ? "absent" : "present" );
      Log::info( "Velocity record: {}",
                 this->velocities().empty() ? "absent" : "present" );
      Log::info( "Flux weight record: {}",
                 this->fluxWeights().empty() ? "absent" : "present" );
      Log::info( "Total cross section record: {}",
                 this->totalCrossSection().empty() ? "absent" : "present" );
      Log::info( "Reaction cross sections record: {}",
                 this->reactionCrossSections().empty() ? "absent" : "present" );
      Log::info( "Scattering matrix record: {}",
                 this->scatteringMatrix().empty() ? "absent" : "present" );
      throw std::exception();
    }

    // consistent group structure: primary
    const auto groups = this->metadata().numberGroups().value();
    bool bTestScatteringMatrix = false;
    for ( auto&& moment : this->scatteringMatrix().moments() ) {

      if ( moment.numberPrimaryGroups() != groups ) {

        bTestScatteringMatrix = true;
      }
    }
    if ( ( this->primaryGroupBoundaries().numberGroups() != groups ) ||
         ( this->velocities().numberGroups() != groups ) ||
         ( this->fluxWeights().numberGroups() != groups ) ||
         ( ( ! this->totalCrossSection().empty() )
           && this->totalCrossSection().numberGroups() != groups ) ||
         ( this->reactionCrossSections().numberGroups() != groups ) ||
         ( bTestScatteringMatrix ) ||
         ( ( ! this->primaryHeatingNumbers().empty() )
           && this->primaryHeatingNumbers().numberGroups() != groups ) ||
         ( ( ! this->primaryKerma().empty() )
           && this->primaryKerma().numberGroups() != groups ) ) {

      Log::error( "Found inconsistent number of primary groups across the table" );
      Log::info( "Number of primary groups in the metadata: {}",
                 this->metadata().numberGroups().value() );
      Log::info( "Number of primary groups in the primary group structure: {}",
                 this->primaryGroupBoundaries().numberGroups() );
      Log::info( "Number of primary groups in the velocities: {}",
                 this->velocities().numberGroups() );
      Log::info( "Number of primary groups in the flux weights: {}",
                 this->fluxWeights().numberGroups() );
      if ( ! this->totalCrossSection().empty() ) {

        Log::info( "Number of primary groups in the total cross section: {}",
                   this->totalCrossSection().numberGroups() );
      }
      Log::info( "Number of primary groups in the reaction cross section data: {}",
                 this->reactionCrossSections().numberGroups() );
      for ( auto&& moment : this->scatteringMatrix().moments() ) {

        Log::info( "Number of primary groups in moment {} of the scattering matrix: {}",
                   moment.order(), moment.numberPrimaryGroups() );
      }
      if ( ! this->primaryHeatingNumbers().empty() ) {

        Log::info( "Number of primary groups in the heating numbers: {}",
                   this->primaryHeatingNumbers().numberGroups() );
      }
      if ( ! this->primaryKerma().empty() ) {

        Log::info( "Number of primary groups in the kerma values: {}",
                   this->primaryKerma().numberGroups() );
      }
      throw std::exception();
    }

    // secondary particles
    if ( this->metadata().numberOutgoingParticles().has_value() ) {

      const auto number = this->metadata().numberOutgoingParticles().value();
      if ( number > 0 ) {

        if ( ( this->outgoingParticleTypes().numberOutgoingParticles() != number ) ||
             ( ! this->outgoingParticleTransportData().empty() && this->outgoingParticleTransportData().numberOutgoingParticles() != number ) ||
             ( this->outgoing_structure_.size() && this->outgoing_structure_.size() != number ) ||
             ( this->outgoing_production_.size() && this->outgoing_production_.size() != number ) ||
             ( this->outgoing_heating_.size() && this->outgoing_heating_.size() != number ) ||
             ( this->outgoing_kerma_.size() && this->outgoing_kerma_.size() != number ) ) {

          Log::error( "Found inconsistent number of outgoing particle types across the table" );
          Log::info( "Number of outgoing particles in the metadata: {}",
                     this->metadata().numberOutgoingParticles().value() );
          Log::info( "Number of types in the outgoing particle types: {}",
                     this->outgoingParticleTypes().numberOutgoingParticles() );
          Log::info( "Number of types in the outgoing transport data: {}",
                     this->outgoingParticleTransportData().numberOutgoingParticles() );
          Log::info( "Number of types in the outgoing group structures: {}",
                     this->outgoing_structure_.size() );
          Log::info( "Number of types in the outgoing production matrices: {}",
                     this->outgoing_production_.size() );
          Log::info( "Number of types in the outgoing heating numbers: {}",
                     this->outgoing_heating_.size() );
          Log::info( "Number of types in the outgoing kerma values: {}",
                     this->outgoing_kerma_.size() );
          throw std::exception();
        }
      }
    }
  };

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  MultigroupTable() :
      metadata_(), primary_structure_(),
      velocities_(), weights_(), total_(), xs_(), scattering_(),
      release_(),
      nubar_prompt_( multigroup::FissionType::Prompt ),
      nubar_delayed_( multigroup::FissionType::Delayed ),
      nubar_total_( multigroup::FissionType::Total ),
      chi_vector_prompt_( multigroup::FissionType::Prompt ),
      chi_vector_delayed_( multigroup::FissionType::Delayed ),
      chi_vector_total_( multigroup::FissionType::Total ),
      chi_matrix_prompt_( multigroup::FissionType::Prompt ),
      chi_matrix_delayed_( multigroup::FissionType::Delayed ),
      chi_matrix_total_( multigroup::FissionType::Total ),
      primary_heating_(), primary_kerma_(),
      product_multiplicities_all_( multigroup::ReactionMultiplicityType::All ),
      product_multiplicities_few_( multigroup::ReactionMultiplicityType::Few ),
      product_multiplicities_rmo_( multigroup::ReactionMultiplicityType::RMO ),
      outgoing_particles_(), outgoing_zaids_(),
      outgoing_structure_(), outgoing_production_(),
      outgoing_heating_(), outgoing_kerma_() {}

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
   *  @param[in] velocities        the group velocities
   *  @param[in] weights           the flux weights
   *  @param[in] total_xs          the total cross section
   *  @param[in] reaction_xs       the reaction cross section data
   *  @param[in] scattering        the scattering matrix
   *  @param[in] information       the table information line (optional)
   *  @param[in] source            the source date (optional)
   *  @param[in] weight            the atomic weight of the target (optional)
   *  @param[in] fission_q         the average fission energy release data (optional)
   *  @param[in] types             the outgoing particle types (optional)
   *  @param[in] transport         the outgoing particle transport data (optional)
   *  @param[in] production        the outgoing production matrices (optional)
   *  @param[in] primaryHeating    the primary particle heating numbers (optional)
   *  @param[in] outgoingHeating   the outgoing particles' heating numbers (optional)
   *  @param[in] primaryKerma      the primary particle kerma (optional)
   *  @param[in] outgoingKerma     the outgoing particle kermas (optional)
   */
  MultigroupTable( std::string zaid, std::string libname,
                   std::string process, double awr, double temperature,
                   double dilution,
                   multigroup::EnergyGroupStructure structure,
                   std::vector< multigroup::EnergyGroupStructure > outgoing,
                   multigroup::Velocities velocities,
                   multigroup::FluxWeights weights,
                   multigroup::TotalCrossSection total_xs,
                   multigroup::ReactionCrossSections reaction_xs,
                   multigroup::ScatteringMatrix scattering,
                   std::optional< std::string > information = std::nullopt,
                   std::optional< std::string > source = std::nullopt,
                   std::optional< double > weight = std::nullopt,
                   std::optional< multigroup::AverageFissionEnergyRelease > fission_q = std::nullopt,
                   std::optional< multigroup::OutgoingParticleTypes > types = std::nullopt,
                   std::optional< multigroup::OutgoingParticleTransportData > transport = std::nullopt,
                   std::vector< multigroup::ScatteringMatrix > production = {},
                   std::optional< multigroup::HeatingNumbers > primaryHeating = std::nullopt,
                   std::vector< multigroup::HeatingNumbers > outgoingHeating = {},
                   std::optional< multigroup::Kerma > primaryKerma = std::nullopt,
                   std::vector< multigroup::Kerma > outgoingKerma = {} ) :
      metadata_( std::move( zaid ), std::move( libname ),
                 std::move( process ), awr, temperature, dilution,
                 structure.numberGroups(), reaction_xs.numberReactions(),
                 scattering.numberLegendreMoments(), generateOutgoingStructureMetadata( outgoing ),
                 generateOutgoingLegendreOrderMetadata( production ),
                 std::move( information ), std::move( source ), std::move( weight ),
                 std::nullopt, std::nullopt ),
      primary_structure_( std::move( structure ) ),
      velocities_( std::move( velocities ) ),
      weights_( std::move( weights ) ),
      total_( std::move( total_xs ) ),
      xs_( std::move( reaction_xs ) ),
      scattering_( std::move( scattering ) ),
      outgoing_structure_( std::move( outgoing ) ),
      outgoing_production_( std::move( production ) ),
      outgoing_heating_( std::move( outgoingHeating ) ),
      outgoing_kerma_( std::move( outgoingKerma ) ) {

    if ( fission_q.has_value() ) {

      this->release_ = std::move( fission_q.value() );
    }
    if ( primaryHeating.has_value() ) {

      this->primary_heating_ = std::move( primaryHeating.value() );
    }
    if ( primaryKerma.has_value() ) {

      this->primary_kerma_ = std::move( primaryKerma.value() );
    }
    if ( types.has_value() ) {

      this->outgoing_particles_ = std::move( types.value() );
    }
    if ( transport.has_value() ) {

      this->outgoing_zaids_ = std::move( transport.value() );
    }
    this->verify();
  }

  /* methods */

  /**
   *  @brief Return the metadata of the table
   */
  const multigroup::Metadata& metadata() const { return this->metadata_; }

  /**
   *  @brief Return the primary group structure record
   */
  const multigroup::EnergyGroupStructure& primaryGroupBoundaries() const {

    return this->primary_structure_;
  }

  /**
   *  @brief Return the velocity record
   */
  const multigroup::Velocities& velocities() const {

    return this->velocities_;
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
   *  @brief Return the scattering matrix record
   */
  const multigroup::ScatteringMatrix& scatteringMatrix() const {

    return this->scattering_;
  }

  /**
   *  @brief Return the average fission energy release record
   */
  const multigroup::AverageFissionEnergyRelease&
  averageFissionEnergyRelease() const {

    return this->release_;
  }

  /**
   *  @brief Return the fission neutron multiplicity record for the requested fission type
   */
  const multigroup::FissionNeutronMultiplicity&
  fissionNeutronMultiplicity( const multigroup::FissionType& type ) const {

    switch ( type ) {

      case multigroup::FissionType::Prompt  : return this->nubar_prompt_;
      case multigroup::FissionType::Delayed : return this->nubar_delayed_;
      case multigroup::FissionType::Total   : return this->nubar_total_;
      default : {

        throw std::runtime_error( "This code is unreachable, contact a developer" );
      }
    }
  }

  /**
   *  @brief Return the fission neutron production record for the requested fission type
   */
  const multigroup::FissionNeutronProduction&
  fissionNeutronProduction( const multigroup::FissionType& type ) const {

    switch ( type ) {

      case multigroup::FissionType::Prompt  : return this->production_prompt_;
      case multigroup::FissionType::Delayed : return this->production_delayed_;
      case multigroup::FissionType::Total   : return this->production_total_;
      default : {

        throw std::runtime_error( "This code is unreachable, contact a developer" );
      }
    }
  }

  /**
   *  @brief Return the fission neutron spectrum vector record for the requested fission type
   */
  const multigroup::FissionNeutronSpectrumVector&
  fissionNeutronSpectrumVector( const multigroup::FissionType& type ) const {

    switch ( type ) {

      case multigroup::FissionType::Prompt  : return this->chi_vector_prompt_;
      case multigroup::FissionType::Delayed : return this->chi_vector_delayed_;
      case multigroup::FissionType::Total   : return this->chi_vector_total_;
      default : {

        throw std::runtime_error( "This code is unreachable, contact a developer" );
      }
    }
  }

  /**
   *  @brief Return the fission neutron spectrum matrix record for the requested fission type
   */
  const multigroup::FissionNeutronSpectrumMatrix&
  fissionNeutronSpectrumMatrix( const multigroup::FissionType& type ) const {

    switch ( type ) {

      case multigroup::FissionType::Prompt  : return this->chi_matrix_prompt_;
      case multigroup::FissionType::Delayed : return this->chi_matrix_delayed_;
      case multigroup::FissionType::Total   : return this->chi_matrix_total_;
      default : {

        throw std::runtime_error( "This code is unreachable, contact a developer" );
      }
    }
  }

  /**
   *  @brief Return the primary heating numbers record
   */
  const multigroup::HeatingNumbers& primaryHeatingNumbers() const {

    return this->primary_heating_;
  }

  /**
   *  @brief Return the primary kerma record
   */
  const multigroup::Kerma& primaryKerma() const {

    return this->primary_kerma_;
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
   *  @brief Return the outgoing particle types record
   */
  const multigroup::OutgoingParticleTypes&
  outgoingParticleTypes() const {

    return this->outgoing_particles_;
  }

  /**
   *  @brief Return the outgoing particle transport data record
   */
  const multigroup::OutgoingParticleTransportData&
  outgoingParticleTransportData() const {

    return this->outgoing_zaids_;
  }

  /**
   *  @brief Return the group structure record for an outgoing particle
   */
  const multigroup::EnergyGroupStructure&
  outgoingGroupBoundaries( unsigned int particle ) const {

    auto pos = std::lower_bound( this->outgoing_structure_.begin(),
                                 this->outgoing_structure_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_structure_.end() ) {

      if ( pos->particle() == particle ) {

        return *pos;
      }
    }
    Log::error( "The requested outgoing particle \'{}\' has no outgoing group structure", particle );
    throw std::exception();
  }

  /**
   *  @brief Return the production matrix record for an outgoing particle
   */
  const multigroup::ScatteringMatrix&
  outgoingProductionMatrix( unsigned int particle ) const {

    auto pos = std::lower_bound( this->outgoing_production_.begin(),
                                 this->outgoing_production_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_production_.end() ) {

      if ( pos->particle() == particle ) {

        return *pos;
      }
    }
    Log::error( "The requested outgoing particle \'{}\' has no outgoing production matrix", particle );
    throw std::exception();
  }

  /**
   *  @brief Return the heating numbers record for an outgoing particle
   */
  const multigroup::HeatingNumbers&
  outgoingHeatingNumbers( unsigned int particle ) const {

    auto pos = std::lower_bound( this->outgoing_heating_.begin(),
                                 this->outgoing_heating_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_heating_.end() ) {

      if ( pos->particle() == particle ) {

        return *pos;
      }
    }
    Log::error( "The requested outgoing particle \'{}\' has no associated "
                "heating numbers", particle );
    throw std::exception();
  }

  /**
   *  @brief Return the kerma record for an outgoing particle
   */
  const multigroup::Kerma&
  outgoingKerma( unsigned int particle ) const {

    auto pos = std::lower_bound( this->outgoing_kerma_.begin(),
                                 this->outgoing_kerma_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_kerma_.end() ) {

      if ( pos->particle() == particle ) {

        return *pos;
      }
    }
    Log::error( "The requested outgoing particle \'{}\' has no associated "
                "kerma record", particle );
    throw std::exception();
  }

  /**
   *  @brief Read the table data
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    // deprecated records
    multigroup::DownScatteringMatrix downScattering;

    std::string keyword;
    while ( ( keyword != "end" ) && ( iter != end ) ) {

      keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );

      // metadata
      if ( this->metadata_.isMetadataKey( keyword ) ) {

        this->metadata_.read( keyword, iter, end );
      }
      // primary and outgoing group structure keyword
      else if ( keyword.find( this->primary_structure_.keyword() ) == 0 ) {

        if ( keyword == this->primary_structure_.keyword() ) {

          readPrimaryStructure( iter, end );
        }
        else {

          readOutgoingStructure( keyword, iter, end );
        }
      }
      // velocities
      else if ( keyword == this->velocities_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->velocities_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
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
      // scattering matrix
      else if ( keyword == this->scattering_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() &&
             this->metadata_.numberLegendreMoments().has_value() ) {

          readRecord( this->scattering_, iter, end,
                      this->metadata_.numberGroups().value(),
                      this->metadata_.numberLegendreMoments().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          if ( ! this->metadata_.numberGroups().has_value() ) {

            Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          }
          if ( ! this->metadata_.numberLegendreMoments().has_value() ) {

            Log::info( "Required metadata is missing: number of Legendre moments" );
          }
          throw std::exception();
        }
      }
      else if ( keyword == downScattering.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() &&
             this->metadata_.numberLegendreMoments().has_value() ) {

          readRecord( downScattering, iter, end,
                      this->metadata_.numberGroups().value(),
                      this->metadata_.numberLegendreMoments().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          if ( ! this->metadata_.numberGroups().has_value() ) {

            Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          }
          if ( ! this->metadata_.numberLegendreMoments().has_value() ) {

            Log::info( "Required metadata is missing: number of Legendre moments" );
          }
          throw std::exception();
        }
      }
      // average fission energy release
      else if ( keyword == this->release_.keyword() ) {

        readRecord( this->release_, iter, end );
      }
      // prompt fission neutron multiplicity
      else if ( keyword == this->nubar_prompt_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->nubar_prompt_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // delayed fission neutron multiplicity
      else if ( keyword == this->nubar_delayed_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->nubar_delayed_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // total fission neutron multiplicity
      else if ( keyword == this->nubar_total_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->nubar_total_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // prompt fission neutron production
      else if ( keyword == this->production_prompt_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->production_prompt_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // delayed fission neutron production
      else if ( keyword == this->production_delayed_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->production_delayed_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // total fission neutron production
      else if ( keyword == this->production_total_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->production_total_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // prompt fission neutron spectrum vector
      else if ( keyword == this->chi_vector_prompt_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->chi_vector_prompt_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // delayed fission neutron spectrum vector
      else if ( keyword == this->chi_vector_delayed_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->chi_vector_delayed_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // total fission neutron spectrum vector
      else if ( keyword == this->chi_vector_total_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->chi_vector_total_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // prompt fission neutron spectrum matrix
      else if ( keyword == this->chi_matrix_prompt_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->chi_matrix_prompt_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // delayed fission neutron spectrum matrix
      else if ( keyword == this->chi_matrix_delayed_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->chi_matrix_delayed_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // total fission neutron spectrum matrix
      else if ( keyword == this->chi_matrix_total_.keyword() ) {

        if ( this->metadata_.numberGroups().has_value() ) {

          readRecord( this->chi_matrix_total_, iter, end, this->metadata_.numberGroups().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
          throw std::exception();
        }
      }
      // primary and outgoing heating keyword
      else if ( keyword.find( this->primary_heating_.keyword() ) == 0 ) {

        if ( keyword == this->primary_heating_.keyword() ) {

          readPrimaryData( this->primary_heating_, iter, end );
        }
        else {

          readOutgoingData( keyword, this->outgoing_heating_, iter, end );
        }
      }
      // primary and outgoing kerma keyword
      else if ( keyword.find( this->primary_kerma_.keyword() ) == 0 ) {

        if ( keyword == this->primary_kerma_.keyword() ) {

          readPrimaryData( this->primary_kerma_, iter, end );
        }
        else {

          readOutgoingData( keyword, this->outgoing_kerma_, iter, end );
        }
      }
      // outgoing particle types
      else if ( keyword == this->outgoing_particles_.keyword() ) {

        if ( this->metadata_.numberOutgoingParticles().has_value() ) {

          readRecord( this->outgoing_particles_, iter, end,
                      this->metadata_.numberOutgoingParticles().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of outgoing particle types" );
          throw std::exception();
        }
      }
      // outgoing particle transport data
      else if ( keyword == this->outgoing_zaids_.keyword() ) {

        if ( this->metadata_.numberOutgoingParticles().has_value() ) {

          readRecord( this->outgoing_zaids_, iter, end,
                      this->metadata_.numberOutgoingParticles().value() );
        }
        else {

          Log::error( "Metadata required for the \'{}\' record was not found", keyword );
          Log::info( "Required metadata is missing: number of outgoing particle types" );
          throw std::exception();
        }
      }
      // outgoing production matrices
      else if ( keyword.find( "pn_prod_full" ) == 0 ) {

        readOutgoingProductionMatrix( keyword, iter, end );
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
      while ( iter != end && std::isspace( *iter ) ) {

        ++iter;
      }
    }
    this->resolveDeprecation( downScattering );
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
    this->velocities_.print( iter );
    this->weights_.print( iter );
    this->total_.print( iter );
    this->xs_.print( iter );
    this->scattering_.print( iter );
    this->release_.print( iter );
    this->nubar_prompt_.print( iter );
    this->nubar_delayed_.print( iter );
    this->nubar_total_.print( iter );
    this->production_prompt_.print( iter );
    this->production_delayed_.print( iter );
    this->production_total_.print( iter );
    this->chi_vector_prompt_.print( iter );
    this->chi_vector_delayed_.print( iter );
    this->chi_vector_total_.print( iter );
    this->chi_matrix_prompt_.print( iter );
    this->chi_matrix_delayed_.print( iter );
    this->chi_matrix_total_.print( iter );
    this->primary_heating_.print( iter );
    this->primary_kerma_.print( iter );
    this->product_multiplicities_all_.print( iter );
    this->product_multiplicities_few_.print( iter );
    this->product_multiplicities_rmo_.print( iter );
    this->outgoing_particles_.print( iter );
    this->outgoing_zaids_.print( iter );
    for ( const auto& entry : this->outgoing_structure_ ) { entry.print( iter ); }
    for ( const auto& entry : this->outgoing_production_ ) { entry.print( iter ); }
    for ( const auto& entry : this->outgoing_heating_ ) { entry.print( iter ); }
    for ( const auto& entry : this->outgoing_kerma_ ) { entry.print( iter ); }
    base::Keyword( "end" ).print( iter );
  };
};

} // NDItk namespace
} // njoy namespace

#endif
