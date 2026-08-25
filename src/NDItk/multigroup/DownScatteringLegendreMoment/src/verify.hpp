/**
 *  @brief Verify the Legendre moment values
 *
 *  The following verification tests are performed:
 *    - there are at least two values
 *    - the matrix is the correct size
 *
 *  @param[in] data     the data values in the Legendre moment subrecord
 *  @param[in] groups   the number of groups
 */
template < typename Range >
static void verify( const Range& data, std::size_t groups ) {

  if ( data.size() < 2 ) {

    Log::error( "Expected at least 2 data values consisting of a Legendre order\n"
                "and at least one matrix value" );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }

  if ( data.size() - 1 != groups * ( groups + 1 ) / 2 ) {

    Log::error( "Expected a compressed down scatter matrix for {} groups, "
                "or with {} elements", groups, groups * ( groups + 1 ) / 2 );
    Log::info( "Found {} matrix elements", data.size() - 1 );
    throw std::exception();
  }
}
