// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/FissionNeutronMultiplicity.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using FissionNeutronMultiplicity = multigroup::FissionNeutronMultiplicity;
using FissionType = multigroup::FissionType;

std::string chunk();
void verifyChunk( const FissionNeutronMultiplicity& );
std::string chunkWithInsufficientNumberValues();

SCENARIO( "FissionNeutronMultiplicity" ) {

  GIVEN( "valid data for a FissionNeutronMultiplicity instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > values = { 2., 2.1, 2.2, 2.3, 2.4, 5.0, 7.0 };

      FissionNeutronMultiplicity chunk( FissionType::Prompt, std::move( values ) );

      THEN( "a FissionNeutronMultiplicity can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "the data is read using iterators" ) {

      auto iter = record.begin() + 5;
      auto end = record.end();

      FissionNeutronMultiplicity chunk( FissionType::Prompt );
      chunk.read( iter, end, 7 );

      THEN( "a FissionNeutronMultiplicity can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a FissionNeutronMultiplicity instance" ) {

    WHEN( "the number of weight values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};

        CHECK_THROWS( FissionNeutronMultiplicity( FissionType::Prompt, std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberValues();
      auto iter = record.begin() + 5;
      auto end = record.end();
      FissionNeutronMultiplicity chunk( FissionType::Prompt );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "nu_pr\n"
         "    2 2.1 2.2 2.3 2.4\n"
         "    5 7\n";
}

void verifyChunk( const FissionNeutronMultiplicity& chunk ) {

  CHECK( "nu_pr" == chunk.keyword() );
  CHECK_THAT(   2, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 2.1, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 2.2, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 2.3, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 2.4, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(   5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT(   7, WithinRel( chunk.values()[6] ) );

  CHECK( false == chunk.empty() );
  CHECK( 7 == chunk.size() );

  CHECK( FissionType::Prompt == chunk.type() );
  CHECK( 7 == chunk.numberGroups() );
}

std::string chunkWithInsufficientNumberValues() {

  return "nu_pr\n";
}
