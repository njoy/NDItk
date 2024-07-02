// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/base/Keyword.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;
using Keyword = base::Keyword;

SCENARIO( "Keyword" ) {

  Keyword result( "num_grps" );
  CHECK( "num_grps" == result.keyword() );
  CHECK( std::nullopt == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( false == result.hasSubtype() );

  result = Keyword( "num_grps_0" );
  CHECK( "num_grps_0" == result.keyword() );
  CHECK( "num_grps" == result.subtype() );
  CHECK( 0 == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "num_grps", 0 );
  CHECK( "num_grps_0" == result.keyword() );
  CHECK( "num_grps" == result.subtype() );
  CHECK( 0 == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "e_bounds_1001" );
  CHECK( "e_bounds_1001" == result.keyword() );
  CHECK( "e_bounds" == result.subtype() );
  CHECK( 1001 == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "e_bounds", 1001 );
  CHECK( "e_bounds_1001" == result.keyword() );
  CHECK( "e_bounds" == result.subtype() );
  CHECK( 1001 == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "sig_0" );
  CHECK( "sig_0" == result.keyword() );
  CHECK( std::nullopt == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( false == result.hasSubtype() );

  result = Keyword( "rprod" );
  CHECK( "rprod" == result.keyword() );
  CHECK( std::nullopt == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( false == result.hasSubtype() );

  result = Keyword( "rprod_all" );
  CHECK( "rprod_all" == result.keyword() );
  CHECK( "rprod" == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( depletion::ReactionMultiplicityType::All == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "rprod_few" );
  CHECK( "rprod_few" == result.keyword() );
  CHECK( "rprod" == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( depletion::ReactionMultiplicityType::Few == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "rprod_rmo" );
  CHECK( "rprod_rmo" == result.keyword() );
  CHECK( "rprod" == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( depletion::ReactionMultiplicityType::RMO == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "nu_pr" );
  CHECK( "nu_pr" == result.keyword() );
  CHECK( "nu" == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( multigroup::FissionType::Prompt == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "nu_del" );
  CHECK( "nu_del" == result.keyword() );
  CHECK( "nu" == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( multigroup::FissionType::Delayed == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "nu_tot" );
  CHECK( "nu_tot" == result.keyword() );
  CHECK( "nu" == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( multigroup::FissionType::Total == result.fissionType() );
  CHECK( true == result.hasSubtype() );

  result = Keyword( "num_sec_parts" );
  CHECK( "num_sec_parts" == result.keyword() );
  CHECK( std::nullopt == result.subtype() );
  CHECK( std::nullopt == result.particle() );
  CHECK( std::nullopt == result.multiplicityType() );
  CHECK( std::nullopt == result.fissionType() );
  CHECK( false == result.hasSubtype() );

  CHECK_THROWS( Keyword( "NuM_GrPs" ) );
} // SCENARIO
