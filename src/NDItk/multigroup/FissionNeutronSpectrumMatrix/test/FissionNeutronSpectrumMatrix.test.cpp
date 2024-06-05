// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/multigroup/FissionNeutronSpectrumMatrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using FissionNeutronSpectrumMatrix = multigroup::FissionNeutronSpectrumMatrix;
using FissionType = multigroup::FissionType;

std::string chunk();
void verifyChunk( const FissionNeutronSpectrumMatrix& );
std::string chunkWithInsufficientNumberValues();

SCENARIO( "FissionNeutronSpectrumMatrix" ) {

  GIVEN( "valid data for a FissionNeutronSpectrumMatrix instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > values = {   1,   2,   3,   4,   5,   6,   7,
                                       1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1,
                                       1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2,
                                       1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3,
                                       1.4, 2.4, 3.4, 4.4, 5.4, 6.4, 7.4,
                                       1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5,
                                       1.6, 2.6, 3.6, 4.6, 5.6, 6.6, 7.6 };

      FissionNeutronSpectrumMatrix chunk( FissionType::Prompt, std::move( values ) );

      THEN( "a FissionNeutronSpectrumMatrix can be constructed and members can "
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

      FissionNeutronSpectrumMatrix chunk( FissionType::Prompt );
      chunk.read( iter, end, 7 );

      THEN( "a FissionNeutronSpectrumMatrix can be constructed and members can "
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

  GIVEN( "invalid data for a FissionNeutronSpectrumMatrix instance" ) {

    WHEN( "the number of weight values is insufficient" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};

        CHECK_THROWS( FissionNeutronSpectrumMatrix( FissionType::Prompt, std::move( empty ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberValues();
      auto iter = record.begin() + 10;
      auto end = record.end();
      FissionNeutronSpectrumMatrix chunk( FissionType::Prompt );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "chi_mat_pr\n"
         "    1 2 3 4 5\n"
         "    6 7 1.1 2.1 3.1\n"
         "    4.1 5.1 6.1 7.1 1.2\n"
         "    2.2 3.2 4.2 5.2 6.2\n"
         "    7.2 1.3 2.3 3.3 4.3\n"
         "    5.3 6.3 7.3 1.4 2.4\n"
         "    3.4 4.4 5.4 6.4 7.4\n"
         "    1.5 2.5 3.5 4.5 5.5\n"
         "    6.5 7.5 1.6 2.6 3.6\n"
         "    4.6 5.6 6.6 7.6\n";
}

void verifyChunk( const FissionNeutronSpectrumMatrix& chunk ) {

  CHECK( "chi_mat_pr" == chunk.keyword() );
  CHECK_THAT( 1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 2, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 3, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 4, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 5, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 6, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 7, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 1.1, WithinRel( chunk.values()[7] ) );
  CHECK_THAT( 2.1, WithinRel( chunk.values()[8] ) );
  CHECK_THAT( 3.1, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 4.1, WithinRel( chunk.values()[10] ) );
  CHECK_THAT( 5.1, WithinRel( chunk.values()[11] ) );
  CHECK_THAT( 6.1, WithinRel( chunk.values()[12] ) );
  CHECK_THAT( 7.1, WithinRel( chunk.values()[13] ) );
  CHECK_THAT( 1.2, WithinRel( chunk.values()[14] ) );
  CHECK_THAT( 2.2, WithinRel( chunk.values()[15] ) );
  CHECK_THAT( 3.2, WithinRel( chunk.values()[16] ) );
  CHECK_THAT( 4.2, WithinRel( chunk.values()[17] ) );
  CHECK_THAT( 5.2, WithinRel( chunk.values()[18] ) );
  CHECK_THAT( 6.2, WithinRel( chunk.values()[19] ) );
  CHECK_THAT( 7.2, WithinRel( chunk.values()[20] ) );
  CHECK_THAT( 1.3, WithinRel( chunk.values()[21] ) );
  CHECK_THAT( 2.3, WithinRel( chunk.values()[22] ) );
  CHECK_THAT( 3.3, WithinRel( chunk.values()[23] ) );
  CHECK_THAT( 4.3, WithinRel( chunk.values()[24] ) );
  CHECK_THAT( 5.3, WithinRel( chunk.values()[25] ) );
  CHECK_THAT( 6.3, WithinRel( chunk.values()[26] ) );
  CHECK_THAT( 7.3, WithinRel( chunk.values()[27] ) );
  CHECK_THAT( 1.4, WithinRel( chunk.values()[28] ) );
  CHECK_THAT( 2.4, WithinRel( chunk.values()[29] ) );
  CHECK_THAT( 3.4, WithinRel( chunk.values()[30] ) );
  CHECK_THAT( 4.4, WithinRel( chunk.values()[31] ) );
  CHECK_THAT( 5.4, WithinRel( chunk.values()[32] ) );
  CHECK_THAT( 6.4, WithinRel( chunk.values()[33] ) );
  CHECK_THAT( 7.4, WithinRel( chunk.values()[34] ) );
  CHECK_THAT( 1.5, WithinRel( chunk.values()[35] ) );
  CHECK_THAT( 2.5, WithinRel( chunk.values()[36] ) );
  CHECK_THAT( 3.5, WithinRel( chunk.values()[37] ) );
  CHECK_THAT( 4.5, WithinRel( chunk.values()[38] ) );
  CHECK_THAT( 5.5, WithinRel( chunk.values()[39] ) );
  CHECK_THAT( 6.5, WithinRel( chunk.values()[40] ) );
  CHECK_THAT( 7.5, WithinRel( chunk.values()[41] ) );
  CHECK_THAT( 1.6, WithinRel( chunk.values()[42] ) );
  CHECK_THAT( 2.6, WithinRel( chunk.values()[43] ) );
  CHECK_THAT( 3.6, WithinRel( chunk.values()[44] ) );
  CHECK_THAT( 4.6, WithinRel( chunk.values()[45] ) );
  CHECK_THAT( 5.6, WithinRel( chunk.values()[46] ) );
  CHECK_THAT( 6.6, WithinRel( chunk.values()[47] ) );
  CHECK_THAT( 7.6, WithinRel( chunk.values()[48] ) );

  CHECK_THAT(   1, WithinRel( chunk.matrix()[0][0] ) );
  CHECK_THAT(   2, WithinRel( chunk.matrix()[0][1] ) );
  CHECK_THAT(   3, WithinRel( chunk.matrix()[0][2] ) );
  CHECK_THAT(   4, WithinRel( chunk.matrix()[0][3] ) );
  CHECK_THAT(   5, WithinRel( chunk.matrix()[0][4] ) );
  CHECK_THAT(   6, WithinRel( chunk.matrix()[0][5] ) );
  CHECK_THAT(   7, WithinRel( chunk.matrix()[0][6] ) );
  CHECK_THAT( 1.1, WithinRel( chunk.matrix()[1][0] ) );
  CHECK_THAT( 2.1, WithinRel( chunk.matrix()[1][1] ) );
  CHECK_THAT( 3.1, WithinRel( chunk.matrix()[1][2] ) );
  CHECK_THAT( 4.1, WithinRel( chunk.matrix()[1][3] ) );
  CHECK_THAT( 5.1, WithinRel( chunk.matrix()[1][4] ) );
  CHECK_THAT( 6.1, WithinRel( chunk.matrix()[1][5] ) );
  CHECK_THAT( 7.1, WithinRel( chunk.matrix()[1][6] ) );
  CHECK_THAT( 1.2, WithinRel( chunk.matrix()[2][0] ) );
  CHECK_THAT( 2.2, WithinRel( chunk.matrix()[2][1] ) );
  CHECK_THAT( 3.2, WithinRel( chunk.matrix()[2][2] ) );
  CHECK_THAT( 4.2, WithinRel( chunk.matrix()[2][3] ) );
  CHECK_THAT( 5.2, WithinRel( chunk.matrix()[2][4] ) );
  CHECK_THAT( 6.2, WithinRel( chunk.matrix()[2][5] ) );
  CHECK_THAT( 7.2, WithinRel( chunk.matrix()[2][6] ) );
  CHECK_THAT( 1.3, WithinRel( chunk.matrix()[3][0] ) );
  CHECK_THAT( 2.3, WithinRel( chunk.matrix()[3][1] ) );
  CHECK_THAT( 3.3, WithinRel( chunk.matrix()[3][2] ) );
  CHECK_THAT( 4.3, WithinRel( chunk.matrix()[3][3] ) );
  CHECK_THAT( 5.3, WithinRel( chunk.matrix()[3][4] ) );
  CHECK_THAT( 6.3, WithinRel( chunk.matrix()[3][5] ) );
  CHECK_THAT( 7.3, WithinRel( chunk.matrix()[3][6] ) );
  CHECK_THAT( 1.4, WithinRel( chunk.matrix()[4][0] ) );
  CHECK_THAT( 2.4, WithinRel( chunk.matrix()[4][1] ) );
  CHECK_THAT( 3.4, WithinRel( chunk.matrix()[4][2] ) );
  CHECK_THAT( 4.4, WithinRel( chunk.matrix()[4][3] ) );
  CHECK_THAT( 5.4, WithinRel( chunk.matrix()[4][4] ) );
  CHECK_THAT( 6.4, WithinRel( chunk.matrix()[4][5] ) );
  CHECK_THAT( 7.4, WithinRel( chunk.matrix()[4][6] ) );
  CHECK_THAT( 1.5, WithinRel( chunk.matrix()[5][0] ) );
  CHECK_THAT( 2.5, WithinRel( chunk.matrix()[5][1] ) );
  CHECK_THAT( 3.5, WithinRel( chunk.matrix()[5][2] ) );
  CHECK_THAT( 4.5, WithinRel( chunk.matrix()[5][3] ) );
  CHECK_THAT( 5.5, WithinRel( chunk.matrix()[5][4] ) );
  CHECK_THAT( 6.5, WithinRel( chunk.matrix()[5][5] ) );
  CHECK_THAT( 7.5, WithinRel( chunk.matrix()[5][6] ) );
  CHECK_THAT( 1.6, WithinRel( chunk.matrix()[6][0] ) );
  CHECK_THAT( 2.6, WithinRel( chunk.matrix()[6][1] ) );
  CHECK_THAT( 3.6, WithinRel( chunk.matrix()[6][2] ) );
  CHECK_THAT( 4.6, WithinRel( chunk.matrix()[6][3] ) );
  CHECK_THAT( 5.6, WithinRel( chunk.matrix()[6][4] ) );
  CHECK_THAT( 6.6, WithinRel( chunk.matrix()[6][5] ) );
  CHECK_THAT( 7.6, WithinRel( chunk.matrix()[6][6] ) );

  CHECK( false == chunk.empty() );
  CHECK( 49 == chunk.size() );

  CHECK( FissionType::Prompt == chunk.type() );
  CHECK( 7 == chunk.numberGroups() );
}

std::string chunkWithInsufficientNumberValues() {

  return "chi_mat_pr\n";
}
