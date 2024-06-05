private:

/**
 *  @brief Private intermediate constructor
 *
 *  @param[in] tuple   the keyword, subtype and particle identifier (if present)
 */
Keyword( std::tuple< std::string,
                     std::optional< std::string >,
                     std::optional< int >,
                     std::optional< depletion::ReactionMultiplicityType >,
                     std::optional< multigroup::FissionType > > tuple ) :
    keyword_( std::move( std::get< 0 >( tuple ) ) ),
    subtype_( std::move( std::get< 1 >( tuple ) ) ),
    particle_( std::move( std::get< 2 >( tuple ) ) ),
    multiplicity_( std::move( std::get< 3 >( tuple ) ) ),
    fission_( std::move( std::get< 4 >( tuple ) ) ) {}

public:

Keyword() = default;

/**
 *  @brief Constructor
 *
 *  @param[in] keyword   the keyword of the record
 */
Keyword( std::string keyword ) :
    Keyword( splitKeyword( std::move( keyword ) ) ) {}

/**
 *  @brief Constructor for particle subtypes
 *
 *  @param[in] subtype    the subtype of the record
 *  @param[in] particle   the particle identifier
 */
Keyword( std::string subtype, unsigned int particle ) :
    Keyword( subtype + "_" + std::to_string( particle ) ) {}

/**
 *  @brief Constructor for multiplicity subtypes
 *
 *  @param[in] subtype    the subtype of the record
 *  @param[in] type       the multiplicity type
 */
Keyword( std::string subtype, depletion::ReactionMultiplicityType type ) :
    Keyword( subtype +
             ( type == depletion::ReactionMultiplicityType::All
               ? std::string( "_all" )
               : type == depletion::ReactionMultiplicityType::Few
                 ? std::string( "_few" )
                 : std::string( "_rmo" ) ) ) {}

/**
 *  @brief Constructor for fission subtypes
 *
 *  @param[in] subtype    the subtype of the record
 *  @param[in] type       the fission type
 */
Keyword( std::string subtype, multigroup::FissionType type ) :
    Keyword( subtype +
             ( type == multigroup::FissionType::Prompt
               ? std::string( "_pr" )
               : type == multigroup::FissionType::Delayed
                 ? std::string( "_del" )
                 : std::string( "_tot" ) ) ) {}
