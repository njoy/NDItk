private:

/**
 *  @brief Private intermediate constructor
 */
DownScatteringMatrix( std::vector< DownScatteringLegendreMoment >&& moments,
                      unsigned int groups,
                      unsigned int number ) :
    RealListRecord( base::Keyword( "pn_down_full" ), generateData( moments ) ),
    groups_( groups ), number_moments_( number ) {

  this->generateBlocks();
}

public:

/**
 *  @brief Default constructor for the scattering matrix
 */
DownScatteringMatrix() : RealListRecord( base::Keyword( "pn_down_full" ) ) {}

/**
 *  @brief Constructor for the scattering matrix
 *
 *  @param[in] moments   the Legendre moments of the scattering matrix
 */
DownScatteringMatrix( std::vector< DownScatteringLegendreMoment > moments ) :
    DownScatteringMatrix( std::move( moments ),
                          moments.size() == 0 ? 0 : moments.front().numberGroups(),
                          moments.size() ) {}

/**
 *  @brief Copy constructor
 */
DownScatteringMatrix( const DownScatteringMatrix& base ) :
    RealListRecord( base ), groups_( base.groups_ ),
    number_moments_( base.number_moments_ ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor
 */
DownScatteringMatrix( DownScatteringMatrix&& base ) :
    RealListRecord( std::move( base ) ), groups_( base.groups_ ),
    number_moments_( base.number_moments_ ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment
 */
DownScatteringMatrix& operator=( const DownScatteringMatrix& base ) {

  if ( this != &base ) {

    base::RealListRecord::operator=( base );
    this->groups_ = base.groups_;
    this->number_moments_ = base.number_moments_;
    this->generateBlocks();
  }
  return *this;
}

/**
 *  @brief Move assignment
 */
DownScatteringMatrix& operator=( DownScatteringMatrix&& base ) {

  if ( this != &base ) {

    base::RealListRecord::operator=( std::move( base ) );
    this->groups_ = base.groups_;
    this->number_moments_ = base.number_moments_;
    this->generateBlocks();
  }
  return *this;
}
