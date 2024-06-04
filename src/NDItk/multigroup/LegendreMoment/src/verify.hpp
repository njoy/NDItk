/**
 *  @brief Verify the cross section data values
 *
 *  The following verification tests are performed:
 *    - there are at least two values
 *    - the reaction identifier looks to be an integer
 *
 *  @param[in] data    the data values in the Legendre moment subrecord
 */
template < typename Range >
static void verify( const Range& data,
                    std::size_t incident, std::size_t outgoing ) {

  if ( data.size() < 2 ) {

    Log::error( "Expected at least 2 data values consisting of a Legendre order\n"
                "and at least one matrix value" );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }

  if ( data.size() - 1  != incident * outgoing ) {

    Log::error( "Expected a matrix of size {} by {}, or with {} elements",
                incident, outgoing, incident * outgoing );
    Log::info( "Found {} matrix elements", data.size() - 1 );
    throw std::exception();
  }
}
