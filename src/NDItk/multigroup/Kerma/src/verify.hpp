/**
 *  @brief Verify the kerma values
 *
 *  The following verification tests are performed:
 *    - there is at least one value
 *
 *  @param[in] values    the kerma values to be verified
 */
template < typename Range >
static void verify( const Range& values ) {

  if ( values.size() < 1 ) {

    Log::error( "Expected at least one kerma value, found {}",
                values.size() );
    throw std::exception();
  }
}
