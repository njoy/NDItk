// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/FissionNeutronSpectrumVector.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using FissionNeutronSpectrumVector = multigroup::FissionNeutronSpectrumVector;
using FissionType = multigroup::FissionType;

std::string chunk();
void verifyChunk( const FissionNeutronSpectrumVector& );
std::string chunkWithInsufficientNumberValues();

SCENARIO( "FissionNeutronSpectrumVector" ) {

  GIVEN( "valid data for a FissionNeutronSpectrumVector instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > values = {   1,   2,   3,   4,   5,   6,   7 };

      FissionNeutronSpectrumVector chunk( FissionType::Prompt, std::move( values ) );

      THEN( "a FissionNeutronSpectrumVector can be constructed and members can "
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

      auto iter = record.begin() + 10;
      auto end = record.end();

      FissionNeutronSpectrumVector chunk( FissionType::Prompt );
      chunk.read( iter, end, 7 );

      THEN( "a FissionNeutronSpectrumVector can be constructed and members can "
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

  GIVEN( "invalid data for a FissionNeutronSpectrumVector instance" ) {

    WHEN( "the number of weight values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};

        CHECK_THROWS( FissionNeutronSpectrumVector( FissionType::Prompt, std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberValues();
      auto iter = record.begin() + 10;
      auto end = record.end();
      FissionNeutronSpectrumVector chunk( FissionType::Prompt );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "chi_vec_pr\n"
         "    1 2 3 4 5\n"
         "    6 7\n";
}

void verifyChunk( const FissionNeutronSpectrumVector& chunk ) {

  CHECK( "chi_vec_pr" == chunk.keyword() );
  CHECK_THAT( 1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 2, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 3, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 4, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 5, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 6, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 7, WithinRel( chunk.values()[6] ) );

  CHECK( false == chunk.empty() );
  CHECK( 7 == chunk.size() );

  CHECK( FissionType::Prompt == chunk.type() );
  CHECK( 7 == chunk.numberGroups() );
}

std::string chunkWithInsufficientNumberValues() {

  return "chi_vec_pr\n";
}
