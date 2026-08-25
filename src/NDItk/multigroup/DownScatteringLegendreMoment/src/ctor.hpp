/**
 *  @brief Constructor
 *
 *  @param[in] order      the Legendre order of the moment
 *  @param[in] values     the compressed down scatter matrix values
 *  @param[in] groups     the number of groups
 */
DownScatteringLegendreMoment( int order, std::vector< double > values,
                              std::size_t groups ) :
  Parent( generateData( order, std::move( values ) ) ),
  groups_( groups ) {

  verify( this->values(), this->numberGroups() );
  this->matrix_ = generateMatrix( this->values(), this->numberGroups() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] begin      the begin iterator of the moment data
 *  @param[in] end        the end iterator of the moment data
 *  @param[in] groups     the number of groups
 */
DownScatteringLegendreMoment( Iterator begin, Iterator end,
                              std::size_t groups ) :
  Parent( begin, end ),
  groups_( groups ) {

  verify( this->values(), this->numberGroups() );
  this->matrix_ = generateMatrix( this->values(), this->numberGroups() );
}
