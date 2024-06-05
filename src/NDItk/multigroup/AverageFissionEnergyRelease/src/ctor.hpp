/**
 *  @brief Default constructor for the average fission energy release
 */
AverageFissionEnergyRelease() : RealListRecord( base::Keyword( "fiss_q" ) ) {}


/**
 *  @brief Constructor for the average fission energy release
 *
 *  @param[in] total       the total energy release (including delayed particles
 *                         and neutrinos)
 *  @param[in] prompt      the recoverable energy release (total minus delayed
 *                         particles and neutrinos)
 *  @param[in] neutrons    the energy release through prompt neutrons
 *  @param[in] gammas      the energy release through prompt gammas
 *  @param[in] betas       the energy release through delayed betas
 *  @param[in] fragments   the kinetic energy of fission fragments
 */
AverageFissionEnergyRelease( double total, double prompt, double neutrons,
                             double gammas, double betas, double fragments ) :
    RealListRecord( base::Keyword( "fiss_q" ), { prompt, total, betas,
                                                 gammas, fragments, neutrons } ) {

  //! @todo do we want to do some verification here?
}
