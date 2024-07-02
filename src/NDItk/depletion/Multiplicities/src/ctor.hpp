/**
 *  @brief Constructor
 *
 *  @param[in] reaction          the reaction number
 *  @param[in] products          the reaction product identifiers
 *  @param[in] multiplicities    the multiplicity values
 */
Multiplicities( int reaction, std::vector< int > products,
                std::vector< int > multiplicities ) :
  Parent( generateData( reaction, std::move( products ), std::move( multiplicities ) ) ) {

  verify( this->values() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the cross section
 *  @param[in] end      the end iterator of the cross section
 */
Multiplicities( Iterator begin, Iterator end ) :
  Parent( begin, end ) {

  verify( this->values() );
}
