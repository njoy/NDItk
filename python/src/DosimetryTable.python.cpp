// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/DosimetryTable.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

void wrapDosimetryTable( python::module& module, python::module& ) {

  // type aliases
  using Table = njoy::NDItk::DosimetryTable;
  using Metadata = njoy::NDItk::dosimetry::Metadata;
  using EnergyGroupStructure = njoy::NDItk::multigroup::EnergyGroupStructure;
  using FluxWeights = njoy::NDItk::multigroup::FluxWeights;
  using TotalCrossSection = njoy::NDItk::multigroup::TotalCrossSection;
  using ReactionCrossSections = njoy::NDItk::multigroup::ReactionCrossSections;

  // wrap views created by this table

  // create the table
  python::class_< Table > table(

    module,
    "DosimetryTable",
    "A dosimetry data table"
  );

  // wrap the table
  table
  .def(

    python::init< std::string, std::string, std::string,
                  double, double, double,
                  EnergyGroupStructure,
                  FluxWeights,
                  TotalCrossSection,
                  ReactionCrossSections,
                  std::optional< std::string >,
                  std::optional< std::string >,
                  std::optional< double > >(),
    python::arg( "zaid" ), python::arg( "libname" ),
    python::arg( "process" ), python::arg( "awr" ),
    python::arg( "temperature" ), python::arg( "dilution" ),
    python::arg( "structure" ), python::arg( "flux" ),
    python::arg( "total_xs" ), python::arg( "reaction_xs" ),
    python::arg( "information" ) = std::nullopt,
    python::arg( "source" ) = std::nullopt,
    python::arg( "weight" ) = std::nullopt,
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
    "    flux               the flux weights\n"
    "    total_xs           the total cross section\n"
    "    reaction_xs        the reaction cross section data\n"
    "    information        the table information line (optional)\n"
    "    source             the source date (optional)\n"
    "    weight             the atomic weight of the target (optional)"
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
  .def(

    "reaction_product_multiplicities",
    &Table::reactionProductMultiplicities,
    python::arg( "type" ),
    "The reaction product multiplicities record for the requested multiplicity type\n\n"
    "Arguments:\n"
    "    self    the table\n"
    "    type    the multiplicity type"
  );

  // add standard table definitions
  addStandardTableDefinitions< Table >( table );
}
