/**
 *  @brief Resolve deprecated records
 *
 *  @param[in] downScattering   the deprecated DownScatteringMatrix
 */
void resolveDeprecation( const multigroup::DownScatteringMatrix& downScattering ) {

  if ( ! downScattering.empty() ) {

    if ( ! this->scattering_.empty() ) {

      Log::error( "A \'{}\' and a \'{}\' keyword cannot both be used in a multigroup table",
                  downScattering.keyword(), this->scattering_.keyword() );
      throw std::exception();
    }
    this->scattering_ = downScattering.toScatteringMatrix();
  }
}
