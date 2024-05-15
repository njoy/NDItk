/**
 *  @brief Verify the multigroup data
 *
 *  The following verification tests are performed:
 *    - the number of groups accross the data is consistent
 */
void verify() {

  // consistent group structure
  const auto groups = this->metadata().numberGroups().value();
  if ( ( this->primaryGroupBoundaries().numberGroups() != groups ) ||
       ( this->velocities().numberGroups() != groups ) ||
       ( this->fluxWeights().numberGroups() != groups ) ||
       ( ( ! this->totalCrossSection().empty() ) && this->totalCrossSection().numberGroups() != groups ) ||
       ( this->reactionCrossSections().numberGroups() != groups ) ) {

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
    throw std::exception();
  }
};
