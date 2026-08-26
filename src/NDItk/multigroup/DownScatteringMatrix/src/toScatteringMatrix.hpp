/**
 *  @brief Convert this deprecated record to a ScatteringMatrix instance
 */
ScatteringMatrix toScatteringMatrix() const {

  if ( this->empty() ) {

    return ScatteringMatrix();
  }

  std::vector< LegendreMoment > moments;
  moments.reserve( this->moments_.size() );
  for ( const auto& moment : this->moments_ ) {

    std::vector< double > matrix;
    matrix.reserve( this->numberGroups() * this->numberGroups() );
    for ( const auto& row : moment.matrix() ) {

      matrix.insert( matrix.end(), row.begin(), row.end() );
    }
    moments.emplace_back( moment.order(), std::move( matrix ),
                          this->numberGroups(), this->numberGroups() );
  }
  return ScatteringMatrix( std::move( moments ) );
}
