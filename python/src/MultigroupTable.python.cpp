// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/MultigroupTable.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMultigroupTable( python::module& module, python::module& ) {

  // type aliases
  using Table = njoy::NDItk::MultigroupTable;
  using Metadata = njoy::NDItk::multigroup::Metadata;
  using EnergyGroupStructure = njoy::NDItk::multigroup::EnergyGroupStructure;
  using Velocities = njoy::NDItk::multigroup::Velocities;
  using FluxWeights = njoy::NDItk::multigroup::FluxWeights;
  using TotalCrossSection = njoy::NDItk::multigroup::TotalCrossSection;
  using ReactionCrossSections = njoy::NDItk::multigroup::ReactionCrossSections;
  using AverageFissionEnergyRelease = njoy::NDItk::multigroup::AverageFissionEnergyRelease;
  using FissionNeutronMultiplicity = njoy::NDItk::multigroup::FissionNeutronMultiplicity;
  using FissionNeutronProduction = njoy::NDItk::multigroup::FissionNeutronProduction;
  using FissionNeutronSpectrumMatrix = njoy::NDItk::multigroup::FissionNeutronSpectrumMatrix;
  using FissionNeutronSpectrumVector = njoy::NDItk::multigroup::FissionNeutronSpectrumVector;
  using OutgoingParticleTypes = njoy::NDItk::multigroup::OutgoingParticleTypes;
  using OutgoingParticleTransportData = njoy::NDItk::multigroup::OutgoingParticleTransportData;
  using HeatingNumbers = njoy::NDItk::multigroup::HeatingNumbers;
  using Kerma = njoy::NDItk::multigroup::Kerma;
  using ScatteringMatrix = njoy::NDItk::multigroup::ScatteringMatrix;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "MultigroupTable",
    "A multigroup neutron and photon table"
  );

  // wrap the table
  table
  .def(

    python::init< std::string, std::string, std::string,
                  double, double, double,
                  EnergyGroupStructure,
                  std::vector< EnergyGroupStructure >,
                  Velocities,
                  FluxWeights,
                  TotalCrossSection,
                  ReactionCrossSections,
                  ScatteringMatrix,
                  std::optional< std::string >,
                  std::optional< std::string >,
                  std::optional< double >,
                  std::optional< AverageFissionEnergyRelease >,
                  std::optional< OutgoingParticleTypes >,
                  std::optional< OutgoingParticleTransportData >,
                  std::vector< ScatteringMatrix >,
                  std::optional< HeatingNumbers >,
                  std::vector< HeatingNumbers >,
                  std::optional< Kerma >,
                  std::vector< Kerma > >(),
    python::arg( "zaid" ), python::arg( "libname" ),
    python::arg( "process" ), python::arg( "awr" ),
    python::arg( "temperature" ), python::arg( "dilution" ),
    python::arg( "structure" ), python::arg( "outgoing" ),
    python::arg( "velocities" ), python::arg( "flux" ),
    python::arg( "total_xs" ), python::arg( "reaction_xs" ),
    python::arg( "scattering" ),
    python::arg( "information" ) = std::nullopt,
    python::arg( "source" ) = std::nullopt,
    python::arg( "weight" ) = std::nullopt,
    python::arg( "fission_q" ) = std::nullopt,
    python::arg( "types" ) = std::nullopt,
    python::arg( "transport" ) = std::nullopt,
    python::arg( "production" ) = std::vector< ScatteringMatrix >{},
    python::arg( "primary_heating" ) = std::nullopt,
    python::arg( "outgoing_heating" ) = std::vector< HeatingNumbers >{},
    python::arg( "primary_kerma" ) = std::nullopt,
    python::arg( "outgoing_kerma" ) = std::vector< Kerma >{},
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self               the table\n"
    "    zaid               the zaid of the table\n"
    "    libname            the library name\n"
    "    process            the processing date\n"
    "    awr                the atomic weight ratio of the target (with respect\n"
    "                       to the neutron mass)\n"
    "    temperature        the temperature of the target\n"
    "    dilution           the dilution (aka sigma0)\n"
    "    structure          the primary group structure\n"
    "    outgoing           the outgoing particle group structures\n"
    "    velocities         the velocities\n"
    "    flux               the flux weights\n"
    "    total_xs           the total cross section\n"
    "    reaction_xs        the reaction cross section data\n"
    "    scattering         the scattering matrix\n"
    "    information        the table information line (optional)\n"
    "    source             the source date (optional)\n"
    "    weight             the atomic weight of the target (optional)\n"
    "    fission_q          the average fission energy release data (optional)\n"
    "    types              the outgoing particle types (optional)\n"
    "    transport          the outgoing particle transport data (optional)\n"
    "    primary_heating    the primary heating numbers (optional)\n"
    "    outgoing_heating   the outgoing particle heating numbers (optional)\n"
    "    primary_kerma      the primary kerma (optional)\n"
    "    outgoing_kerma     the outgoing particle kermas (optional)"
  )
  .def_property_readonly(

    "metadata",
    &Table::metadata,
    "The metadata of the table"
  )
  .def_property_readonly(

    "primary_group_boundaries",
    &Table::primaryGroupBoundaries,
    "The primary group structure record"
  )
  .def_property_readonly(

    "velocities",
    &Table::velocities,
    "The velocity record"
  )
  .def_property_readonly(

    "flux_weights",
    &Table::fluxWeights,
    "The flux weight record"
  )
  .def_property_readonly(

    "total_cross_section",
    &Table::totalCrossSection,
    "The total cross section record"
  )
  .def_property_readonly(

    "reaction_cross_sections",
    &Table::reactionCrossSections,
    "The reaction cross section record"
  )
  .def_property_readonly(

    "scattering_matrix",
    &Table::scatteringMatrix,
    "The scattering matrix record"
  )
  .def_property_readonly(

    "average_fission_energy_release",
    &Table::averageFissionEnergyRelease,
    "The average fission energy release record"
  )
  .def(

    "fission_neutron_multiplicity",
    &Table::fissionNeutronMultiplicity,
    python::arg( "type" ),
    "The fission neutron multiplicity record for the requested fission type"
    "Arguments:\n"
    "    self    the table\n"
    "    type    the fission type"
  )
  .def(

    "fission_neutron_production",
    &Table::fissionNeutronProduction,
    python::arg( "type" ),
    "The fission neutron production record for the requested fission type"
    "Arguments:\n"
    "    self    the table\n"
    "    type    the fission type"
  )
  .def(

    "fission_neutron_spectrum_matrix",
    &Table::fissionNeutronSpectrumMatrix,
    python::arg( "type" ),
    "The fission neutron spectrum matrix record for the requested fission type"
    "Arguments:\n"
    "    self    the table\n"
    "    type    the fission type"
  )
  .def(

    "fission_neutron_spectrum_vector",
    &Table::fissionNeutronSpectrumVector,
    python::arg( "type" ),
    "The fission neutron spectrum vector record for the requested fission type"
    "Arguments:\n"
    "    self    the table\n"
    "    type    the fission type"
  )
  .def_property_readonly(

    "primary_heating_numbers",
    &Table::primaryHeatingNumbers,
    "The primary heating numbers record"
  )
  .def_property_readonly(

    "primary_kerma",
    &Table::primaryKerma,
    "The primary kerma record"
  )
  .def_property_readonly(

    "outgoing_particle_types",
    &Table::outgoingParticleTypes,
    "The outgoing particle types record"
  )
  .def_property_readonly(

    "outgoing_particle_transport_data",
    &Table::outgoingParticleTransportData,
    "The outgoing particle transport data record"
  )
  .def(

    "outgoing_group_boundaries",
    &Table::outgoingGroupBoundaries,
    python::arg( "particle" ),
    "The group structure record for an outgoing particle\n\n"
    "Arguments:\n"
    "    self       the table\n"
    "    particle   the outgoing particle identifier"
  )
  .def(

    "outgoing_production_matrix",
    &Table::outgoingProductionMatrix,
    python::arg( "particle" ),
    "The production record for an outgoing particle\n\n"
    "Arguments:\n"
    "    self       the table\n"
    "    particle   the outgoing particle identifier"
  )
  .def(

    "outgoing_heating_numbers",
    &Table::outgoingHeatingNumbers,
    python::arg( "particle" ),
    "The heating numbers record for an outgoing particle\n\n"
    "Arguments:\n"
    "    self       the table\n"
    "    particle   the outgoing particle identifier"
  )
  .def(

    "outgoing_kerma",
    &Table::outgoingKerma,
    python::arg( "particle" ),
    "The kerma record for an outgoing particle\n\n"
    "Arguments:\n"
    "    self       the table\n"
    "    particle   the outgoing particle identifier"
  );

  // add standard table definitions
  addStandardTableDefinitions< Table >( table );
}
