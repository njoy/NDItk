/**
 *  @brief Default constructor
 */
MultigroupTable() : metadata_(), structure_(), weights_(), xs_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] zaid           the zaid of the table
 *  @param[in] libname        the library name
 *  @param[in] source         the source date
 *  @param[in] process        the processing date
 *  @param[in] awr            the atomic weight ratio of the target
 *                            (with respect to the neutron mass)
 *  @param[in] weight         the atomic weight of the target
 *  @param[in] temperature    the temperature of the target
 *  @param[in] dilution       the dilution (aka sigma0)
 *  @param[in] structure      the primary group structure
 *  @param[in] weights        the flux weights
 *  @param[in] xs             the reaction cross section data
 */
MultigroupTable( std::string zaid, std::string libname, std::string source,
                 std::string process, double awr, double weight, double temperature,
                 double dilution,
                 multigroup::Structure structure,
                 multigroup::FluxWeights weigths,
                 multigroup::ReactionCrossSections xs ) :
    metadata_( std::move( zaid ), std::move( libname ), std::move( source ),
               std::move( process ), awr, weight, temperature, dilution,
               xs.numberGroups(), xs.numberReactions() ),
    structure_( std::move( structure ) ),
    weights_( std::move( weigths ) ),
    xs_( std::move( xs ) ) {

  this->verify();
}