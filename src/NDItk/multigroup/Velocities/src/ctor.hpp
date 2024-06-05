/**
 *  @brief Default constructor
 */
Velocities() : RealListRecord( base::Keyword( "vel" ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] values    the velocity values
 */
Velocities( std::vector< double > values ) :
    RealListRecord( base::Keyword( "vel" ), std::move( values ) ) {

  verify( this->values() );
}
