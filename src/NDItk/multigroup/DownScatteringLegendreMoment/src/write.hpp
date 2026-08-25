/**
 *  @brief Write the record data
 *
 *  This assumes that the record is not empty.
 *
 *  @param[in] iter   the current position in the output
 */
template< typename OutputIterator >
void write( OutputIterator& iter ) const {

  std::ostringstream buffer;

  auto x = this->begin();
  buffer << "    " << static_cast< int >( std::round( *x ) ) << '\n';
  ++x;

  auto full = ( this->size() - 1 ) / 5;
  auto partial = ( this->size() - 1 ) % 5;

  while ( full-- ) {

    buffer << "    " << std::setprecision( 15 ) << x[0];
    buffer << ' ' << std::setprecision( 15 ) << x[1];
    buffer << ' ' << std::setprecision( 15 ) << x[2];
    buffer << ' ' << std::setprecision( 15 ) << x[3];
    buffer << ' ' << std::setprecision( 15 ) << x[4] << '\n';
    x += 5;
  }

  if ( partial ) {

    buffer << "   ";
    while ( partial-- ) {

      buffer << ' ' << std::setprecision( 15 ) << *x;
      ++x;
    }
    buffer << '\n';
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
};
