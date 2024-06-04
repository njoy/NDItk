// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/depletion/Multiplicities.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Multiplicities = depletion::Multiplicities;

std::string chunk();
std::vector< int > data();
void verifyChunk( const Multiplicities& );
std::vector< int > dataWithInsufficientLength();

SCENARIO( "Multiplicities" ) {

  GIVEN( "valid data for a Multiplicities instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      int reaction = 16;
      std::vector< int > products = { 1, 92234 };
      std::vector< int > multiplicities = { 2, 1 };

      Multiplicities chunk( reaction, std::move( products ), std::move( multiplicities ) );

      THEN( "a Multiplicities can be constructed and members can "
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

    WHEN( "the data is defined using iterators" ) {

      std::vector< int > values = data();
      auto begin = values.begin();
      auto end = values.end();

      Multiplicities chunk( begin, end );

      THEN( "a Multiplicities can be constructed and members can "
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

  GIVEN( "invalid data for a Multiplicities instance" ) {

    WHEN( "the number of reaction products and multiplcities is insufficient" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Multiplicities( 16, { 1, 92233 }, { 1 } ) );
      } // THEN
    } // WHEN

    WHEN( "using iterators and the number of cross section values is "
          "insufficient" ) {

      std::vector< int > values = dataWithInsufficientLength();
      auto begin = values.begin();
      auto end = values.end();

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Multiplicities( begin, end ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "    16\n"
         "    2\n"
         "    1 2\n"
         "    92234 1\n";
}

std::vector< int > data() {

  return { 16,
            2,
           1, 2, 92234, 1 };
}

void verifyChunk( const Multiplicities& chunk ) {

  CHECK(    16 == chunk.values()[0] );
  CHECK(     2 == chunk.values()[1] );
  CHECK(     1 == chunk.values()[2] );
  CHECK(     2 == chunk.values()[3] );
  CHECK( 92234 == chunk.values()[4] );
  CHECK(     1 == chunk.values()[5] );

  CHECK( false == chunk.empty() );
  CHECK( 6 == chunk.size() );

  CHECK( 2 == chunk.numberReactionProducts() );
  CHECK( 2 == chunk.reactionProducts().size() );
  CHECK( 2 == chunk.multiplicities().size() );
  CHECK( 16 == chunk.identifier() );
  CHECK( 1 == chunk.reactionProducts()[0] );
  CHECK( 92234 == chunk.reactionProducts()[1] );
  CHECK( 2 == chunk.multiplicities()[0] );
  CHECK( 1 == chunk.multiplicities()[1] );
}

std::vector< int > dataWithInsufficientLength() {

  return { 16 };
}
