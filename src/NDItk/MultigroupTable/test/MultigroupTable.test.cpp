// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "NDItk/MultigroupTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::NDItk;

std::string chunk();
void verifyChunk( const MultigroupTable& );
std::string chunkWithMissingRecords();

SCENARIO( "MultigroupTable" ) {

  GIVEN( "valid data for a MultigroupTable instance" ) {

    std::string record = chunk();

    WHEN( "the data is given explicitly" ) {

      std::string zaid = "92235.711nm";
      std::string information = "this is some information for the table";
      std::string name = "mendf71x";
      std::string source = "12/22/2011";
      std::string process = "08/07/2013";
      double awr = 233.0248;
      double weight = 235.043937521619;
      double temperature = 2.53e-8;
      double dilution = 1e+10;
      multigroup::EnergyGroupStructure structure( { 20., 18.123456789, 16.0000000000001,
                                                    14., 10., 5, 1, 1e-11 } );
      std::vector< multigroup::EnergyGroupStructure > outgoing =   {
          { 0, { 20., 10., 5, 1e-11 } },
          { 1001, { 20., 10., 1e-11 } }
      };
      multigroup::Velocities velocities( { 2.1, 2.2, 2.25, 2.05, 2.15, 2.04, 2.06 } );
      multigroup::FluxWeights weights( { 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 } );
      multigroup::TotalCrossSection total( { 1.1, 1.2, 1.25, 1.05, 1.15, 1.04, 1.06 } );
      multigroup::ReactionCrossSections xs( { { 2, 0.0, { 10., 20., 30., 40., 50., 60., 70. } },
                                              { 16, 1.1234567, { 1., 2., 3., 4., 5., 6., 7. } } } );
      multigroup::ScatteringMatrix scattering( { { 0, { 1, 0, 0, 0, 0, 0, 0,
                                                        0, 1, 0, 0, 0, 0, 0,
                                                        0, 0, 1, 0, 0, 0, 0,
                                                        0, 0, 0, 1, 0, 0, 0,
                                                        0, 0, 0, 0, 1, 0, 0,
                                                        0, 0, 0, 0, 0, 1, 0,
                                                        0, 0, 0, 0, 0, 0, 1 }, 7 },
                                                 { 1, { 0, 0, 0, 0, 0, 0, 1,
                                                        0, 0, 0, 0, 0, 1, 0,
                                                        0, 0, 0, 0, 1, 0, 0,
                                                        0, 0, 0, 1, 0, 0, 0,
                                                        0, 0, 1, 0, 0, 0, 0,
                                                        0, 1, 0, 0, 0, 0, 0,
                                                        1, 0, 0, 0, 0, 0, 0 }, 7 } } );
      multigroup::AverageFissionEnergyRelease release( 202.827, 181.238898, 4.827645,
                                                       7.281253, 6.5, 169.13 );
      multigroup::OutgoingParticleTypes types( { 0, 1001 } );
      multigroup::OutgoingParticleTransportData transport( { "92000", "92235.proton" } );
      std::vector< multigroup::ScatteringMatrix > production = {

        multigroup::ScatteringMatrix( 0, { { 0, { 1, 0, 0,
                                                  0, 1, 0,
                                                  0, 0, 1,
                                                  0, 1, 0,
                                                  1, 0, 0,
                                                  0, 1, 0,
                                                  0, 0, 1, }, 7, 3 },
                                           { 1, { 0, 0, 1,
                                                  0, 1, 0,
                                                  1, 0, 0,
                                                  0, 1, 0,
                                                  0, 0, 1,
                                                  0, 1, 0,
                                                  1, 0, 0 }, 7, 3 } } ),
        multigroup::ScatteringMatrix( 1001, { { 0, { 1, 0,
                                                     0, 1,
                                                     1, 0,
                                                     0, 1,
                                                     1, 0,
                                                     0, 1,
                                                     1, 0, }, 7, 2 },
                                              { 1, { 0, 1,
                                                     1, 0,
                                                     0, 1,
                                                     1, 0,
                                                     0, 1,
                                                     1, 0,
                                                     0, 1 }, 7, 2 } } )
      };
      multigroup::HeatingNumbers primaryHeating( { 11., 22., 33., 44., 55., 66., 77. } );
      std::vector< multigroup::HeatingNumbers > outgoingHeating =   {
          { 0, { 21., 11., 5.1, 3., 4., 6., 7. } },
          { 1001, { 25., 15., 9.1, 7., 8., 10., 11. } }
      };
      multigroup::Kerma primaryKerma( { 110., 220., 330., 440., 550., 660., 770. } );
      std::vector< multigroup::Kerma > outgoingKerma =   {
          { 0, { 210., 110., 51., 30., 40., 60., 70. } },
          { 1001, { 250., 150., 91., 70., 80., 100., 110. } }
      };

      MultigroupTable chunk( std::move( zaid ), std::move( name ),
                             std::move( process ), awr, temperature, dilution,
                             std::move( structure ), std::move( outgoing ),
                             std::move( velocities ), std::move( weights ),
                             std::move( total ), std::move( xs ), std::move( scattering ),
                             std::move( information ), std::move( source ), weight,
                             std::move( release ), std::move( types ), std::move( transport ),
                             std::move( production ),
                             std::move( primaryHeating ), std::move( outgoingHeating ),
                             std::move( primaryKerma ), std::move( outgoingKerma ) );

      THEN( "a MultigroupTable can be constructed and members can "
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

      auto iter = record.begin();
      auto end = record.end();

      MultigroupTable chunk;
      chunk.read( iter, end );

      THEN( "a MultigroupTable can be constructed and members can "
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

  GIVEN( "invalid data for a MultigroupTable instance" ) {

    WHEN( "required records are missing" ) {

      std::string record = chunkWithMissingRecords();
      auto iter = record.begin();
      auto end = record.end();

      MultigroupTable chunk;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk.read( iter, end ) );
      } // THEN
    } // WHEN

    WHEN( "the number of groups is inconsistent" ) {

      std::string zaid = "92235.711nm";
      std::string information = "this is some information for the table";
      std::string name = "mendf71x";
      std::string source = "12/22/2011";
      std::string process = "08/07/2013";
      double awr = 233.0248;
      double weight = 235.043937521619;
      double temperature = 2.53e-8;
      double dilution = 1e+10;
      multigroup::EnergyGroupStructure structure( { 20., 18., 16., 14., 10., 5, 1, 1e-11 } );            // <-- 7 groups
      multigroup::Velocities velocities( { 2.1, 2.2, 2.25, 2.05 } );                                     // <-- 4 groups
      multigroup::FluxWeights weights( { 0.1, 0.2, 0.25, 0.05, 0.15, 0.04 } );                           // <-- 6 groups
      multigroup::TotalCrossSection total( { 1.1, 1.2, 1.25, 1.05, 1.15, 1.04 } );                       // <-- 5 groups
      multigroup::ReactionCrossSections xs( { { 2, 0.0, { 10., 20., 30., 40., 50., 60., 70., 80. } },    // <-- 8 groups
                                              { 16, 1.1234567, { 1., 2., 3., 4., 5., 6., 7., 8. } } } );
      multigroup::ScatteringMatrix scattering( { { 0, { 1, 0, 0, 0, 0, 0, 0,
                                                        0, 1, 0, 0, 0, 0, 0,
                                                        0, 0, 1, 0, 0, 0, 0,
                                                        0, 0, 0, 1, 0, 0, 0,
                                                        0, 0, 0, 0, 1, 0, 0,
                                                        0, 0, 0, 0, 0, 1, 0,
                                                        0, 0, 0, 0, 0, 0, 1 }, 7 },
                                                 { 1, { 0, 0, 0, 0, 0, 0, 1,
                                                        0, 0, 0, 0, 0, 1, 0,
                                                        0, 0, 0, 0, 1, 0, 0,
                                                        0, 0, 0, 1, 0, 0, 0,
                                                        0, 0, 1, 0, 0, 0, 0,
                                                        0, 1, 0, 0, 0, 0, 0,
                                                        1, 0, 0, 0, 0, 0, 0 }, 7 } } );
      multigroup::AverageFissionEnergyRelease release( 202.827, 181.238898, 4.827645,
                                                       7.281253, 6.5, 169.13 );
      multigroup::OutgoingParticleTypes types( { 0, 1001 } );
      multigroup::OutgoingParticleTransportData transport( { "92000", "92235.proton" } );
      std::vector< multigroup::ScatteringMatrix > production = {

        multigroup::ScatteringMatrix( 0, { { 0, { 1, 0, 0,
                                                  0, 1, 0,
                                                  0, 0, 1,
                                                  0, 1, 0,
                                                  1, 0, 0,
                                                  0, 1, 0,
                                                  0, 0, 1, }, 7, 3 },
                                           { 1, { 0, 0, 1,
                                                  0, 1, 0,
                                                  1, 0, 0,
                                                  0, 1, 0,
                                                  0, 0, 1,
                                                  0, 1, 0,
                                                  1, 0, 0 }, 7, 3 } } ),
        multigroup::ScatteringMatrix( 1001, { { 0, { 1, 0,
                                                     0, 1,
                                                     1, 0,
                                                     0, 1,
                                                     1, 0,
                                                     0, 1,
                                                     1, 0, }, 7, 2 },
                                              { 1, { 0, 1,
                                                     1, 0,
                                                     0, 1,
                                                     1, 0,
                                                     0, 1,
                                                     1, 0,
                                                     0, 1 }, 7, 2 } } )
      };
      multigroup::HeatingNumbers primaryHeating( { 11., 22., 33., 44., 55., 66., 77. } );
      std::vector< multigroup::HeatingNumbers > outgoingHeating =   {
          { 0, { 21., 11., 5.1, 3., 4., 6., 7. } },
          { 1001, { 25., 15., 9.1, 7., 8., 10., 11. } }
      };
      multigroup::Kerma primaryKerma( { 110., 220., 330., 440., 550., 660., 770. } );
      std::vector< multigroup::Kerma > outgoingKerma =   {
          { 0, { 210., 110., 51., 30., 40., 60., 70. } },
          { 1001, { 250., 150., 91., 70., 80., 100., 110. } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MultigroupTable( std::move( zaid ), std::move( name ),
                                       std::move( process ), awr, temperature, dilution,
                                       std::move( structure ), {}, std::move( velocities ),
                                       std::move( weights ), std::move( total ), std::move( xs ),
                                       std::move( scattering ), std::move( information ),
                                       std::move( source ), weight, std::move( release ),
                                       std::move( types ), std::move( transport ),
                                       std::move( production ),
                                       std::move( primaryHeating ), std::move( outgoingHeating ),
                                       std::move( primaryKerma ), std::move( outgoingKerma ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "zaid\n"
         "    92235.711nm\n"
         "info\n"
         "    this is some information for the table\n"
         "library_name\n"
         "    mendf71x\n"
         "date_source\n"
         "    12/22/2011\n"
         "date_processed\n"
         "    08/07/2013\n"
         "awr\n"
         "    233.0248\n"
         "at_wgt\n"
         "    235.043937521619\n"
         "temp\n"
         "    2.53e-08\n"
         "sig_0\n"
         "    10000000000\n"
         "num_grps\n"
         "    7\n"
         "num_reac\n"
         "    2\n"
         "pn_order\n"
         "    2\n"
         "num_sec_parts\n"
         "    2\n"
         "num_grps_0\n"
         "    3\n"
         "num_grps_1001\n"
         "    2\n"
         "pn_order_0\n"
         "    2\n"
         "pn_order_1001\n"
         "    2\n"
         "e_bounds\n"
         "    20 18.123456789 16.0000000000001 14 10\n"
         "    5 1 1e-11\n"
         "vel\n"
         "    2.1 2.2 2.25 2.05 2.15\n"
         "    2.04 2.06\n"
         "wgts\n"
         "    0.1 0.2 0.25 0.05 0.15\n"
         "    0.04 0.06\n"
         "sig_tot\n"
         "    1.1 1.2 1.25 1.05 1.15\n"
         "    1.04 1.06\n"
         "sig_reac\n"
         "    2 0\n"
         "    10 20 30 40 50\n"
         "    60 70\n"
         "    16 1.1234567\n"
         "    1 2 3 4 5\n"
         "    6 7\n"
         "pn_full\n"
         "    0\n"
         "    1 0 0 0 0\n"
         "    0 0 0 1 0\n"
         "    0 0 0 0 0\n"
         "    0 1 0 0 0\n"
         "    0 0 0 0 1\n"
         "    0 0 0 0 0\n"
         "    0 0 1 0 0\n"
         "    0 0 0 0 0\n"
         "    1 0 0 0 0\n"
         "    0 0 0 1\n"
         "    1\n"
         "    0 0 0 0 0\n"
         "    0 1 0 0 0\n"
         "    0 0 1 0 0\n"
         "    0 0 0 1 0\n"
         "    0 0 0 0 1\n"
         "    0 0 0 0 0\n"
         "    1 0 0 0 0\n"
         "    0 1 0 0 0\n"
         "    0 0 1 0 0\n"
         "    0 0 0 0\n"
         "fiss_q\n"
         "    181.238898 202.827 6.5 7.281253 169.13\n"
         "    4.827645\n"
         "heating\n"
         "    11 22 33 44 55\n"
         "    66 77\n"
         "kerma\n"
         "    110 220 330 440 550\n"
         "    660 770\n"
         "sec_part_types\n"
         "    0 1001\n"
         "sec_part_zaids\n"
         "    92000 92235.proton\n"
         "e_bounds_0\n"
         "    20 10 5 1e-11\n"
         "e_bounds_1001\n"
         "    20 10 1e-11\n"
         "pn_prod_full_0\n"
         "    0\n"
         "    1 0 0 0 1\n"
         "    0 0 0 1 0\n"
         "    1 0 1 0 0\n"
         "    0 1 0 0 0\n"
         "    1\n"
         "    1\n"
         "    0 0 1 0 1\n"
         "    0 1 0 0 0\n"
         "    1 0 0 0 1\n"
         "    0 1 0 1 0\n"
         "    0\n"
         "pn_prod_full_1001\n"
         "    0\n"
         "    1 0 0 1 1\n"
         "    0 0 1 1 0\n"
         "    0 1 1 0\n"
         "    1\n"
         "    0 1 1 0 0\n"
         "    1 1 0 0 1\n"
         "    1 0 0 1\n"
         "heating_0\n"
         "    21 11 5.1 3 4\n"
         "    6 7\n"
         "heating_1001\n"
         "    25 15 9.1 7 8\n"
         "    10 11\n"
         "kerma_0\n"
         "    210 110 51 30 40\n"
         "    60 70\n"
         "kerma_1001\n"
         "    250 150 91 70 80\n"
         "    100 110\n"
         "end\n";
}

void verifyChunk( const MultigroupTable& chunk ) {

  // metadata
  CHECK( "92235.711nm" == chunk.metadata().zaid() );
  CHECK( "this is some information for the table" == chunk.metadata().information() );
  CHECK( "mendf71x" == chunk.metadata().libraryName() );
  CHECK( "12/22/2011" == chunk.metadata().sourceDate() );
  CHECK( "08/07/2013" == chunk.metadata().processingDate() );
  CHECK_THAT( 233.0248, WithinRel( chunk.metadata().atomicWeightRatio().value() ) );
  CHECK_THAT( 235.043937521619, WithinRel( chunk.metadata().atomicWeight().value() ) );
  CHECK_THAT( 2.53e-8, WithinRel( chunk.metadata().temperature().value() ) );
  CHECK_THAT( 1e+10, WithinRel( chunk.metadata().dilution().value() ) );
  CHECK( 7 == chunk.metadata().numberGroups() );
  CHECK( 2 == chunk.metadata().numberReactions() );
  CHECK( 2 == chunk.metadata().numberOutgoingParticles() );
  CHECK( 2 == chunk.metadata().numberLegendreMoments() );
  CHECK( 2 == chunk.metadata().numberOutgoingLegendreMoments( 0 ) );
  CHECK( 2 == chunk.metadata().numberOutgoingLegendreMoments( 1001 ) );

  // principal group structure
  auto structure = chunk.primaryGroupBoundaries();
  CHECK( "e_bounds" == structure.keyword() );
  CHECK( std::nullopt == structure.particle() );
  CHECK( false == structure.empty() );
  CHECK( 8 == structure.size() );
  CHECK( 8 == structure.values().size() );
  CHECK( 7 == structure.numberGroups() );
  CHECK_THAT(    20, WithinRel( structure.values()[0] ) );
  CHECK_THAT(    18.123456789, WithinRel( structure.values()[1] ) );
  CHECK_THAT(    16.0000000000001, WithinRel( structure.values()[2] ) );
  CHECK_THAT(    14, WithinRel( structure.values()[3] ) );
  CHECK_THAT(    10, WithinRel( structure.values()[4] ) );
  CHECK_THAT(     5, WithinRel( structure.values()[5] ) );
  CHECK_THAT(     1, WithinRel( structure.values()[6] ) );
  CHECK_THAT( 1e-11, WithinRel( structure.values()[7] ) );

  // velocity values
  auto velocities = chunk.velocities();
  CHECK( "vel" == velocities.keyword() );
  CHECK( false == velocities.empty() );
  CHECK( 7 == velocities.size() );
  CHECK( 7 == velocities.values().size() );
  CHECK( 7 == velocities.numberGroups() );
  CHECK_THAT( 2.10, WithinRel( velocities.values()[0] ) );
  CHECK_THAT( 2.20, WithinRel( velocities.values()[1] ) );
  CHECK_THAT( 2.25, WithinRel( velocities.values()[2] ) );
  CHECK_THAT( 2.05, WithinRel( velocities.values()[3] ) );
  CHECK_THAT( 2.15, WithinRel( velocities.values()[4] ) );
  CHECK_THAT( 2.04, WithinRel( velocities.values()[5] ) );
  CHECK_THAT( 2.06, WithinRel( velocities.values()[6] ) );

  // flux values
  auto flux = chunk.fluxWeights();
  CHECK( "wgts" == flux.keyword() );
  CHECK( false == flux.empty() );
  CHECK( 7 == flux.size() );
  CHECK( 7 == flux.values().size() );
  CHECK( 7 == flux.numberGroups() );
  CHECK_THAT( 0.10, WithinRel( flux.values()[0] ) );
  CHECK_THAT( 0.20, WithinRel( flux.values()[1] ) );
  CHECK_THAT( 0.25, WithinRel( flux.values()[2] ) );
  CHECK_THAT( 0.05, WithinRel( flux.values()[3] ) );
  CHECK_THAT( 0.15, WithinRel( flux.values()[4] ) );
  CHECK_THAT( 0.04, WithinRel( flux.values()[5] ) );
  CHECK_THAT( 0.06, WithinRel( flux.values()[6] ) );

  // total cross section
  CHECK( "sig_tot" == chunk.totalCrossSection().keyword() );
  CHECK( false == chunk.totalCrossSection().empty() );
  CHECK( 7 == chunk.totalCrossSection().size() );
  CHECK( 7 == chunk.totalCrossSection().values().size() );
  CHECK( 7 == chunk.totalCrossSection().numberGroups() );
  CHECK_THAT( 1.10, WithinRel( chunk.totalCrossSection().values()[0] ) );
  CHECK_THAT( 1.20, WithinRel( chunk.totalCrossSection().values()[1] ) );
  CHECK_THAT( 1.25, WithinRel( chunk.totalCrossSection().values()[2] ) );
  CHECK_THAT( 1.05, WithinRel( chunk.totalCrossSection().values()[3] ) );
  CHECK_THAT( 1.15, WithinRel( chunk.totalCrossSection().values()[4] ) );
  CHECK_THAT( 1.04, WithinRel( chunk.totalCrossSection().values()[5] ) );
  CHECK_THAT( 1.06, WithinRel( chunk.totalCrossSection().values()[6] ) );

  // reaction cross sections
  CHECK( 18 == chunk.reactionCrossSections().size() );
  CHECK( false == chunk.reactionCrossSections().empty() );
  CHECK( 2 == chunk.reactionCrossSections().numberReactions() );
  CHECK( 7 == chunk.reactionCrossSections().numberGroups() );
  CHECK( true == chunk.reactionCrossSections().hasReaction( 2 ) );
  CHECK( true == chunk.reactionCrossSections().hasReaction( 16 ) );
  CHECK( false == chunk.reactionCrossSections().hasReaction( 102 ) );
  CHECK( false == chunk.reactionCrossSections().reactions()[0].empty() );
  CHECK( 9 == chunk.reactionCrossSections().reactions()[0].size() );
  CHECK( 7 == chunk.reactionCrossSections().reactions()[0].numberGroups() );
  CHECK( 2 == chunk.reactionCrossSections().reactions()[0].identifier() );
  CHECK_THAT( 0.0, WithinRel( chunk.reactionCrossSections().reactions()[0].qvalue() ) );
  CHECK_THAT( 10.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[0] ) );
  CHECK_THAT( 20.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[1] ) );
  CHECK_THAT( 30.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[2] ) );
  CHECK_THAT( 40.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[3] ) );
  CHECK_THAT( 50.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[4] ) );
  CHECK_THAT( 60.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[5] ) );
  CHECK_THAT( 70.0, WithinRel( chunk.reactionCrossSections().reactions()[0].crossSections()[6] ) );
  CHECK( false == chunk.reactionCrossSections().reactions()[1].empty() );
  CHECK( 9 == chunk.reactionCrossSections().reactions()[1].size() );
  CHECK( 7 == chunk.reactionCrossSections().reactions()[1].numberGroups() );
  CHECK( 16 == chunk.reactionCrossSections().reactions()[1].identifier() );
  CHECK_THAT( 1.1234567, WithinRel( chunk.reactionCrossSections().reactions()[1].qvalue() ) );
  CHECK_THAT( 1.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[0] ) );
  CHECK_THAT( 2.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[1] ) );
  CHECK_THAT( 3.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[2] ) );
  CHECK_THAT( 4.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[3] ) );
  CHECK_THAT( 5.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[4] ) );
  CHECK_THAT( 6.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[5] ) );
  CHECK_THAT( 7.0, WithinRel( chunk.reactionCrossSections().reactions()[1].crossSections()[6] ) );
  auto xs = chunk.reactionCrossSections().reaction( 2 );
  CHECK( false == xs.empty() );
  CHECK( 9 == xs.size() );
  CHECK( 7 == xs.numberGroups() );
  CHECK( 2 == xs.identifier() );
  CHECK_THAT( 0.0, WithinRel( xs.qvalue() ) );
  CHECK_THAT( 10.0, WithinRel( xs.crossSections()[0] ) );
  CHECK_THAT( 20.0, WithinRel( xs.crossSections()[1] ) );
  CHECK_THAT( 30.0, WithinRel( xs.crossSections()[2] ) );
  CHECK_THAT( 40.0, WithinRel( xs.crossSections()[3] ) );
  CHECK_THAT( 50.0, WithinRel( xs.crossSections()[4] ) );
  CHECK_THAT( 60.0, WithinRel( xs.crossSections()[5] ) );
  CHECK_THAT( 70.0, WithinRel( xs.crossSections()[6] ) );
  xs = chunk.reactionCrossSections().reaction( 16 );
  CHECK( false == xs.empty() );
  CHECK( 9 == xs.size() );
  CHECK( 7 == xs.numberGroups() );
  CHECK( 16 == xs.identifier() );
  CHECK_THAT( 1.1234567, WithinRel( xs.qvalue() ) );
  CHECK_THAT( 1.0, WithinRel( xs.crossSections()[0] ) );
  CHECK_THAT( 2.0, WithinRel( xs.crossSections()[1] ) );
  CHECK_THAT( 3.0, WithinRel( xs.crossSections()[2] ) );
  CHECK_THAT( 4.0, WithinRel( xs.crossSections()[3] ) );
  CHECK_THAT( 5.0, WithinRel( xs.crossSections()[4] ) );
  CHECK_THAT( 6.0, WithinRel( xs.crossSections()[5] ) );
  CHECK_THAT( 7.0, WithinRel( xs.crossSections()[6] ) );

  // the scattering matrix
  CHECK( "pn_full" == chunk.scatteringMatrix().keyword() );
  CHECK( false == chunk.scatteringMatrix().empty() );
  CHECK( 100 == chunk.scatteringMatrix().size() );
  CHECK( 7 == chunk.scatteringMatrix().numberPrimaryGroups() );
  CHECK( 7 == chunk.scatteringMatrix().numberOutgoingGroups() );
  CHECK( 2 == chunk.scatteringMatrix().numberLegendreMoments() );
  auto moment = chunk.scatteringMatrix().moment( 0 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 7 == moment.matrix()[0].size() );
  CHECK( 0 == moment.order() );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][3] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][4] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][5] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][6] ) );
  moment = chunk.scatteringMatrix().moment( 1 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 7 == moment.matrix()[0].size() );
  CHECK( 1 == moment.order() );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][5] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][4] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][3] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][6] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][6] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][3] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][4] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][5] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][6] ) );

  // average fission energy release
  CHECK( "fiss_q" == chunk.averageFissionEnergyRelease().keyword() );
  CHECK( false == chunk.averageFissionEnergyRelease().empty() );
  CHECK( 6 == chunk.averageFissionEnergyRelease().size() );
  CHECK_THAT( 181.238898, WithinRel( chunk.averageFissionEnergyRelease().promptEnergyRelease() ) );
  CHECK_THAT(    202.827, WithinRel( chunk.averageFissionEnergyRelease().totalEnergyRelease() ) );
  CHECK_THAT(        6.5, WithinRel( chunk.averageFissionEnergyRelease().delayedBetas() ) );
  CHECK_THAT(   7.281253, WithinRel( chunk.averageFissionEnergyRelease().promptGammas() ) );
  CHECK_THAT(     169.13, WithinRel( chunk.averageFissionEnergyRelease().fissionFragments() ) );
  CHECK_THAT(   4.827645, WithinRel( chunk.averageFissionEnergyRelease().promptNeutrons() ) );

  // principal heating numbers
  auto heating = chunk.primaryHeatingNumbers();
  CHECK( "heating" == heating.keyword() );
  CHECK( std::nullopt == heating.particle() );
  CHECK( false == heating.empty() );
  CHECK( 7 == heating.size() );
  CHECK( 7 == heating.values().size() );
  CHECK( 7 == heating.numberGroups() );
  CHECK_THAT( 11, WithinRel( heating.values()[0] ) );
  CHECK_THAT( 22, WithinRel( heating.values()[1] ) );
  CHECK_THAT( 33, WithinRel( heating.values()[2] ) );
  CHECK_THAT( 44, WithinRel( heating.values()[3] ) );
  CHECK_THAT( 55, WithinRel( heating.values()[4] ) );
  CHECK_THAT( 66, WithinRel( heating.values()[5] ) );
  CHECK_THAT( 77, WithinRel( heating.values()[6] ) );

  // principal kerma
  auto kerma = chunk.primaryKerma();
  CHECK( "kerma" == kerma.keyword() );
  CHECK( std::nullopt == kerma.particle() );
  CHECK( false == kerma.empty() );
  CHECK( 7 == kerma.size() );
  CHECK( 7 == kerma.values().size() );
  CHECK( 7 == kerma.numberGroups() );
  CHECK_THAT( 110, WithinRel( kerma.values()[0] ) );
  CHECK_THAT( 220, WithinRel( kerma.values()[1] ) );
  CHECK_THAT( 330, WithinRel( kerma.values()[2] ) );
  CHECK_THAT( 440, WithinRel( kerma.values()[3] ) );
  CHECK_THAT( 550, WithinRel( kerma.values()[4] ) );
  CHECK_THAT( 660, WithinRel( kerma.values()[5] ) );
  CHECK_THAT( 770, WithinRel( kerma.values()[6] ) );

  // outgoing particle types
  auto types = chunk.outgoingParticleTypes();
  CHECK( "sec_part_types" == types.keyword() );
  CHECK( false == types.empty() );
  CHECK( 2 == types.size() );
  CHECK( 2 == types.values().size() );
  CHECK( 2 == types.numberOutgoingParticles() );
  CHECK(    0 == types.values()[0] );
  CHECK( 1001 == types.values()[1] );

  // outgoing particle transport data
  auto transport = chunk.outgoingParticleTransportData();
  CHECK( "sec_part_zaids" == transport.keyword() );
  CHECK( false == transport.empty() );
  CHECK( 2 == transport.size() );
  CHECK( 2 == transport.values().size() );
  CHECK( 2 == transport.numberOutgoingParticles() );
  CHECK( "92000" == transport.values()[0] );
  CHECK( "92235.proton" == transport.values()[1] );

  // outgoing group structure: 0
  structure = chunk.outgoingGroupBoundaries( 0 );
  CHECK( "e_bounds_0" == structure.keyword() );
  CHECK( 0 == structure.particle() );
  CHECK( false == structure.empty() );
  CHECK( 4 == structure.size() );
  CHECK( 4 == structure.values().size() );
  CHECK( 3 == structure.numberGroups() );
  CHECK_THAT(    20, WithinRel( structure.values()[0] ) );
  CHECK_THAT(    10, WithinRel( structure.values()[1] ) );
  CHECK_THAT(     5, WithinRel( structure.values()[2] ) );
  CHECK_THAT( 1e-11, WithinRel( structure.values()[3] ) );

  // outgoing group structure: 1001
  structure = chunk.outgoingGroupBoundaries( 1001 );
  CHECK( "e_bounds_1001" == structure.keyword() );
  CHECK( 1001 == structure.particle() );
  CHECK( false == structure.empty() );
  CHECK( 3 == structure.size() );
  CHECK( 3 == structure.values().size() );
  CHECK( 2 == structure.numberGroups() );
  CHECK_THAT(    20, WithinRel( structure.values()[0] ) );
  CHECK_THAT(    10, WithinRel( structure.values()[1] ) );
  CHECK_THAT( 1e-11, WithinRel( structure.values()[2] ) );

  // the outgoing production matrix: 0
  auto production = chunk.outgoingProductionMatrix( 0 );
  CHECK( "pn_prod_full_0" == production.keyword() );
  CHECK( 0 == production.particle() );
  CHECK( false == production.empty() );
  CHECK( 44 == production.size() );
  CHECK( 7 == production.numberPrimaryGroups() );
  CHECK( 3 == production.numberOutgoingGroups() );
  CHECK( 2 == production.numberLegendreMoments() );
  moment = production.moment( 0 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 3 == moment.matrix()[0].size() );
  CHECK( 0 == moment.order() );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][2] ) );
  moment = production.moment( 1 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 3 == moment.matrix()[0].size() );
  CHECK( 1 == moment.order() );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][2] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][2] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][2] ) );

  // the outgoing production matrix: 1001
  production = chunk.outgoingProductionMatrix( 1001 );
  CHECK( "pn_prod_full_1001" == production.keyword() );
  CHECK( 1001 == production.particle() );
  CHECK( false == production.empty() );
  CHECK( 30 == production.size() );
  CHECK( 7 == production.numberPrimaryGroups() );
  CHECK( 2 == production.numberOutgoingGroups() );
  CHECK( 2 == production.numberLegendreMoments() );
  moment = production.moment( 0 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 2 == moment.matrix()[0].size() );
  CHECK( 0 == moment.order() );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][1] ) );
  moment = production.moment( 1 );
  CHECK( 7 == moment.matrix().size() );
  CHECK( 2 == moment.matrix()[0].size() );
  CHECK( 1 == moment.order() );
  CHECK_THAT( 0, WithinRel( moment.matrix()[0][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[0][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[1][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[1][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[2][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[2][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[3][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[3][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[4][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[4][1] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[5][0] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[5][1] ) );
  CHECK_THAT( 0, WithinRel( moment.matrix()[6][0] ) );
  CHECK_THAT( 1, WithinRel( moment.matrix()[6][1] ) );

  // outgoing heating numbers: 0
  heating = chunk.outgoingHeatingNumbers( 0 );
  CHECK( "heating_0" == heating.keyword() );
  CHECK( 0 == heating.particle() );
  CHECK( false == heating.empty() );
  CHECK( 7 == heating.size() );
  CHECK( 7 == heating.values().size() );
  CHECK( 7 == heating.numberGroups() );
  CHECK_THAT(  21, WithinRel( heating.values()[0] ) );
  CHECK_THAT(  11, WithinRel( heating.values()[1] ) );
  CHECK_THAT( 5.1, WithinRel( heating.values()[2] ) );
  CHECK_THAT(   3, WithinRel( heating.values()[3] ) );
  CHECK_THAT(   4, WithinRel( heating.values()[4] ) );
  CHECK_THAT(   6, WithinRel( heating.values()[5] ) );
  CHECK_THAT(   7, WithinRel( heating.values()[6] ) );

  // outgoing heating numbers: 1001
  heating = chunk.outgoingHeatingNumbers( 1001 );
  CHECK( "heating_1001" == heating.keyword() );
  CHECK( 1001 == heating.particle() );
  CHECK( false == heating.empty() );
  CHECK( 7 == heating.size() );
  CHECK( 7 == heating.values().size() );
  CHECK( 7 == heating.numberGroups() );
  CHECK_THAT(  25, WithinRel( heating.values()[0] ) );
  CHECK_THAT(  15, WithinRel( heating.values()[1] ) );
  CHECK_THAT( 9.1, WithinRel( heating.values()[2] ) );
  CHECK_THAT(   7, WithinRel( heating.values()[3] ) );
  CHECK_THAT(   8, WithinRel( heating.values()[4] ) );
  CHECK_THAT(  10, WithinRel( heating.values()[5] ) );
  CHECK_THAT(  11, WithinRel( heating.values()[6] ) );

  // outgoing kerma: 0
  kerma = chunk.outgoingKerma( 0 );
  CHECK( "kerma_0" == kerma.keyword() );
  CHECK( 0 == kerma.particle() );
  CHECK( false == kerma.empty() );
  CHECK( 7 == kerma.size() );
  CHECK( 7 == kerma.values().size() );
  CHECK( 7 == kerma.numberGroups() );
  CHECK_THAT(  210, WithinRel( kerma.values()[0] ) );
  CHECK_THAT(  110, WithinRel( kerma.values()[1] ) );
  CHECK_THAT(   51, WithinRel( kerma.values()[2] ) );
  CHECK_THAT(   30, WithinRel( kerma.values()[3] ) );
  CHECK_THAT(   40, WithinRel( kerma.values()[4] ) );
  CHECK_THAT(   60, WithinRel( kerma.values()[5] ) );
  CHECK_THAT(   70, WithinRel( kerma.values()[6] ) );

  // outgoing kerma: 1001
  kerma = chunk.outgoingKerma( 1001 );
  CHECK( "kerma_1001" == kerma.keyword() );
  CHECK( 1001 == kerma.particle() );
  CHECK( false == kerma.empty() );
  CHECK( 7 == kerma.size() );
  CHECK( 7 == kerma.values().size() );
  CHECK( 7 == kerma.numberGroups() );
  CHECK_THAT(  250, WithinRel( kerma.values()[0] ) );
  CHECK_THAT(  150, WithinRel( kerma.values()[1] ) );
  CHECK_THAT(   91, WithinRel( kerma.values()[2] ) );
  CHECK_THAT(   70, WithinRel( kerma.values()[3] ) );
  CHECK_THAT(   80, WithinRel( kerma.values()[4] ) );
  CHECK_THAT(  100, WithinRel( kerma.values()[5] ) );
  CHECK_THAT(  110, WithinRel( kerma.values()[6] ) );
}

std::string chunkWithMissingRecords() {

  // e_bounds and wgts are not present
  return "zaid\n"
         "    92235.711nm\n"
         "library_name\n"
         "    mendf71x\n"
         "date_source\n"
         "    12/22/2011\n"
         "date_processed\n"
         "    08/07/2013\n"
         "awr\n"
         "    233.0248\n"
         "at_wgt\n"
         "    235.043937521619\n"
         "temp\n"
         "    2.53e-08\n"
         "sig_0\n"
         "    10000000000\n"
         "num_grps\n"
         "    7\n"
         "num_grps_0\n"
         "    3\n"
         "num_grps_1001\n"
         "    2\n"
         "num_reac\n"
         "    2\n"
         "e_bounds_0\n"
         "    20 10 5 1e-11\n"
         "e_bounds_1001\n"
         "    20 10 1e-11\n"
         "vel\n"
         "    2.1 2.2 2.25 2.05 2.15\n"
         "    2.04 2.06\n"
         "sig_tot\n"
         "    1.1 1.2 1.25 1.05 1.15\n"
         "    1.04 1.06\n"
         "sig_reac\n"
         "    2 0\n"
         "    10 20 30 40 50\n"
         "    60 70\n"
         "    16 1.1234567\n"
         "    1 2 3 4 5\n"
         "    6 7\n"
         "fiss_q\n"
         "    181.238898 202.827 6.5 7.281253 169.13\n"
         "    4.827645\n"
         "end\n";
}
