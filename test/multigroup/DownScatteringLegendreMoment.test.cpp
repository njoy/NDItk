// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/DownScatteringLegendreMoment.hpp"
#include "tools/std20/views.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using DownScatteringLegendreMoment = multigroup::DownScatteringLegendreMoment;

std::string chunk();
std::vector< double > data();
void verifyChunk( const DownScatteringLegendreMoment& );
std::vector< double > dataWithInsufficientLength();

SCENARIO( "DownScatteringLegendreMoment" ) {

  GIVEN( "valid data for a DownScatteringLegendreMoment instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      int order = 2;
      std::vector< double > values = { 1., 2., 3., 4.,
                                           5., 6., 7.,
                                               8., 9.,
                                                  10. };
      std::size_t groups = 4;

      DownScatteringLegendreMoment chunk( order, std::move( values ), groups );

      THEN( "a DownScatteringLegendreMoment can be constructed and members can "
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

      std::vector< double > values = data();
      auto begin = values.begin();
      auto end = values.end();

      DownScatteringLegendreMoment chunk( begin, end, 4 );

      THEN( "a DownScatteringLegendreMoment can be constructed and members can "
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

  GIVEN( "invalid data for a DownScatteringLegendreMoment instance" ) {

    WHEN( "the number of matrix values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DownScatteringLegendreMoment( 2, {}, 4 ) );
      } // THEN
    } // WHEN

    WHEN( "using iterators and the number of matrix values is "
          "insufficient" ) {

      std::vector< double > values = dataWithInsufficientLength();
      auto begin = values.begin();
      auto end = values.end();

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( DownScatteringLegendreMoment( begin, end, 4 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "    2\n"
         "    1 2 3 4 5\n"
         "    6 7 8 9 10\n";
}

std::vector< double > data() {

  return {  2,
            1., 2., 3., 4.,
                5., 6., 7.,
                    8., 9.,
                       10. };
}

void verifyChunk( const DownScatteringLegendreMoment& chunk ) {

  CHECK( 2 == chunk.order() );
  CHECK( 4 == chunk.numberGroups() );
  CHECK( 4 == chunk.numberPrimaryGroups() );
  CHECK( 4 == chunk.numberOutgoingGroups() );

  // the full matrix: stored values on/above the diagonal, zeros below
  CHECK_THAT(  1, WithinRel( chunk.matrix()[0][0] ) );
  CHECK_THAT(  2, WithinRel( chunk.matrix()[0][1] ) );
  CHECK_THAT(  3, WithinRel( chunk.matrix()[0][2] ) );
  CHECK_THAT(  4, WithinRel( chunk.matrix()[0][3] ) );
  CHECK_THAT(  0, WithinRel( chunk.matrix()[1][0] ) );
  CHECK_THAT(  5, WithinRel( chunk.matrix()[1][1] ) );
  CHECK_THAT(  6, WithinRel( chunk.matrix()[1][2] ) );
  CHECK_THAT(  7, WithinRel( chunk.matrix()[1][3] ) );
  CHECK_THAT(  0, WithinRel( chunk.matrix()[2][0] ) );
  CHECK_THAT(  0, WithinRel( chunk.matrix()[2][1] ) );
  CHECK_THAT(  8, WithinRel( chunk.matrix()[2][2] ) );
  CHECK_THAT(  9, WithinRel( chunk.matrix()[2][3] ) );
  CHECK_THAT(  0, WithinRel( chunk.matrix()[3][0] ) );
  CHECK_THAT(  0, WithinRel( chunk.matrix()[3][1] ) );
  CHECK_THAT(  0, WithinRel( chunk.matrix()[3][2] ) );
  CHECK_THAT( 10, WithinRel( chunk.matrix()[3][3] ) );

  // the stored (compressed) data
  CHECK_THAT(  2, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(  1, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(  2, WithinRel( chunk.values()[2] ) );
  CHECK_THAT(  3, WithinRel( chunk.values()[3] ) );
  CHECK_THAT(  4, WithinRel( chunk.values()[4] ) );
  CHECK_THAT(  5, WithinRel( chunk.values()[5] ) );
  CHECK_THAT(  6, WithinRel( chunk.values()[6] ) );
  CHECK_THAT(  7, WithinRel( chunk.values()[7] ) );
  CHECK_THAT(  8, WithinRel( chunk.values()[8] ) );
  CHECK_THAT(  9, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 10, WithinRel( chunk.values()[10] ) );

  CHECK( false == chunk.empty() );
  CHECK( 11 == chunk.size() );
}

std::vector< double > dataWithInsufficientLength() {

  return { 2 };
}
