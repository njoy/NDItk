/**
 *  @brief Default constructor
 */
FissionNeutronSpectrumVector() : RealListRecord( base::Keyword( "chi_vec" ) ) {}

/**
 *  @brief Default constructor
 */
FissionNeutronSpectrumVector( FissionType type ) : RealListRecord( base::Keyword( "chi_vec", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] values    the fission neutron spectrum vector values
 */
FissionNeutronSpectrumVector( FissionType type,
                              std::vector< double > values ) :
    RealListRecord( base::Keyword( "chi_vec", type ), std::move( values ) ) {

  verify( this->values() );
}
