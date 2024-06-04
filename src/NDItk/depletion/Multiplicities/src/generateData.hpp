/**
 *  @brief Generate the subrecord's data vector
 *
 *  @param[in] reaction          the reaction number
 *  @param[in] products          the reaction product identifiers
 *  @param[in] multiplicities    the multiplicity values
 */
static std::vector< int >
generateData( int reaction, std::vector< int > products,
              std::vector< int > multiplicities ) {

  auto size = products.size();
  if ( multiplicities.size() != size ) {

    Log::error( "The number of reaction product identifiers and multiplicities "
                "is inconsistent" );
    Log::info( "Found {} reaction product identifiers", products.size() );
    Log::info( "Found {} multiplicity values", multiplicities.size() );
    throw std::exception();
  }
  std::vector< int > data = { reaction, static_cast< int >( size ) };
  for ( unsigned int i = 0; i < size; ++i ) {

    data.push_back( products[i] );
    data.push_back( multiplicities[i] );
  }
  return data;
}
