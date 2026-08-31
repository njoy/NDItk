/**
 *  @brief Expand the compressed upper triangular matrix into a full square matrix
 *
 *  @param[in] data     the data values in the Legendre moment subrecord
 *  @param[in] groups   the number of groups
 */
template < typename Range >
static std::vector< double > generateMatrix( const Range& data, unsigned int groups ) {

  std::vector< double > matrix( groups * groups, 0. );
  std::size_t index = 1;
  for ( unsigned int i = 0; i < groups; ++i ) {

    for ( unsigned int j = i; j < groups; ++j ) {

      matrix[ i * groups + j ] = data[ index ];
      ++index;
    }
  }
  return matrix;
}
