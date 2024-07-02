// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/depletion/Multiplicities.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace depletion {

void wrapMultiplicities( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::depletion::Multiplicities;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "Multiplicities",
    "A reaction product multiplicity subrecord for depletion data"
  );

  // wrap the record
  record
  .def(

    python::init< int, std::vector< int >, std::vector< int > >(),
    python::arg( "reaction" ), python::arg( "products" ),
    python::arg( "multiplicities" ),
    "Initialise the subrecord\n\n"
    "Arguments:\n"
    "    self              the record\n"
    "    reaction          the reaction number\n"
    "    products          the reaction product identifiers\n"
    "    multiplicities    the multiplicity values"
  )
  .def_property_readonly(

    "identifier",
    &Record::identifier,
    "The reaction identifier"
  )
  .def_property_readonly(

    "number_reaction_products",
    &Record::numberReactionProducts,
    "The number of reaction products"
  )
  .def_property_readonly(

    "reaction_products",
    [] ( const Record& self ) -> IntRange
       { return self.reactionProducts(); },
    "The reaction product identifiers"
  )
  .def_property_readonly(

    "multiplicities",
    [] ( const Record& self ) -> IntRange
       { return self.multiplicities(); },
    "The reaction product multiplicities"
  );

  // add standard record definitions
  addStandardSubrecordDefinitions< Record, IntRange >( record );
}

} // depletion namespace
