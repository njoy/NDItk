/**
 *  @brief Verify the cross section data values
 *
 *  The following verification tests are performed:
 *    - there are at least three values
 *    - the reaction identifier looks to be an integer
 *
 *  @param[in] data    the data values in the cross section subrecord
 */
template < typename Range >
static void verify( const Range& data ) {

  if ( data.size() < 2 ) {

    Log::error( "Expected at least 2 data values consisting of a reaction identifier,\n"
                "and the number of reaction products" );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }

  if ( data[1] < 0 ) {

    Log::error( "The number of reaction products cannot be less than zero" );
    Log::info( "Found {} as the number of reaction products", data[1] );
    throw std::exception();
  }


  if ( data.size() != 2 + 2 * data[1] ) {

    Log::error( "Expected at least {} data values consisting of a reaction identifier,\n"
                "the number of reaction products (in this case equal to {}) followed\n"
                "by {} reaction product identifier and multiplicity value pairs",
                2 + 2 * data[1], data[1], data[1] );
    Log::info( "Found {} data values", data.size() );
    throw std::exception();
  }
}
