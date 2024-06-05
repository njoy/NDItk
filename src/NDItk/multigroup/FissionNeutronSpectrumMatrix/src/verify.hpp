/**
 *  @brief Verify the fission neutron spectrum vector values
 *
 *  The following verification tests are performed:
 *    - there is at least one value
 *
 *  @param[in] values    the production values to be verified
 */
template < typename Range >
static void verify( const Range& values ) {

  if ( values.size() < 1 ) {

    Log::error( "Expected at least one fission neutron spectrum matrix value, found {}",
                values.size() );
    throw std::exception();
  }
  unsigned int size = std::sqrt( values.size() );
  if ( values.size() != size * size ) {

    Log::error( "Expected an array of size {} but found {} whoich does not represent a matrix",
                size * size, values.size() );
    throw std::exception();
  }
}
