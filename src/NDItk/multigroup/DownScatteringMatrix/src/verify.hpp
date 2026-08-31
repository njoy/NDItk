/**
 *  @brief Verify the down scattering matrix information
 *
 *  The following verification tests are performed:
 *    - there is at least one Legendre moment
 *    - the number of groups for each moment is the same
 *
 *  @param[in] moments   the moments to be verified
 */
template < typename Range >
static void verify( const Range& moments ) {

  if ( moments.size() < 1 ) {

    Log::error( "Expected at least one moment, found {}", moments.size() );
    throw std::exception();
  }

  const auto groups = moments.front().numberGroups();
  for ( unsigned int i = 0; i < moments.size(); ++i ) {

    if ( moments[i].numberGroups() != groups ) {

      Log::error( "Inconsistent number of groups detected for moment "
                  "with order \'{}\'", moments[i].order() );
      Log::info( "Expected number of groups: {}", groups );
      Log::info( "Found number of groups: {}", moments[i].numberGroups() );
      throw std::exception();
    }
  }
}
