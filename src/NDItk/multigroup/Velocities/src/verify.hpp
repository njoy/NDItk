/**
 *  @brief Verify the velocities
 *
 *  The following verification tests are performed:
 *    - there is at least one value
 *
 *  @param[in] values    the velocity values to be verified
 */
template < typename Range >
static void verify( const Range& values ) {

  if ( values.size() < 1 ) {

    Log::error( "Expected at least one velocity value, found {}",
                values.size() );
    throw std::exception();
  }
}
