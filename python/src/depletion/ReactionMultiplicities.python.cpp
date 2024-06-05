// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/depletion/ReactionMultiplicities.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace depletion {

void wrapReactionMultiplicities( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::depletion::ReactionMultiplicities;
  using Multiplicities = njoy::NDItk::depletion::Multiplicities;
  using ReactionMultiplicityType = njoy::NDItk::depletion::ReactionMultiplicityType;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "ReactionMultiplicities",
    "A reaction product multiplicity record for depletion data"
  );

  // wrap the record
  record
  .def(

    python::init< std::vector< Multiplicities > >(),
    python::arg( "multiplicities" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self              the record\n"
    "    multiplicities    the multiplicity data"
  )
  .def(

    python::init< const ReactionMultiplicityType&,
                  std::vector< Multiplicities > >(),
    python::arg( "type" ),python::arg( "multiplicities" ),
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self              the record\n"
    "    type              the multiplicity type (all, few or rmo)\n"
    "    multiplicities    the multiplicity data"
  )
  .def_property_readonly(

    "type",
    &Record::type,
    "The multiplicity type defined by this record"
  )
  .def_property_readonly(

    "number_reactions",
    &Record::numberReactions,
    "The number of reactions defined by this record"
  )
  .def_property_readonly(

    "reactions",
    &Record::reactions,
    "The multiplicity data for all reactions"
  )
  .def(

    "has_reaction",
    &Record::hasReaction,
    python::arg( "reaction" ),
    "Return whether or not a given reaction is present\n\n"
    "    self        the record\n"
    "    reaction    the reaction to look for"
  )
  .def(

    "reaction",
    &Record::reaction,
    python::arg( "reaction" ),
    "Return the multiplicity data for a given reaction\n\n"
    "    self        the record\n"
    "    reaction    the reaction to look for"
  )
  .def_static(

    "from_string",
    [] ( const std::string& string, unsigned int reactions ) -> Record
       { return readWithMultiplicitySubtype< Record >( string, reactions ); },
    python::arg( "string" ), python::arg( "reactions" ),
    "Read the record from a string\n\n"
    "An exception is raised if something goes wrong while reading the\n"
    "record\n\n"
    "Arguments:\n"
    "    string      the string representing the record\n"
    "    reactions   the number of reactions to be read"
  );

  // add standard record definitions
  addStandardRecordDefinitions< Record, DoubleRange >( record );
}

} // depletion namespace
