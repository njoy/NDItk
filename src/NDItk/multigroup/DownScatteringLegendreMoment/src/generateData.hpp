/**
 *  @brief Generate the subrecord's data vector
 *
 *  @param[in] order     the Legendre order of the moment
 *  @param[in] values    the matrix values
 */
static std::vector< double >
generateData( int order, std::vector< double > values ) {

  std::vector< double > data( std::move( values ) );
  data.insert( data.begin(), static_cast< double >( order ) );
  return data;
}
