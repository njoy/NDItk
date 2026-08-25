/**
 *  @brief Print the record (if it is not empty)
 *
 *  @param[in] iter   the current position in the output
 */
template< typename OutputIterator >
void print( OutputIterator& iter ) const {

  if ( ! this->empty() ) {

    this->key().print( iter );
    for ( const auto& entry : this->moments_ ) {

      entry.print( iter );
    }
  }
};
