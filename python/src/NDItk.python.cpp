// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations

// declarations - record and subrecord subpackages
void wrapDepletion( python::module&, python::module& );
void wrapMultigroup( python::module&, python::module& );

// declarations - NDI table types
void wrapMultigroupTable( python::module&, python::module& );

/**
 *  @brief NDItk python bindings
 *
 *  The name given here (NDItk) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( NDItk, module ) {

  python::module::import( "tools" );

  // create the views submodule
  python::module viewmodule = module.def_submodule(

    "sequence",
    "sequence - NDI sequences (internal use only)"
  );

  // record and subrecord subpackages
  wrapDepletion( module, viewmodule );
  wrapMultigroup( module, viewmodule );

  // wrap ACE table types
  wrapMultigroupTable( module, viewmodule );
}
