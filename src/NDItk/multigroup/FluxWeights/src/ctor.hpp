/**
 *  @brief Default constructor
 */
FluxWeights() : RealListRecord( base::Keyword( "wgts" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] values    the flux weight values
 */
FluxWeights( std::vector< double > values ) :
    RealListRecord( base::Keyword( "wgts" ), std::move( values ) ) {

  verify( this->values() );
}
