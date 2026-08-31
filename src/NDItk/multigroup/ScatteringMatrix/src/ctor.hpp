private:

/**
 *  @brief Private intermediate constructor
 */
ScatteringMatrix( std::vector< LegendreMoment >&& moments,
                  unsigned int incident,
                  unsigned int number ) :
    RealListRecord( base::Keyword( "pn_full" ), generateData( moments ) ),
    incident_( incident ), outgoing_( incident ), number_moments_( number ) {

  this->generateBlocks();
}

/**
 *  @brief Private intermediate constructor
 */
ScatteringMatrix( unsigned int particle,
                  std::vector< LegendreMoment >&& moments,
                  unsigned int incident,
                  unsigned int outgoing,
                  unsigned int number ) :
    RealListRecord( base::Keyword( "pn_prod_full", particle ),
                    generateData( std::move( moments ) ) ),
    incident_( incident ), outgoing_( outgoing ), number_moments_( number ) {

  this->generateBlocks();
}

public:

/**
 *  @brief Default constructor for the scattering matrix
 */
ScatteringMatrix() : RealListRecord( base::Keyword( "pn_full" ) ) {}

/**
 *  @brief Default constructor for a secondary particle's production matrix
 *
 *  @param[in] particle    the secondary particle identifier
 */
ScatteringMatrix( unsigned int particle ) :
    RealListRecord( base::Keyword( "pn_prod_full", particle ) ) {}

/**
 *  @brief Constructor for the scattering matrix
 *
 *  @param[in] moments   the Legendre moments of the scattering matrix
 */
ScatteringMatrix( std::vector< LegendreMoment > moments ) :
    ScatteringMatrix( std::move( moments ),
                      moments.size() == 0 ? 0 : moments.front().numberPrimaryGroups(),
                      moments.size() ) {}

/**
 *  @brief Constructor for a secondary particle's production matrix
 *
 *  @param[in] particle   the secondary particle identifier
 *  @param[in] moments    the Legendre moments of the production matrix
 */
ScatteringMatrix( unsigned int particle,
                  std::vector< LegendreMoment > moments ) :
    ScatteringMatrix( particle,
                      std::move( moments ),
                      moments.size() == 0 ? 0 : moments.front().numberPrimaryGroups(),
                      moments.size() == 0 ? 0 : moments.front().numberOutgoingGroups(),
                      moments.size() ) {}

/**
 *  @brief Copy constructor
 */
ScatteringMatrix( const ScatteringMatrix& base ) :
    RealListRecord( base ), incident_( base.incident_ ), outgoing_( base.outgoing_ ),
    number_moments_( base.number_moments_ ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor
 */
ScatteringMatrix( ScatteringMatrix&& base ) :
    RealListRecord( std::move( base ) ), incident_( base.incident_ ), outgoing_( base.outgoing_ ),
    number_moments_( base.number_moments_ ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment
 */
ScatteringMatrix& operator=( const ScatteringMatrix& base ) {

  if ( this != &base ) {

    base::RealListRecord::operator=( base );
    this->incident_ = base.incident_;
    this->outgoing_ = base.outgoing_;
    this->number_moments_ = base.number_moments_;
    this->generateBlocks();
  }
  return *this;
}

/**
 *  @brief Move assignment
 */
ScatteringMatrix& operator=( ScatteringMatrix&& base ) {

  if ( this != &base ) {

    base::RealListRecord::operator=( std::move( base ) );
    this->incident_ = base.incident_;
    this->outgoing_ = base.outgoing_;
    this->number_moments_ = base.number_moments_;
    this->generateBlocks();
  }
  return *this;
}
