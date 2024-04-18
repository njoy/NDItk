// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/base/IntegerListRecord.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using IntegerListRecord = base::IntegerListRecord;

std::string chunk();
void verifyChunk( const IntegerListRecord& );

SCENARIO( "IntegerListRecord" ) {

  GIVEN( "valid data for a IntegerListRecord instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      IntegerListRecord chunk( "rprod_all", { 1, 2, 3, 4, 5, 6, 7, 8 } );

      THEN( "a IntegerListRecord can be constructed and members can "
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

    WHEN( "the data is defined by iterators" ) {

      auto iter = record.begin() + 9;
      auto end = record.end();
      IntegerListRecord chunk( "rprod_all" );
      chunk.read( iter, end, 8 );

      THEN( "a IntegerListRecord can be constructed and members can "
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
} // SCENARIO

std::string chunk() {

  return "rprod_all\n"
         "         1         2         3         4         5         6\n"
         "         7         8\n";
}

void verifyChunk( const IntegerListRecord& chunk ) {

  CHECK( "rprod_all" == chunk.keyword() );
  CHECK( true == chunk.hasContent() );
  CHECK( 8 == chunk.content().value().size() );
  CHECK( 1 == chunk.content().value()[0] );
  CHECK( 2 == chunk.content().value()[1] );
  CHECK( 3 == chunk.content().value()[2] );
  CHECK( 4 == chunk.content().value()[3] );
  CHECK( 5 == chunk.content().value()[4] );
  CHECK( 6 == chunk.content().value()[5] );
  CHECK( 7 == chunk.content().value()[6] );
  CHECK( 8 == chunk.content().value()[7] );
}