// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/DownScatteringLegendreMoment.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapDownScatteringLegendreMoment( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::multigroup::DownScatteringLegendreMoment;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "DownScatteringLegendreMoment",
    "A Legendre moment subrecord for multigroup neutron data using an upper\n"
    "triangular matrix (deprecated)"
  );

  // wrap the record
  record
  .def(

    python::init< int, std::vector< double >, std::size_t >(),
    python::arg( "order" ), python::arg( "values" ),
    python::arg( "groups" ),
    "Initialise the subrecord\n\n"
    "Arguments:\n"
    "    self      the record\n"
    "    order     the Legendre order\n"
    "    values    the compressed (down scatter) values of the matrix\n"
    "    groups    the number of groups"
  )
  .def_property_readonly(

    "order",
    &Record::order,
    "The Legendre moment order"
  )
  .def_property_readonly(

    "number_groups",
    &Record::numberGroups,
    "The number of groups"
  )
  .def_property_readonly(

    "number_primary_groups",
    &Record::numberPrimaryGroups,
    "The number of primary groups"
  )
  .def_property_readonly(

    "number_outgoing_groups",
    &Record::numberOutgoingGroups,
    "The number of outgoing groups"
  )
  .def_property_readonly(

    "matrix",
    [] ( const Record& self ) -> DoubleRange2D
       { return self.matrix(); },
    "The full matrix defined by this record"
  );

  // add standard record definitions
  addStandardSubrecordDefinitions< Record, DoubleRange >( record );
}

} // multigroup namespace
