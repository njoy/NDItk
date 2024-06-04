// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/depletion/ReactionMultiplicities.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Multiplicities = depletion::Multiplicities;
using ReactionMultiplicities = depletion::ReactionMultiplicities;

std::string chunk();
void verifyChunk( const ReactionMultiplicities& );
std::string chunkWithMultiplicityType();
void verifyChunkWithMultiplicityType( const ReactionMultiplicities& );
std::string chunkWithInsufficientNumberReactions();

SCENARIO( "ReactionMultiplicities" ) {

  GIVEN( "valid data for a ReactionMultiplicities instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< Multiplicities > multiplicities = {

        { 2, { 1, 92235 }, { 1, 1 } },
        { 16, { 1, 92234 }, { 2, 1 } }
      };

      ReactionMultiplicities chunk( std::move( multiplicities ) );

      THEN( "a ReactionMultiplicities can be constructed and members can "
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

      auto iter = record.begin() + 5;
      auto end = record.end();

      ReactionMultiplicities chunk;
      chunk.read( iter, end, 2 );

      THEN( "a ReactionMultiplicities can be constructed and members can "
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

  GIVEN( "valid data for a ReactionMultiplicities instance with a multiplicity type" ) {

    std::string record = chunkWithMultiplicityType();

    WHEN( "the data is given explicitly" ) {

      std::vector< Multiplicities > multiplicities = {

        { 2, { 1, 92235 }, { 1, 1 } },
        { 16, { 1, 92234 }, { 2, 1 } }
      };

      ReactionMultiplicities chunk( depletion::ReactionMultiplicityType::All,
                                    std::move( multiplicities ) );

      THEN( "a ReactionMultiplicities can be constructed and members can "
            "be tested" ) {

        verifyChunkWithMultiplicityType( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "the data is defined using iterators" ) {

      auto iter = record.begin() + 9;
      auto end = record.end();

      ReactionMultiplicities chunk( depletion::ReactionMultiplicityType::All );
      chunk.read( iter, end, 2 );

      THEN( "a ReactionMultiplicities can be constructed and members can "
            "be tested" ) {

        verifyChunkWithMultiplicityType( chunk );
      } // THEN

      THEN( "the record can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output );

        CHECK( buffer == record );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ReactionMultiplicities instance" ) {

    WHEN( "the number of reactions is insufficient" ) {

      std::vector< Multiplicities > multiplicities = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReactionMultiplicities( std::move( multiplicities ) ) );
      } // THEN
    } // WHEN

    WHEN( "reading the data of the record and the number of reactions "
          "values is insufficient" ) {

      std::string record = chunkWithInsufficientNumberReactions();
      auto iter = record.begin() + 5;
      auto end = record.end();
      ReactionMultiplicities chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end, 0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "rprod\n"
         "    2\n"
         "    2\n"
         "    1 1\n"
         "    92235 1\n"
         "    16\n"
         "    2\n"
         "    1 2\n"
         "    92234 1\n";
}

void verifyChunk( const ReactionMultiplicities& chunk ) {

  CHECK( "rprod" == chunk.keyword() );
  CHECK(     2 == chunk.values()[0] );
  CHECK(     2 == chunk.values()[1] );
  CHECK(     1 == chunk.values()[2] );
  CHECK(     1 == chunk.values()[3] );
  CHECK( 92235 == chunk.values()[4] );
  CHECK(     1 == chunk.values()[5] );
  CHECK(    16 == chunk.values()[6] );
  CHECK(     2 == chunk.values()[7] );
  CHECK(     1 == chunk.values()[8] );
  CHECK(     2 == chunk.values()[9] );
  CHECK( 92234 == chunk.values()[10] );
  CHECK(     1 == chunk.values()[11] );

  CHECK( false == chunk.empty() );
  CHECK( 12 == chunk.size() );

  CHECK( 2 == chunk.numberReactions() );

  CHECK( true == chunk.hasReaction( 2 ) );
  CHECK( true == chunk.hasReaction( 16 ) );
  CHECK( false == chunk.hasReaction( 102 ) );

  CHECK( 2 == chunk.reactions()[0].identifier() );
  CHECK( 2 == chunk.reactions()[0].numberReactionProducts() );
  CHECK( 1 == chunk.reactions()[0].reactionProducts()[0] );
  CHECK( 92235 == chunk.reactions()[0].reactionProducts()[1] );
  CHECK( 1 == chunk.reactions()[0].multiplicities()[0] );
  CHECK( 1 == chunk.reactions()[0].multiplicities()[1] );

  CHECK( 16 == chunk.reactions()[1].identifier() );
  CHECK( 2 == chunk.reactions()[1].numberReactionProducts() );
  CHECK( 1 == chunk.reactions()[1].reactionProducts()[0] );
  CHECK( 92234 == chunk.reactions()[1].reactionProducts()[1] );
  CHECK( 2 == chunk.reactions()[1].multiplicities()[0] );
  CHECK( 1 == chunk.reactions()[1].multiplicities()[1] );

  auto multiplicities = chunk.reaction( 2 );
  CHECK( 2 == chunk.reaction( 2 ).identifier() );
  CHECK( 2 == chunk.reaction( 2 ).numberReactionProducts() );
  CHECK( 1 == chunk.reaction( 2 ).reactionProducts()[0] );
  CHECK( 92235 == chunk.reaction( 2 ).reactionProducts()[1] );
  CHECK( 1 == chunk.reaction( 2 ).multiplicities()[0] );
  CHECK( 1 == chunk.reaction( 2 ).multiplicities()[1] );

  CHECK( 16 == chunk.reaction( 16 ).identifier() );
  CHECK( 2 == chunk.reaction( 16 ).numberReactionProducts() );
  CHECK( 1 == chunk.reaction( 16 ).reactionProducts()[0] );
  CHECK( 92234 == chunk.reaction( 16 ).reactionProducts()[1] );
  CHECK( 2 == chunk.reaction( 16 ).multiplicities()[0] );
  CHECK( 1 == chunk.reaction( 16 ).multiplicities()[1] );
}

std::string chunkWithMultiplicityType() {

  return "rprod_all\n"
         "    2\n"
         "    2\n"
         "    1 1\n"
         "    92235 1\n"
         "    16\n"
         "    2\n"
         "    1 2\n"
         "    92234 1\n";
}

void verifyChunkWithMultiplicityType( const ReactionMultiplicities& chunk ) {

  CHECK( "rprod_all" == chunk.keyword() );
  CHECK(     2 == chunk.values()[0] );
  CHECK(     2 == chunk.values()[1] );
  CHECK(     1 == chunk.values()[2] );
  CHECK(     1 == chunk.values()[3] );
  CHECK( 92235 == chunk.values()[4] );
  CHECK(     1 == chunk.values()[5] );
  CHECK(    16 == chunk.values()[6] );
  CHECK(     2 == chunk.values()[7] );
  CHECK(     1 == chunk.values()[8] );
  CHECK(     2 == chunk.values()[9] );
  CHECK( 92234 == chunk.values()[10] );
  CHECK(     1 == chunk.values()[11] );

  CHECK( false == chunk.empty() );
  CHECK( 12 == chunk.size() );

  CHECK( 2 == chunk.numberReactions() );

  CHECK( true == chunk.hasReaction( 2 ) );
  CHECK( true == chunk.hasReaction( 16 ) );
  CHECK( false == chunk.hasReaction( 102 ) );

  CHECK( 2 == chunk.reactions()[0].identifier() );
  CHECK( 2 == chunk.reactions()[0].numberReactionProducts() );
  CHECK( 1 == chunk.reactions()[0].reactionProducts()[0] );
  CHECK( 92235 == chunk.reactions()[0].reactionProducts()[1] );
  CHECK( 1 == chunk.reactions()[0].multiplicities()[0] );
  CHECK( 1 == chunk.reactions()[0].multiplicities()[1] );

  CHECK( 16 == chunk.reactions()[1].identifier() );
  CHECK( 2 == chunk.reactions()[1].numberReactionProducts() );
  CHECK( 1 == chunk.reactions()[1].reactionProducts()[0] );
  CHECK( 92234 == chunk.reactions()[1].reactionProducts()[1] );
  CHECK( 2 == chunk.reactions()[1].multiplicities()[0] );
  CHECK( 1 == chunk.reactions()[1].multiplicities()[1] );

  auto multiplicities = chunk.reaction( 2 );
  CHECK( 2 == chunk.reaction( 2 ).identifier() );
  CHECK( 2 == chunk.reaction( 2 ).numberReactionProducts() );
  CHECK( 1 == chunk.reaction( 2 ).reactionProducts()[0] );
  CHECK( 92235 == chunk.reaction( 2 ).reactionProducts()[1] );
  CHECK( 1 == chunk.reaction( 2 ).multiplicities()[0] );
  CHECK( 1 == chunk.reaction( 2 ).multiplicities()[1] );

  CHECK( 16 == chunk.reaction( 16 ).identifier() );
  CHECK( 2 == chunk.reaction( 16 ).numberReactionProducts() );
  CHECK( 1 == chunk.reaction( 16 ).reactionProducts()[0] );
  CHECK( 92234 == chunk.reaction( 16 ).reactionProducts()[1] );
  CHECK( 2 == chunk.reaction( 16 ).multiplicities()[0] );
  CHECK( 1 == chunk.reaction( 16 ).multiplicities()[1] );
}

std::string chunkWithInsufficientNumberReactions() {

  return "rprod\n";
}
