// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/Kerma.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapKerma( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::Kerma;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "Kerma",
    "A kerma record for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< std::vector< double > >(),
    python::arg( "values" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self      the record\n"
    "    values    the kerma values"
  )
  .def(

    python::init< unsigned int, std::vector< double > >(),
    python::arg( "particle" ), python::arg( "values" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self        the table\n"
    "    particle    the secondary particle identifier\n"
    "    values      the kerma values"
  )
  .def_property_readonly(

    "number_groups",
    &Record::numberGroups,
    "The number of groups defined by this record"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, unsigned int number ) -> Record
       { return readWithSubtype< Record >( string, number ); },
    python::arg( "string" ), python::arg( "number" ),
    "Read the record from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "record\n\n"
    "Arguments:\n"
    "    string    the string representing the record\n"
    "    number    the number of kerma values to be read"
  );

  // add standard record definitions
  addStandardRecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
