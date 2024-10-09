/**
 *  @brief Default constructor
 */
FissionNeutronMultiplicity() : RealListRecord( base::Keyword( "nu" ) ) {}

/**
 *  @brief Constructor for a fission type
 *
 *  @param[in] type    the fission type (prompt, delayed or total)
 */
FissionNeutronMultiplicity( FissionType type ) : RealListRecord( base::Keyword( "nu", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] type      the fission type (prompt, delayed or total)
 *  @param[in] values    the fission neutron multiplicity values
 */
FissionNeutronMultiplicity( FissionType type,
                            std::vector< double > values ) :
    RealListRecord( base::Keyword( "nu", type ), std::move( values ) ) {

  verify( this->values() );
}