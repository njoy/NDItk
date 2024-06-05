/**
 *  @brief Default constructor
 */
FissionNeutronProduction() : RealListRecord( base::Keyword( "nu_sig_f" ) ) {}

/**
 *  @brief Default constructor
 */
FissionNeutronProduction( FissionType type ) : RealListRecord( base::Keyword( "nu_sig_f", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] values    the fission neutron production values
 */
FissionNeutronProduction( FissionType type,
                          std::vector< double > values ) :
    RealListRecord( base::Keyword( "nu_sig_f", type ), std::move( values ) ) {

  verify( this->values() );
}
