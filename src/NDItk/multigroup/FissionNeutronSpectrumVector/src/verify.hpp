/**
 *  @brief Verify the fission neutron spectrum vector values
 *
 *  The following verification tests are performed:
 *    - there is at least one value
 *
 *  @param[in] values    the fission neutron spectrum values to be verified
 */
template < typename Range >
static void verify( const Range& values ) {

  if ( values.size() < 1 ) {

    Log::error( "Expected at least one fission neutron spectrum vector value, found {}",
                values.size() );
    throw std::exception();
  }
}
