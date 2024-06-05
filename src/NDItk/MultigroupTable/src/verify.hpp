/**
 *  @brief Verify the multigroup data
 *
 *  The following verification tests are performed:
 *    - the number of groups accross the data is consistent
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
               this->reactionCrossSections().empty() ? "absent" : "present" );
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

    const auto types = this->metadata().numberOutgoingParticles().value();
    if ( types > 0 ) {

      if ( ( this->outgoingParticleTypes().numberOutgoingParticles() != types ) ||
           ( ! this->outgoingParticleTransportData().empty() && this->outgoingParticleTransportData().numberOutgoingParticles() != types ) ||
           ( this->outgoing_structure_.size() && this->outgoing_structure_.size() != types ) ||
           ( this->outgoing_production_.size() && this->outgoing_production_.size() != types ) ||
           ( this->outgoing_heating_.size() && this->outgoing_heating_.size() != types ) ||
           ( this->outgoing_kerma_.size() && this->outgoing_kerma_.size() != types ) ) {

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
