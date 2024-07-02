// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace depletion {

  // declarations - NDI enumerators
  void wrapReactionMultiplicityType( python::module&, python::module& );

  // declarations - NDI records and subrecords
  void wrapMultiplicities( python::module&, python::module& );
  void wrapReactionMultiplicities( python::module&, python::module& );
}

void wrapDepletion( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "depletion",
    "Depeltion NDI records and subrecords"
  );

  depletion::wrapReactionMultiplicityType( submodule, viewmodule );
  depletion::wrapMultiplicities( submodule, viewmodule );
  depletion::wrapReactionMultiplicities( submodule, viewmodule );
}
