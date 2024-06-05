/**
 *  @brief Generate the record's data vector
 *
 *  @param[in] moments    the Legendre moments
 */
static std::vector< double > generateData( std::vector< LegendreMoment > moments ) {

  // verify the data
  verify( moments );

  // generate the data vector
  std::vector< double > data;
  const auto size = moments.front().size();
  data.reserve( moments.size() * size );
  for ( unsigned int i = 0; i < moments.size(); ++i ) {

    data.insert( data.end(), moments[i].begin(), moments[i].end() );
  }
  return data;
}
