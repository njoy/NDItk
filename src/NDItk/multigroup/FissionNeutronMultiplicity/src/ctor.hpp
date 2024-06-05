/**
 *  @brief Default constructor
 */
FissionNeutronMultiplicity() : RealListRecord( base::Keyword( "nu" ) ) {}

/**
 *  @brief Default constructor
 */
FissionNeutronMultiplicity( FissionType type ) : RealListRecord( base::Keyword( "nu", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] values    the fission neutron multiplicity values
 */
FissionNeutronMultiplicity( FissionType type,
                            std::vector< double > values ) :
    RealListRecord( base::Keyword( "nu", type ), std::move( values ) ) {

  verify( this->values() );
}
