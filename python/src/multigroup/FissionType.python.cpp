// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/multigroup/FissionType.hpp"

// namespace aliases
namespace python = pybind11;

namespace multigroup {

void wrapFissionType( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::NDItk::multigroup::FissionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "FissionType",
    "The fission data types",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Prompt", Component::Prompt )
  .value( "Delayed", Component::Delayed )
  .value( "Total", Component::Total );
}

} // namespace multigroup