// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/FissionNeutronProduction.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapFissionNeutronProduction( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::FissionNeutronProduction;
  using FissionType = njoy::NDItk::multigroup::FissionType;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "FissionNeutronProduction",
    "A fission neutron production record for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< FissionType, std::vector< double > >(),
    python::arg( "type" ), python::arg( "values" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self      the record\n"
    "    values    the fission neutron production values"
  )
  .def_property_readonly(

    "type",
    &Record::type,
    "The fission type defined by this record"
  )
  .def_property_readonly(

    "number_groups",
    &Record::numberGroups,
    "The number of groups defined by this record"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, unsigned int number ) -> Record
       { return readWithFissionSubtype< Record >( string, number ); },
    python::arg( "string" ), python::arg( "number" ),
    "Read the record from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "record\n\n"
    "Arguments:\n"
    "    string    the string representing the record\n"
    "    number    the fission neutron production values"
  );

  // add standard record definitions
  addStandardRecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
