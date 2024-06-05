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
    product_multiplicities_all_( depletion::ReactionMultiplicityType::All ),
    product_multiplicities_few_( depletion::ReactionMultiplicityType::Few ),
    product_multiplicities_rmo_( depletion::ReactionMultiplicityType::RMO ),
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
                 multigroup::FluxWeights weigths,
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
    weights_( std::move( weigths ) ),
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
