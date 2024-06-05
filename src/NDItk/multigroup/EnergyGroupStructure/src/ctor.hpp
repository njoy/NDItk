/**
 *  @brief Default constructor for the primary group structure
 */
EnergyGroupStructure() : RealListRecord( base::Keyword( "e_bounds" ) ) {}

/**
 *  @brief Default constructor for a secondary particle group structure
 *
 *  @param[in] particle    the secondary particle identifier
 */
EnergyGroupStructure( unsigned int particle ) :
    RealListRecord( base::Keyword( "e_bounds", particle ) ) {}

/**
 *  @brief Constructor for the primary group structure
 *
 *  @param[in] boundaries    the group structure boundary values
 */
EnergyGroupStructure( std::vector< double > values ) :
    RealListRecord( base::Keyword( "e_bounds" ), std::move( values ) ) {

  verify( this->values() );
}

/**
 *  @brief Constructor for a secondary particle group structure
 *
 *  @param[in] particle    the secondary particle identifier
 *  @param[in] values      the group structure boundary values
 */
EnergyGroupStructure( unsigned int particle, std::vector< double > values ) :
    RealListRecord( base::Keyword( "e_bounds", particle ),
                    std::move( values ) ) {

  verify( this->values() );
}
