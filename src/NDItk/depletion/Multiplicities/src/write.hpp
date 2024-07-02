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
  buffer << "    " << x[0] << '\n'
         << "    " << x[1] << '\n';
  x += 2;

  auto lines = this->numberReactionProducts();

  while ( lines-- ) {

    buffer << "    " << x[0] << ' ' << x[1] << '\n';
    x += 2;
  }

  for ( auto c : buffer.str() ) { *iter++ = c; }
};
