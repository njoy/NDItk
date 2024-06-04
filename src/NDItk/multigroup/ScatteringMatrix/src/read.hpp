/**
 *  @brief Read the record data (secondary particle production matrix)
 *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input
 *  @param[in,out] incident    the number of incident energy groups
 *  @param[in,out] outgoing    the number of outgoing energy groups
 *  @param[in,out] number      the number of moments
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end, unsigned int incident,
           unsigned int outgoing, unsigned int number ) {

  // read in the data
  this->incident_ = incident;
  this->outgoing_ = outgoing;
  this->number_moments_ = number;
  base::RealListRecord::read( iter, end, number * ( 1 + incident * outgoing ) );
  this->generateBlocks();

  // verify
  verify( this->moments() );
};

/**
 *  @brief Read the record data (scattering matrix)
 *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input
 *  @param[in,out] incident    the number of incident energy groups
 *  @param[in,out] number      the number of moments
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end, unsigned int incident,
           unsigned int number ) {

  read( iter, end, incident, incident, number );
};
