// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace multigroup {

  // declarations - NDI enumerators
  void wrapReactionMultiplicityType( python::module&, python::module& );

  // declarations - NDI records and subrecords
  void wrapMultiplicities( python::module&, python::module& );
  void wrapReactionMultiplicities( python::module&, python::module& );
  void wrapFissionType( python::module&, python::module& );
  void wrapMetadata( python::module&, python::module& );
  void wrapCrossSection( python::module&, python::module& );
  void wrapDownScatteringLegendreMoment( python::module&, python::module& );
  void wrapDownScatteringMatrix( python::module&, python::module& );
  void wrapFluxWeights( python::module&, python::module& );
  void wrapEnergyGroupStructure( python::module&, python::module& );
  void wrapReactionCrossSections( python::module&, python::module& );
  void wrapTotalCrossSection( python::module&, python::module& );
  void wrapVelocities( python::module&, python::module& );
  void wrapHeatingNumbers( python::module&, python::module& );
  void wrapKerma( python::module&, python::module& );
  void wrapAverageFissionEnergyRelease( python::module&, python::module& );
  void wrapFissionNeutronMultiplicity( python::module&, python::module& );
  void wrapFissionNeutronProduction( python::module&, python::module& );
  void wrapFissionNeutronSpectrumMatrix( python::module&, python::module& );
  void wrapFissionNeutronSpectrumVector( python::module&, python::module& );
  void wrapOutgoingParticleTypes( python::module&, python::module& );
  void wrapOutgoingParticleTransportData( python::module&, python::module& );
  void wrapLegendreMoment( python::module&, python::module& );
  void wrapScatteringMatrix( python::module&, python::module& );
}

void wrapMultigroup( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "multigroup",
    "Multigroup neutron and photon NDI records and subrecords"
  );

  multigroup::wrapReactionMultiplicityType( submodule, viewmodule );
  multigroup::wrapMultiplicities( submodule, viewmodule );
  multigroup::wrapReactionMultiplicities( submodule, viewmodule );
  multigroup::wrapFissionType( submodule, viewmodule );
  multigroup::wrapMetadata( submodule, viewmodule );
  multigroup::wrapCrossSection( submodule, viewmodule );
  multigroup::wrapDownScatteringLegendreMoment( submodule, viewmodule );
  multigroup::wrapDownScatteringMatrix( submodule, viewmodule );
  multigroup::wrapFluxWeights( submodule, viewmodule );
  multigroup::wrapEnergyGroupStructure( submodule, viewmodule );
  multigroup::wrapReactionCrossSections( submodule, viewmodule );
  multigroup::wrapTotalCrossSection( submodule, viewmodule );
  multigroup::wrapVelocities( submodule, viewmodule );
  multigroup::wrapHeatingNumbers( submodule, viewmodule );
  multigroup::wrapKerma( submodule, viewmodule );
  multigroup::wrapAverageFissionEnergyRelease( submodule, viewmodule );
  multigroup::wrapFissionNeutronMultiplicity( submodule, viewmodule );
  multigroup::wrapFissionNeutronProduction( submodule, viewmodule );
  multigroup::wrapFissionNeutronSpectrumMatrix( submodule, viewmodule );
  multigroup::wrapFissionNeutronSpectrumVector( submodule, viewmodule );
  multigroup::wrapOutgoingParticleTypes( submodule, viewmodule );
  multigroup::wrapOutgoingParticleTransportData( submodule, viewmodule );
  multigroup::wrapLegendreMoment( submodule, viewmodule );
  multigroup::wrapScatteringMatrix( submodule, viewmodule );
}
