// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/DownScatteringMatrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using DownScatteringMatrix = multigroup::DownScatteringMatrix;
using DownScatteringLegendreMoment = multigroup::DownScatteringLegendreMoment;
using ScatteringMatrix = multigroup::ScatteringMatrix;

std::string chunk();
void verifyChunk( const DownScatteringMatrix& );
DownScatteringMatrix makeDummyRecord();

SCENARIO( "DownScatteringMatrix" ) {

  GIVEN( "valid data for a DownScatteringMatrix instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< DownScatteringLegendreMoment > moments = {

        { 0, { 1, 2, 3, 4, 5, 6 }, 3 },
        { 1, { 11, 12, 13, 14, 15, 16 }, 3 }
      };

      DownScatteringMatrix chunk( std::move( moments ) );

      THEN( "a DownScatteringMatrix can be constructed and members can "
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

      auto iter = record.begin() + 12;
      auto end = record.end();

      DownScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2 );

      THEN( "a DownScatteringMatrix can be constructed and members can "
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

    WHEN( "using the copy constructor" ) {

      auto iter = record.begin() + 12;
      auto end = record.end();
      DownScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2 );

      DownScatteringMatrix copy( chunk );

      THEN( "a DownScatteringMatrix can be constructed and members can "
            "be tested" ) {

        verifyChunk( copy );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        copy.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      auto iter = record.begin() + 12;
      auto end = record.end();
      DownScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2 );

      DownScatteringMatrix move( std::move( chunk ) );

      THEN( "a DownScatteringMatrix can be constructed and members can "
            "be tested" ) {

        verifyChunk( move );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        move.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      auto iter = record.begin() + 12;
      auto end = record.end();
      DownScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2 );

      DownScatteringMatrix copy = makeDummyRecord();
      copy = chunk;

      THEN( "a DownScatteringMatrix can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        copy.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      auto iter = record.begin() + 12;
      auto end = record.end();
      DownScatteringMatrix chunk;
      chunk.read( iter, end, 3, 2 );

      DownScatteringMatrix move = makeDummyRecord();
      move = std::move( chunk );

      THEN( "a DownScatteringMatrix can be move assigned and "
            "members can be tested" ) {

        verifyChunk( move );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        move.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a DownScatteringMatrix instance" ) {

    WHEN( "the number of moments is insufficient" ) {

      std::vector< DownScatteringLegendreMoment > moments = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DownScatteringMatrix( std::move( moments ) ) );
      } // THEN
    } // WHEN

    WHEN( "the number of groups is inconsistent" ) {

      std::vector< DownScatteringLegendreMoment > moments = {

        { 0, { 1, 2, 3 }, 2 },                        // <-- groups = 2
        { 1, { 11, 12, 13, 14, 15, 16 }, 3 }          // <-- groups = 3
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DownScatteringMatrix( std::move( moments ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "pn_down_full\n"
         "    0\n"
         "    1 2 3 4 5\n"
         "    6\n"
         "    1\n"
         "    11 12 13 14 15\n"
         "    16\n";
}

void verifyChunk( const DownScatteringMatrix& chunk ) {

  CHECK( "pn_down_full" == chunk.keyword() );
  CHECK( std::nullopt == chunk.particle() );
  CHECK_THAT(  0, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  1, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(  2, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(  3, WithinRel( chunk.values()[3] ) );
  CHECK_THAT(  4, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(  5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT(  6, WithinRel( chunk.values()[6] ) );
  CHECK_THAT(  1, WithinRel( chunk.values()[7] ) );
  CHECK_THAT( 11, WithinRel( chunk.values()[8] ) );
  CHECK_THAT( 12, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 13, WithinRel( chunk.values()[10] ) );
  CHECK_THAT( 14, WithinRel( chunk.values()[11] ) );
  CHECK_THAT( 15, WithinRel( chunk.values()[12] ) );
  CHECK_THAT( 16, WithinRel( chunk.values()[13] ) );

  CHECK( false == chunk.empty() );
  CHECK( 14 == chunk.size() );

  CHECK( 3 == chunk.numberGroups() );
  CHECK( 3 == chunk.numberPrimaryGroups() );
  CHECK( 3 == chunk.numberOutgoingGroups() );
  CHECK( 2 == chunk.numberLegendreMoments() );

  CHECK( true == chunk.hasMoment( 0 ) );
  CHECK( true == chunk.hasMoment( 1 ) );
  CHECK( false == chunk.hasMoment( 102 ) );

  CHECK( 0 == chunk.moments()[0].order() );
  CHECK_THAT( 1, WithinRel( chunk.moments()[0].matrix()[0][0] ) );
  CHECK_THAT( 2, WithinRel( chunk.moments()[0].matrix()[0][1] ) );
  CHECK_THAT( 3, WithinRel( chunk.moments()[0].matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( chunk.moments()[0].matrix()[1][0] ) );
  CHECK_THAT( 4, WithinRel( chunk.moments()[0].matrix()[1][1] ) );
  CHECK_THAT( 5, WithinRel( chunk.moments()[0].matrix()[1][2] ) );
  CHECK_THAT( 0, WithinRel( chunk.moments()[0].matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( chunk.moments()[0].matrix()[2][1] ) );
  CHECK_THAT( 6, WithinRel( chunk.moments()[0].matrix()[2][2] ) );

  CHECK( 1 == chunk.moments()[1].order() );
  CHECK_THAT( 11, WithinRel( chunk.moments()[1].matrix()[0][0] ) );
  CHECK_THAT( 12, WithinRel( chunk.moments()[1].matrix()[0][1] ) );
  CHECK_THAT( 13, WithinRel( chunk.moments()[1].matrix()[0][2] ) );
  CHECK_THAT(  0, WithinRel( chunk.moments()[1].matrix()[1][0] ) );
  CHECK_THAT( 14, WithinRel( chunk.moments()[1].matrix()[1][1] ) );
  CHECK_THAT( 15, WithinRel( chunk.moments()[1].matrix()[1][2] ) );
  CHECK_THAT(  0, WithinRel( chunk.moments()[1].matrix()[2][0] ) );
  CHECK_THAT(  0, WithinRel( chunk.moments()[1].matrix()[2][1] ) );
  CHECK_THAT( 16, WithinRel( chunk.moments()[1].matrix()[2][2] ) );

  auto moment = chunk.moment( 0 );
  CHECK( 0 == moment.order() );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 2, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 3, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 4, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 5, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 6, WithinRel( moment.matrix()[2][2] ) );

  moment = chunk.moment( 1 );
  CHECK( 1 == moment.order() );
  CHECK_THAT( 11, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 12, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 13, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT(  0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 14, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 15, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT(  0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT(  0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 16, WithinRel( moment.matrix()[2][2] ) );

  ScatteringMatrix converted = chunk.toScatteringMatrix();

  CHECK( "pn_full" == converted.keyword() );
  CHECK( std::nullopt == converted.particle() );
  CHECK( false == converted.empty() );

  CHECK( 3 == converted.numberPrimaryGroups() );
  CHECK( 3 == converted.numberOutgoingGroups() );
  CHECK( 2 == converted.numberLegendreMoments() );

  CHECK( true == converted.hasMoment( 0 ) );
  CHECK( true == converted.hasMoment( 1 ) );

  auto moment = converted.moment( 0 );
  CHECK( 0 == moment.order() );
  CHECK( 3 == moment.numberPrimaryGroups() );
  CHECK( 3 == moment.numberOutgoingGroups() );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 2, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 3, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 4, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 5, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 6, WithinRel( moment.matrix()[2][2] ) );

  moment = converted.moment( 1 );
  CHECK( 1 == moment.order() );
  CHECK_THAT( 11, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 12, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 13, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT(  0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 14, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 15, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT(  0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT(  0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 16, WithinRel( moment.matrix()[2][2] ) );
}

DownScatteringMatrix makeDummyRecord() {

  return { { { 0, { 1, 2, 3 }, 2 } } };
}
