// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/OutgoingParticleTypes.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapOutgoingParticleTypes( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::OutgoingParticleTypes;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "OutgoingParticleTypes",
    "An outgoing particle type record for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< std::vector< int > >(),
    python::arg( "values" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self      the record\n"
    "    values    the particle types"
  )
  .def_property_readonly(

    "number_outgoing_particles",
    &Record::numberOutgoingParticles,
    "The number of outgoing particles defined by this record"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, unsigned int number ) -> Record
       { return read< Record >( string, number ); },
    python::arg( "string" ), python::arg( "number" ),
    "Read the record from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "record\n\n"
    "Arguments:\n"
    "    string    the string representing the record\n"
    "    number    the number of particle types to be read"
  );

  // add standard record definitions
  addStandardRecordDefinitions< Record, IntRange >( record );
}

} // multigroup namespace