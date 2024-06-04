/**
 *  @brief Generate the record's data vector
 *
 *  @param[in] xs    the cross section data
 */
static std::vector< int > generateData( std::vector< Multiplicities > multiplicities ) {

  // verify the data
  verify( multiplicities );

  // generate the data vector
  std::vector< int > data;
  for ( unsigned int i = 0; i < multiplicities.size(); ++i ) {

    data.insert( data.end(), multiplicities[i].begin(), multiplicities[i].end() );
  }
  return data;
}
