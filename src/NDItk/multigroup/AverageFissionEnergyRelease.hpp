#ifndef NJOY_NDITK_MULTIGROUP_AVERAGEFISSIONENERGYRELEASE
#define NJOY_NDITK_MULTIGROUP_AVERAGEFISSIONENERGYRELEASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/RealListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief An average fission energy release record for multigroup
 *         neutron data
 */
class AverageFissionEnergyRelease : protected base::RealListRecord {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

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

  /* methods */

  /**
   *  @brief Return the prompt energy release (total energy release
   *         minus delayed particles and neutrinos)
   */
  double promptEnergyRelease() const {

    return this->values()[0];
  }

  /**
   *  @brief Return the total energy release (including delayed particles
   *         and neutrinos)
   */
  double totalEnergyRelease() const {

    return this->values()[1];
  }

  /**
   *  @brief Return the energy release through delayed betas
   */
  double delayedBetas() const {

    return this->values()[2];
  }

  /**
   *  @brief Return the energy release through prompt gammas
   */
  double promptGammas() const {

    return this->values()[3];
  }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons
   */
  double promptNeutrons() const {

    return this->values()[5];
  }

  /**
   *  @brief Return the kinetic energy of the fission products
   */
  double fissionFragments() const {

    return this->values()[4];
  }

  using base::RealListRecord::keyword;
  using base::RealListRecord::values;
  using base::RealListRecord::size;
  using base::RealListRecord::empty;
  using base::RealListRecord::begin;
  using base::RealListRecord::end;
  using base::RealListRecord::print;

  /**
   *  @brief Read the record data
   *
   *  This function overrides the base record read() function to enable
   *  verification of the read data.
   *
   *  @param[in,out] iter     an iterator to the current position in the input
   *  @param[in,out] end      an iterator to the end of the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    //! @todo do we want to do some verification here?
    base::RealListRecord::read( iter, end, 6 );
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
