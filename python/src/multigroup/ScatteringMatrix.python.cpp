// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/ScatteringMatrix.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapScatteringMatrix( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::ScatteringMatrix;
  using LegendreMoment = njoy::NDItk::multigroup::LegendreMoment;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "ScatteringMatrix",
    "A scattering matrix record for multigroup neutron and photon data"
  );

  // wrap the record
  record
  .def(

    python::init< std::vector< LegendreMoment > >(),
    python::arg( "moments" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self      the record\n"
    "    moments   the Legendre moments of the scattering matrix"
  )
  .def(

    python::init< unsigned int, std::vector< LegendreMoment > >(),
    python::arg( "particle" ), python::arg( "moments" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self       the record\n"
    "    particle   the secondary particle identifier\n"
    "    moments    the Legendre moments of the scattering matrix"
  )
  .def_property_readonly(

    "particle",
    [] ( const Record& self ) { return self.particle(); },
    "The particle identifier"
  )
  .def_property_readonly(

    "number_primary_groups",
    &Record::numberPrimaryGroups,
    "The number of primary groups defined by this record"
  )
  .def_property_readonly(

    "number_outgoing_groups",
    &Record::numberOutgoingGroups,
    "The number of outgoing groups defined by this record"
  )
  .def_property_readonly(

    "number_legendre_moments",
    &Record::numberLegendreMoments,
    "The number of moments defined in this record"
  )
  .def_property_readonly(

    "moments",
    &Record::moments,
    "The  Legendre moments"
  )
  .def(

    "has_moment",
    &Record::hasMoment,
    python::arg( "order" ),
    "Return whether or not a given moment is present\n\n"
    "    self     the record\n"
    "    order    the Legendre order to look for"
  )
  .def(

    "moment",
    &Record::moment,
    python::arg( "order" ),
    "Return the moment for a given order\n\n"
    "    self     the record\n"
    "    order    the Legendre order to look for"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, unsigned int incident,
         unsigned int number ) -> Record
       { return readWithParticleSubtype< Record >( string, incident, number ); },
    python::arg( "string" ), python::arg( "incident" ),
    python::arg( "number" ),
    "Read the record from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "record\n\n"
    "Arguments:\n"
    "    string      the string representing the record\n"
    "    incident    the number of incident energy groups\n"
    "    number      the number of moments"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, unsigned int incident,
         unsigned int outgoing, unsigned int number ) -> Record
       { return readWithParticleSubtype< Record >( string, incident, outgoing, number ); },
    python::arg( "string" ), python::arg( "incident" ),
    python::arg( "outgoing" ), python::arg( "number" ),
    "Read the record from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "record\n\n"
    "Arguments:\n"
    "    string      the string representing the record\n"
    "    incident    the number of incident energy groups\n"
    "    outgoing    the number of outgoing energy groups\n"
    "    number      the number of moments"
  );

  // add standard record definitions
  addStandardRecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
