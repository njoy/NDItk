/**
 *  @brief Read the record data (down scattering matrix)
 *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input
 *  @param[in,out] groups      the number of energy groups
 *  @param[in,out] number      the number of moments
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end, unsigned int groups,
           unsigned int number ) {

  // read in the data
  this->groups_ = groups;
  this->number_moments_ = number;
  base::RealListRecord::read( iter, end, number * ( 1 + groups * ( groups + 1 ) / 2 ) );
  this->generateBlocks();

  // verify
  verify( this->moments() );
};
