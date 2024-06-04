/**
 *  @brief Verify the nu values
 *
 *  The following verification tests are performed:
 *    - there is at least one value
 *
 *  @param[in] values    the nu values to be verified
 */
template < typename Range >
static void verify( const Range& values ) {

  if ( values.size() < 1 ) {

    Log::error( "Expected at least one nu value, found {}",
                values.size() );
    throw std::exception();
  }
}
