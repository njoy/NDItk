private:

/**
 *  @brief Private intermediate constructor
 */
ReactionMultiplicities( std::vector< Multiplicities >&& multiplicities,
                        std::size_t reactions ) :
    IntegerListRecord( base::Keyword( "rprod" ),
                       generateData( std::move( multiplicities ) ) ),
    reactions_( reactions ) {

  this->generateBlocks();
}

/**
 *  @brief Private intermediate constructor
 */
ReactionMultiplicities( ReactionMultiplicityType type,
                        std::vector< Multiplicities >&& multiplicities,
                        std::size_t reactions ) :
    IntegerListRecord( base::Keyword( "rprod", type ),
                       generateData( std::move( multiplicities ) ) ),
    reactions_( reactions ) {

  this->generateBlocks();
}

public:

/**
 *  @brief Default constructor
 */
ReactionMultiplicities() : IntegerListRecord( base::Keyword( "rprod" ) ) {}

/**
 *  @brief Default constructor
 */
ReactionMultiplicities( ReactionMultiplicityType type ) :
    IntegerListRecord( base::Keyword( "rprod", type ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] multiplicities    the multiplicity data
 */
ReactionMultiplicities( std::vector< Multiplicities > multiplicities ) :
    ReactionMultiplicities( std::move( multiplicities ),
                            multiplicities.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] type              the multiplicity type (all, few or rmo)
 *  @param[in] multiplicities    the multiplicity data
 */
ReactionMultiplicities( ReactionMultiplicityType type,
                        std::vector< Multiplicities > multiplicities ) :
    ReactionMultiplicities( type,
                            std::move( multiplicities ),
                            multiplicities.size() ) {}

/**
 *  @brief Copy constructor
 */
ReactionMultiplicities( const ReactionMultiplicities& base ) :
    IntegerListRecord( base ), reactions_( base.reactions_ ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor
 */
ReactionMultiplicities( ReactionMultiplicities&& base ) :
    IntegerListRecord( std::move( base ) ), reactions_( base.reactions_ ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment
 */
ReactionMultiplicities& operator=( const ReactionMultiplicities& base ) {

  new (this) ReactionMultiplicities( base );
  return *this;
}

/**
 *  @brief Move assignment
 */
ReactionMultiplicities& operator=( ReactionMultiplicities&& base ) {

  new (this) ReactionMultiplicities( std::move( base ) );
  return *this;
}
