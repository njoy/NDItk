/**
 *  @brief Verify the heating numbers
 *
 *  The following verification tests are performed:
 *    - there is at least one value
 *
 *  @param[in] values    the heating numbers to be verified
 */
template < typename Range >
static void verify( const Range& values ) {

  if ( values.size() < 1 ) {

    Log::error( "Expected at least one heating number, found {}",
                values.size() );
    throw std::exception();
  }
}
