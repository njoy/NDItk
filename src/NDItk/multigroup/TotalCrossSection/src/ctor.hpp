/**
 *  @brief Default constructor
 */
TotalCrossSection() : RealListRecord( base::Keyword( "sig_tot" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] values    the total cross section values
 */
TotalCrossSection( std::vector< double > values ) :
    RealListRecord( base::Keyword( "sig_tot" ), std::move( values ) ) {

  verify( this->values() );
}
