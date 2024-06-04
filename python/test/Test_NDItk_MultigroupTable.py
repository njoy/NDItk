# standard imports
import unittest
import os

# third party imports

# local imports
from NDItk import MultigroupTable
from NDItk.multigroup import AverageFissionEnergyRelease
from NDItk.multigroup import EnergyGroupStructure
from NDItk.multigroup import FluxWeights
from NDItk.multigroup import TotalCrossSection
from NDItk.multigroup import ReactionCrossSections
from NDItk.multigroup import CrossSection
from NDItk.multigroup import Velocities
from NDItk.multigroup import HeatingNumbers
from NDItk.multigroup import Kerma
from NDItk.multigroup import OutgoingParticleTypes
from NDItk.multigroup import OutgoingParticleTransportData
from NDItk.multigroup import LegendreMoment
from NDItk.multigroup import ScatteringMatrix

class Test_NDItk_MultigroupTable( unittest.TestCase ) :
    """Unit test for the MultigroupTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content - metadata
            metadata = chunk.metadata
            self.assertEqual( '92235.711nm', metadata.zaid )
            self.assertEqual( 'this is some information for the table', metadata.information )
            self.assertEqual( 'mendf71x', metadata.library_name )
            self.assertEqual( '12/22/2011', metadata.source_date )
            self.assertEqual( '08/07/2013', metadata.processing_date )
            self.assertAlmostEqual( 233.0248, metadata.atomic_weight_ratio )
            self.assertAlmostEqual( 235.043937521619, metadata.atomic_weight )
            self.assertAlmostEqual( 2.53e-8, metadata.temperature )
            self.assertAlmostEqual( 1e+10, metadata.dilution )
            self.assertEqual( 7, metadata.number_groups )
            self.assertEqual( 3, metadata.number_outgoing_groups( 0 ) )
            self.assertEqual( 2, metadata.number_outgoing_groups( 1001 ) )
            self.assertEqual( 2, metadata.number_reactions )
            self.assertEqual( 2, metadata.number_legendre_moments )
            self.assertEqual( 2, metadata.number_outgoing_legendre_moments( 0 ) )
            self.assertEqual( 2, metadata.number_outgoing_legendre_moments( 1001 ) )

            # verify content - primary energy boundaries
            structure = chunk.primary_group_boundaries
            self.assertEqual( 7, structure.number_groups )
            self.assertAlmostEqual(    20, structure.values[0] )
            self.assertAlmostEqual(    18.123456789, structure.values[1] )
            self.assertAlmostEqual(    16.0000000000001, structure.values[2] )
            self.assertAlmostEqual(    14, structure.values[3] )
            self.assertAlmostEqual(    10, structure.values[4] )
            self.assertAlmostEqual(     5, structure.values[5] )
            self.assertAlmostEqual(     1, structure.values[6] )
            self.assertAlmostEqual( 1e-11, structure.values[7] )

            # verify content - velocities
            velocities = chunk.velocities
            self.assertEqual( 7, velocities.number_groups )
            self.assertAlmostEqual( 2.10, velocities.values[0] )
            self.assertAlmostEqual( 2.20, velocities.values[1] )
            self.assertAlmostEqual( 2.25, velocities.values[2] )
            self.assertAlmostEqual( 2.05, velocities.values[3] )
            self.assertAlmostEqual( 2.15, velocities.values[4] )
            self.assertAlmostEqual( 2.04, velocities.values[5] )
            self.assertAlmostEqual( 2.06, velocities.values[6] )

            # verify content - flux weights
            flux = chunk.flux_weights
            self.assertEqual( 7, flux.number_groups )
            self.assertAlmostEqual( 0.10, flux.values[0] )
            self.assertAlmostEqual( 0.20, flux.values[1] )
            self.assertAlmostEqual( 0.25, flux.values[2] )
            self.assertAlmostEqual( 0.05, flux.values[3] )
            self.assertAlmostEqual( 0.15, flux.values[4] )
            self.assertAlmostEqual( 0.04, flux.values[5] )
            self.assertAlmostEqual( 0.06, flux.values[6] )

            # verify content - total cross section
            total = chunk.total_cross_section
            self.assertEqual( 7, total.number_groups )
            self.assertAlmostEqual( 1.10, total.values[0] )
            self.assertAlmostEqual( 1.20, total.values[1] )
            self.assertAlmostEqual( 1.25, total.values[2] )
            self.assertAlmostEqual( 1.05, total.values[3] )
            self.assertAlmostEqual( 1.15, total.values[4] )
            self.assertAlmostEqual( 1.04, total.values[5] )
            self.assertAlmostEqual( 1.06, total.values[6] )

            # verify content - reaction cross sections
            reactions = chunk.reaction_cross_sections
            self.assertEqual( 2, reactions.number_reactions )
            self.assertEqual( 7, reactions.number_groups )
            self.assertEqual( True, reactions.has_reaction( 2 ) )
            self.assertEqual( True, reactions.has_reaction( 16 ) )
            self.assertEqual( False, reactions.has_reaction( 102 ) )
            self.assertEqual( 2, reactions.reactions[0].identifier )
            self.assertAlmostEqual( 0.0, reactions.reactions[0].qvalue )
            self.assertAlmostEqual( 10.0, reactions.reactions[0].cross_sections[0] )
            self.assertAlmostEqual( 20.0, reactions.reactions[0].cross_sections[1] )
            self.assertAlmostEqual( 30.0, reactions.reactions[0].cross_sections[2] )
            self.assertAlmostEqual( 40.0, reactions.reactions[0].cross_sections[3] )
            self.assertAlmostEqual( 50.0, reactions.reactions[0].cross_sections[4] )
            self.assertAlmostEqual( 60.0, reactions.reactions[0].cross_sections[5] )
            self.assertAlmostEqual( 70.0, reactions.reactions[0].cross_sections[6] )

            self.assertEqual( 16, reactions.reactions[1].identifier )
            self.assertAlmostEqual( 1.1234567, reactions.reactions[1].qvalue )
            self.assertAlmostEqual( 1.0, reactions.reactions[1].cross_sections[0] )
            self.assertAlmostEqual( 2.0, reactions.reactions[1].cross_sections[1] )
            self.assertAlmostEqual( 3.0, reactions.reactions[1].cross_sections[2] )
            self.assertAlmostEqual( 4.0, reactions.reactions[1].cross_sections[3] )
            self.assertAlmostEqual( 5.0, reactions.reactions[1].cross_sections[4] )
            self.assertAlmostEqual( 6.0, reactions.reactions[1].cross_sections[5] )
            self.assertAlmostEqual( 7.0, reactions.reactions[1].cross_sections[6] )

            xs = reactions.reaction( 2 )
            self.assertEqual( 2, xs.identifier )
            self.assertAlmostEqual( 0.0, xs.qvalue )
            self.assertAlmostEqual( 10.0, xs.cross_sections[0] )
            self.assertAlmostEqual( 20.0, xs.cross_sections[1] )
            self.assertAlmostEqual( 30.0, xs.cross_sections[2] )
            self.assertAlmostEqual( 40.0, xs.cross_sections[3] )
            self.assertAlmostEqual( 50.0, xs.cross_sections[4] )
            self.assertAlmostEqual( 60.0, xs.cross_sections[5] )
            self.assertAlmostEqual( 70.0, xs.cross_sections[6] )

            xs = reactions.reaction( 16 )
            self.assertEqual( 16, xs.identifier )
            self.assertAlmostEqual( 1.1234567, xs.qvalue )
            self.assertAlmostEqual( 1.0, xs.cross_sections[0] )
            self.assertAlmostEqual( 2.0, xs.cross_sections[1] )
            self.assertAlmostEqual( 3.0, xs.cross_sections[2] )
            self.assertAlmostEqual( 4.0, xs.cross_sections[3] )
            self.assertAlmostEqual( 5.0, xs.cross_sections[4] )
            self.assertAlmostEqual( 6.0, xs.cross_sections[5] )
            self.assertAlmostEqual( 7.0, xs.cross_sections[6] )

            # verify content - scattering matrix
            matrix = chunk.scattering_matrix
            self.assertEqual( "pn_full", matrix.keyword )
            self.assertEqual( False, matrix.empty )
            self.assertEqual( 100, matrix.size )
            self.assertEqual( 7, matrix.number_primary_groups )
            self.assertEqual( 7, matrix.number_outgoing_groups )
            self.assertEqual( 2, matrix.number_legendre_moments )
            moment = matrix.moment( 0 )
            self.assertEqual( 7, len( moment.matrix ) )
            self.assertEqual( 7, len( moment.matrix[0] ) )
            self.assertEqual( 0, moment.order )
            self.assertAlmostEqual( 1, moment.matrix[0][0] )
            self.assertAlmostEqual( 0, moment.matrix[0][1] )
            self.assertAlmostEqual( 0, moment.matrix[0][2] )
            self.assertAlmostEqual( 0, moment.matrix[0][3] )
            self.assertAlmostEqual( 0, moment.matrix[0][4] )
            self.assertAlmostEqual( 0, moment.matrix[0][5] )
            self.assertAlmostEqual( 0, moment.matrix[0][6] )
            self.assertAlmostEqual( 0, moment.matrix[1][0] )
            self.assertAlmostEqual( 1, moment.matrix[1][1] )
            self.assertAlmostEqual( 0, moment.matrix[1][2] )
            self.assertAlmostEqual( 0, moment.matrix[1][3] )
            self.assertAlmostEqual( 0, moment.matrix[1][4] )
            self.assertAlmostEqual( 0, moment.matrix[1][5] )
            self.assertAlmostEqual( 0, moment.matrix[1][6] )
            self.assertAlmostEqual( 0, moment.matrix[2][0] )
            self.assertAlmostEqual( 0, moment.matrix[2][1] )
            self.assertAlmostEqual( 1, moment.matrix[2][2] )
            self.assertAlmostEqual( 0, moment.matrix[2][3] )
            self.assertAlmostEqual( 0, moment.matrix[2][4] )
            self.assertAlmostEqual( 0, moment.matrix[2][5] )
            self.assertAlmostEqual( 0, moment.matrix[2][6] )
            self.assertAlmostEqual( 0, moment.matrix[3][0] )
            self.assertAlmostEqual( 0, moment.matrix[3][1] )
            self.assertAlmostEqual( 0, moment.matrix[3][2] )
            self.assertAlmostEqual( 1, moment.matrix[3][3] )
            self.assertAlmostEqual( 0, moment.matrix[3][4] )
            self.assertAlmostEqual( 0, moment.matrix[3][5] )
            self.assertAlmostEqual( 0, moment.matrix[3][6] )
            self.assertAlmostEqual( 0, moment.matrix[4][0] )
            self.assertAlmostEqual( 0, moment.matrix[4][1] )
            self.assertAlmostEqual( 0, moment.matrix[4][2] )
            self.assertAlmostEqual( 0, moment.matrix[4][3] )
            self.assertAlmostEqual( 1, moment.matrix[4][4] )
            self.assertAlmostEqual( 0, moment.matrix[4][5] )
            self.assertAlmostEqual( 0, moment.matrix[4][6] )
            self.assertAlmostEqual( 0, moment.matrix[5][0] )
            self.assertAlmostEqual( 0, moment.matrix[5][1] )
            self.assertAlmostEqual( 0, moment.matrix[5][2] )
            self.assertAlmostEqual( 0, moment.matrix[5][3] )
            self.assertAlmostEqual( 0, moment.matrix[5][4] )
            self.assertAlmostEqual( 1, moment.matrix[5][5] )
            self.assertAlmostEqual( 0, moment.matrix[5][6] )
            self.assertAlmostEqual( 0, moment.matrix[6][0] )
            self.assertAlmostEqual( 0, moment.matrix[6][1] )
            self.assertAlmostEqual( 0, moment.matrix[6][2] )
            self.assertAlmostEqual( 0, moment.matrix[6][3] )
            self.assertAlmostEqual( 0, moment.matrix[6][4] )
            self.assertAlmostEqual( 0, moment.matrix[6][5] )
            self.assertAlmostEqual( 1, moment.matrix[6][6] )
            moment = matrix.moment( 1 )
            self.assertEqual( 7, len( moment.matrix ) )
            self.assertEqual( 7, len( moment.matrix[0] ) )
            self.assertEqual( 1, moment.order )
            self.assertAlmostEqual( 0, moment.matrix[0][0] )
            self.assertAlmostEqual( 0, moment.matrix[0][1] )
            self.assertAlmostEqual( 0, moment.matrix[0][2] )
            self.assertAlmostEqual( 0, moment.matrix[0][3] )
            self.assertAlmostEqual( 0, moment.matrix[0][4] )
            self.assertAlmostEqual( 0, moment.matrix[0][5] )
            self.assertAlmostEqual( 1, moment.matrix[0][6] )
            self.assertAlmostEqual( 0, moment.matrix[1][0] )
            self.assertAlmostEqual( 0, moment.matrix[1][1] )
            self.assertAlmostEqual( 0, moment.matrix[1][2] )
            self.assertAlmostEqual( 0, moment.matrix[1][3] )
            self.assertAlmostEqual( 0, moment.matrix[1][4] )
            self.assertAlmostEqual( 1, moment.matrix[1][5] )
            self.assertAlmostEqual( 0, moment.matrix[1][6] )
            self.assertAlmostEqual( 0, moment.matrix[2][0] )
            self.assertAlmostEqual( 0, moment.matrix[2][1] )
            self.assertAlmostEqual( 0, moment.matrix[2][2] )
            self.assertAlmostEqual( 0, moment.matrix[2][3] )
            self.assertAlmostEqual( 1, moment.matrix[2][4] )
            self.assertAlmostEqual( 0, moment.matrix[2][5] )
            self.assertAlmostEqual( 0, moment.matrix[2][6] )
            self.assertAlmostEqual( 0, moment.matrix[3][0] )
            self.assertAlmostEqual( 0, moment.matrix[3][1] )
            self.assertAlmostEqual( 0, moment.matrix[3][2] )
            self.assertAlmostEqual( 1, moment.matrix[3][3] )
            self.assertAlmostEqual( 0, moment.matrix[3][4] )
            self.assertAlmostEqual( 0, moment.matrix[3][5] )
            self.assertAlmostEqual( 0, moment.matrix[3][6] )
            self.assertAlmostEqual( 0, moment.matrix[4][0] )
            self.assertAlmostEqual( 0, moment.matrix[4][1] )
            self.assertAlmostEqual( 1, moment.matrix[4][2] )
            self.assertAlmostEqual( 0, moment.matrix[4][3] )
            self.assertAlmostEqual( 0, moment.matrix[4][4] )
            self.assertAlmostEqual( 0, moment.matrix[4][5] )
            self.assertAlmostEqual( 0, moment.matrix[4][6] )
            self.assertAlmostEqual( 0, moment.matrix[5][0] )
            self.assertAlmostEqual( 1, moment.matrix[5][1] )
            self.assertAlmostEqual( 0, moment.matrix[5][2] )
            self.assertAlmostEqual( 0, moment.matrix[5][3] )
            self.assertAlmostEqual( 0, moment.matrix[5][4] )
            self.assertAlmostEqual( 0, moment.matrix[5][5] )
            self.assertAlmostEqual( 0, moment.matrix[5][6] )
            self.assertAlmostEqual( 1, moment.matrix[6][0] )
            self.assertAlmostEqual( 0, moment.matrix[6][1] )
            self.assertAlmostEqual( 0, moment.matrix[6][2] )
            self.assertAlmostEqual( 0, moment.matrix[6][3] )
            self.assertAlmostEqual( 0, moment.matrix[6][4] )
            self.assertAlmostEqual( 0, moment.matrix[6][5] )
            self.assertAlmostEqual( 0, moment.matrix[6][6] )

            # verify content - average fission energy release
            release = chunk.average_fission_energy_release
            self.assertAlmostEqual( 181.238898, release.prompt_energy_release )
            self.assertAlmostEqual(    202.827, release.total_energy_release )
            self.assertAlmostEqual(        6.5, release.delayed_betas )
            self.assertAlmostEqual(   7.281253, release.prompt_gammas )
            self.assertAlmostEqual(     169.13, release.fission_fragments )
            self.assertAlmostEqual(   4.827645, release.prompt_neutrons )

            # verify content - primary heating numbers
            heating = chunk.primary_heating_numbers
            self.assertEqual( 7, heating.number_groups )
            self.assertAlmostEqual( 11, heating.values[0] )
            self.assertAlmostEqual( 22, heating.values[1] )
            self.assertAlmostEqual( 33, heating.values[2] )
            self.assertAlmostEqual( 44, heating.values[3] )
            self.assertAlmostEqual( 55, heating.values[4] )
            self.assertAlmostEqual( 66, heating.values[5] )
            self.assertAlmostEqual( 77, heating.values[6] )

            # verify content - outgoing particle types
            types = chunk.outgoing_particle_types
            self.assertEqual( 2, types.number_outgoing_particles )
            self.assertEqual(    0, types.values[0] )
            self.assertEqual( 1001, types.values[1] )

            # verify content - outgoing particle transport data
            transport = chunk.outgoing_particle_transport_data
            self.assertEqual( 2, transport.number_outgoing_particles )
            self.assertEqual( '92000', transport.values[0] )
            self.assertEqual( '92235.proton', transport.values[1] )

            # verify content - production matrix: 0
            matrix = chunk.outgoing_production_matrix( 0 )
            self.assertEqual( "pn_prod_full_0", matrix.keyword )
            self.assertEqual( 0, matrix.particle )
            self.assertEqual( False, matrix.empty )
            self.assertEqual( 44, matrix.size )
            self.assertEqual( 7, matrix.number_primary_groups )
            self.assertEqual( 3, matrix.number_outgoing_groups )
            self.assertEqual( 2, matrix.number_legendre_moments )
            moment = matrix.moment( 0 )
            self.assertEqual( 7, len( moment.matrix ) )
            self.assertEqual( 3, len( moment.matrix[0] ) )
            self.assertEqual( 0, moment.order )
            self.assertAlmostEqual( 1, moment.matrix[0][0] )
            self.assertAlmostEqual( 0, moment.matrix[0][1] )
            self.assertAlmostEqual( 0, moment.matrix[0][2] )
            self.assertAlmostEqual( 0, moment.matrix[1][0] )
            self.assertAlmostEqual( 1, moment.matrix[1][1] )
            self.assertAlmostEqual( 0, moment.matrix[1][2] )
            self.assertAlmostEqual( 0, moment.matrix[2][0] )
            self.assertAlmostEqual( 0, moment.matrix[2][1] )
            self.assertAlmostEqual( 1, moment.matrix[2][2] )
            self.assertAlmostEqual( 0, moment.matrix[3][0] )
            self.assertAlmostEqual( 1, moment.matrix[3][1] )
            self.assertAlmostEqual( 0, moment.matrix[3][2] )
            self.assertAlmostEqual( 1, moment.matrix[4][0] )
            self.assertAlmostEqual( 0, moment.matrix[4][1] )
            self.assertAlmostEqual( 0, moment.matrix[4][2] )
            self.assertAlmostEqual( 0, moment.matrix[5][0] )
            self.assertAlmostEqual( 1, moment.matrix[5][1] )
            self.assertAlmostEqual( 0, moment.matrix[5][2] )
            self.assertAlmostEqual( 0, moment.matrix[6][0] )
            self.assertAlmostEqual( 0, moment.matrix[6][1] )
            self.assertAlmostEqual( 1, moment.matrix[6][2] )
            moment = matrix.moment( 1 )
            self.assertEqual( 7, len( moment.matrix ) )
            self.assertEqual( 3, len( moment.matrix[0] ) )
            self.assertEqual( 1, moment.order )
            self.assertAlmostEqual( 0, moment.matrix[0][0] )
            self.assertAlmostEqual( 0, moment.matrix[0][1] )
            self.assertAlmostEqual( 1, moment.matrix[0][2] )
            self.assertAlmostEqual( 0, moment.matrix[1][0] )
            self.assertAlmostEqual( 1, moment.matrix[1][1] )
            self.assertAlmostEqual( 0, moment.matrix[1][2] )
            self.assertAlmostEqual( 1, moment.matrix[2][0] )
            self.assertAlmostEqual( 0, moment.matrix[2][1] )
            self.assertAlmostEqual( 0, moment.matrix[2][2] )
            self.assertAlmostEqual( 0, moment.matrix[3][0] )
            self.assertAlmostEqual( 1, moment.matrix[3][1] )
            self.assertAlmostEqual( 0, moment.matrix[3][2] )
            self.assertAlmostEqual( 0, moment.matrix[4][0] )
            self.assertAlmostEqual( 0, moment.matrix[4][1] )
            self.assertAlmostEqual( 1, moment.matrix[4][2] )
            self.assertAlmostEqual( 0, moment.matrix[5][0] )
            self.assertAlmostEqual( 1, moment.matrix[5][1] )
            self.assertAlmostEqual( 0, moment.matrix[5][2] )
            self.assertAlmostEqual( 1, moment.matrix[6][0] )
            self.assertAlmostEqual( 0, moment.matrix[6][1] )
            self.assertAlmostEqual( 0, moment.matrix[6][2] )

            # verify content - production matrix: 1001
            matrix = chunk.outgoing_production_matrix( 1001 )
            self.assertEqual( "pn_prod_full_1001", matrix.keyword )
            self.assertEqual( 1001, matrix.particle )
            self.assertEqual( False, matrix.empty )
            self.assertEqual( 30, matrix.size )
            self.assertEqual( 7, matrix.number_primary_groups )
            self.assertEqual( 2, matrix.number_outgoing_groups )
            self.assertEqual( 2, matrix.number_legendre_moments )
            moment = matrix.moment( 0 )
            self.assertEqual( 7, len( moment.matrix ) )
            self.assertEqual( 2, len( moment.matrix[0] ) )
            self.assertEqual( 0, moment.order )
            self.assertAlmostEqual( 1, moment.matrix[0][0] )
            self.assertAlmostEqual( 0, moment.matrix[0][1] )
            self.assertAlmostEqual( 0, moment.matrix[1][0] )
            self.assertAlmostEqual( 1, moment.matrix[1][1] )
            self.assertAlmostEqual( 1, moment.matrix[2][0] )
            self.assertAlmostEqual( 0, moment.matrix[2][1] )
            self.assertAlmostEqual( 0, moment.matrix[3][0] )
            self.assertAlmostEqual( 1, moment.matrix[3][1] )
            self.assertAlmostEqual( 1, moment.matrix[4][0] )
            self.assertAlmostEqual( 0, moment.matrix[4][1] )
            self.assertAlmostEqual( 0, moment.matrix[5][0] )
            self.assertAlmostEqual( 1, moment.matrix[5][1] )
            self.assertAlmostEqual( 1, moment.matrix[6][0] )
            self.assertAlmostEqual( 0, moment.matrix[6][1] )
            moment = matrix.moment( 1 )
            self.assertEqual( 7, len( moment.matrix ) )
            self.assertEqual( 2, len( moment.matrix[0] ) )
            self.assertEqual( 1, moment.order )
            self.assertAlmostEqual( 0, moment.matrix[0][0] )
            self.assertAlmostEqual( 1, moment.matrix[0][1] )
            self.assertAlmostEqual( 1, moment.matrix[1][0] )
            self.assertAlmostEqual( 0, moment.matrix[1][1] )
            self.assertAlmostEqual( 0, moment.matrix[2][0] )
            self.assertAlmostEqual( 1, moment.matrix[2][1] )
            self.assertAlmostEqual( 1, moment.matrix[3][0] )
            self.assertAlmostEqual( 0, moment.matrix[3][1] )
            self.assertAlmostEqual( 0, moment.matrix[4][0] )
            self.assertAlmostEqual( 1, moment.matrix[4][1] )
            self.assertAlmostEqual( 1, moment.matrix[5][0] )
            self.assertAlmostEqual( 0, moment.matrix[5][1] )
            self.assertAlmostEqual( 0, moment.matrix[6][0] )
            self.assertAlmostEqual( 1, moment.matrix[6][1] )

            # verify content - primary kerma
            kerma = chunk.primary_kerma
            self.assertEqual( 7, kerma.number_groups )
            self.assertAlmostEqual( 110, kerma.values[0] )
            self.assertAlmostEqual( 220, kerma.values[1] )
            self.assertAlmostEqual( 330, kerma.values[2] )
            self.assertAlmostEqual( 440, kerma.values[3] )
            self.assertAlmostEqual( 550, kerma.values[4] )
            self.assertAlmostEqual( 660, kerma.values[5] )
            self.assertAlmostEqual( 770, kerma.values[6] )

            # verify content - outgoing energy boundaries: 0
            structure = chunk.outgoing_group_boundaries( 0 )
            self.assertEqual( 3, structure.number_groups )
            self.assertAlmostEqual(    20, structure.values[0] )
            self.assertAlmostEqual(    10, structure.values[1] )
            self.assertAlmostEqual(     5, structure.values[2] )
            self.assertAlmostEqual( 1e-11, structure.values[3] )

            # verify content - outgoing energy boundaries: 1001
            structure = chunk.outgoing_group_boundaries( 1001 )
            self.assertEqual( 2, structure.number_groups )
            self.assertAlmostEqual(    20, structure.values[0] )
            self.assertAlmostEqual(    10, structure.values[1] )
            self.assertAlmostEqual( 1e-11, structure.values[2] )

            # verify content - outgoing heating numbers: 0
            heating = chunk.outgoing_heating_numbers( 0 )
            self.assertEqual( 7, heating.number_groups )
            self.assertAlmostEqual( 21  , heating.values[0] )
            self.assertAlmostEqual( 11  , heating.values[1] )
            self.assertAlmostEqual(  5.1, heating.values[2] )
            self.assertAlmostEqual(  3  , heating.values[3] )
            self.assertAlmostEqual(  4  , heating.values[4] )
            self.assertAlmostEqual(  6  , heating.values[5] )
            self.assertAlmostEqual(  7  , heating.values[6] )

            # verify content - outgoing heating numbers: 1001
            heating = chunk.outgoing_heating_numbers( 1001 )
            self.assertEqual( 7, heating.number_groups )
            self.assertAlmostEqual( 25  , heating.values[0] )
            self.assertAlmostEqual( 15  , heating.values[1] )
            self.assertAlmostEqual(  9.1, heating.values[2] )
            self.assertAlmostEqual(  7  , heating.values[3] )
            self.assertAlmostEqual(  8  , heating.values[4] )
            self.assertAlmostEqual( 10  , heating.values[5] )
            self.assertAlmostEqual( 11  , heating.values[6] )

            # verify content - outgoing kerma: 0
            kerma = chunk.outgoing_kerma( 0 )
            self.assertEqual( 7, kerma.number_groups )
            self.assertAlmostEqual( 210, kerma.values[0] )
            self.assertAlmostEqual( 110, kerma.values[1] )
            self.assertAlmostEqual(  51, kerma.values[2] )
            self.assertAlmostEqual(  30, kerma.values[3] )
            self.assertAlmostEqual(  40, kerma.values[4] )
            self.assertAlmostEqual(  60, kerma.values[5] )
            self.assertAlmostEqual(  70, kerma.values[6] )

            # verify content - outgoing kerma: 1001
            kerma = chunk.outgoing_kerma( 1001 )
            self.assertEqual( 7, kerma.number_groups )
            self.assertAlmostEqual( 250, kerma.values[0] )
            self.assertAlmostEqual( 150, kerma.values[1] )
            self.assertAlmostEqual(  91, kerma.values[2] )
            self.assertAlmostEqual(  70, kerma.values[3] )
            self.assertAlmostEqual(  80, kerma.values[4] )
            self.assertAlmostEqual( 100, kerma.values[5] )
            self.assertAlmostEqual( 110, kerma.values[6] )

        # the data is given explicitly
        chunk = MultigroupTable( zaid = '92235.711nm', libname = 'mendf71x',
                                 information = 'this is some information for the table', source = '12/22/2011',
                                 process = '08/07/2013', awr = 233.0248, weight = 235.043937521619,
                                 temperature = 2.53e-8, dilution = 1e+10,
                                 structure = EnergyGroupStructure( [ 20., 18.123456789, 16.0000000000001, 14., 10., 5, 1, 1e-11 ] ),
                                 velocities = Velocities( [ 2.1, 2.2, 2.25, 2.05, 2.15, 2.04, 2.06 ] ),
                                 flux = FluxWeights( [ 0.1, 0.2, 0.25, 0.05, 0.15, 0.04, 0.06 ] ),
                                 total_xs = TotalCrossSection( [ 1.1, 1.2, 1.25, 1.05, 1.15, 1.04, 1.06 ] ),
                                 reaction_xs = ReactionCrossSections(
                                                   xs = [ CrossSection( 2, 0., [ 10., 20., 30., 40., 50., 60., 70. ] ),
                                                          CrossSection( 16, 1.1234567, [ 1., 2., 3., 4., 5., 6., 7. ] ) ] ),
                                 scattering = ScatteringMatrix(
                                     [ LegendreMoment( 0, [ 1, 0, 0, 0, 0, 0, 0,
                                                            0, 1, 0, 0, 0, 0, 0,
                                                            0, 0, 1, 0, 0, 0, 0,
                                                            0, 0, 0, 1, 0, 0, 0,
                                                            0, 0, 0, 0, 1, 0, 0,
                                                            0, 0, 0, 0, 0, 1, 0,
                                                            0, 0, 0, 0, 0, 0, 1 ], 7 ),
                                       LegendreMoment( 1, [ 0, 0, 0, 0, 0, 0, 1,
                                                             0, 0, 0, 0, 0, 1, 0,
                                                             0, 0, 0, 0, 1, 0, 0,
                                                             0, 0, 0, 1, 0, 0, 0,
                                                             0, 0, 1, 0, 0, 0, 0,
                                                             0, 1, 0, 0, 0, 0, 0,
                                                             1, 0, 0, 0, 0, 0, 0 ], 7 ) ] ),
                                 fission_q = AverageFissionEnergyRelease( 202.827, 181.238898, 4.827645,
                                                                          7.281253, 6.5, 169.13 ),
                                 primary_heating = HeatingNumbers( [ 11., 22., 33., 44., 55., 66., 77. ] ),
                                 primary_kerma = Kerma( [ 110., 220., 330., 440., 550., 660., 770. ] ),
                                 types = OutgoingParticleTypes( [ 0, 1001 ] ),
                                 transport = OutgoingParticleTransportData( [ "92000", "92235.proton" ] ),
                                 production = [

                                     ScatteringMatrix( 0,
                                         [ LegendreMoment( 0, [ 1, 0, 0,
                                                                0, 1, 0,
                                                                0, 0, 1,
                                                                0, 1, 0,
                                                                1, 0, 0,
                                                                0, 1, 0,
                                                                0, 0, 1 ], 7, 3 ),
                                           LegendreMoment( 1, [ 0, 0, 1,
                                                                0, 1, 0,
                                                                1, 0, 0,
                                                                0, 1, 0,
                                                                0, 0, 1,
                                                                0, 1, 0,
                                                                1, 0, 0 ], 7, 3 ) ] ),
                                     ScatteringMatrix( 1001,
                                         [ LegendreMoment( 0, [ 1, 0,
                                                                0, 1,
                                                                1, 0,
                                                                0, 1,
                                                                1, 0,
                                                                0, 1,
                                                                1, 0 ], 7, 2 ),
                                           LegendreMoment( 1, [ 0, 1,
                                                                1, 0,
                                                                0, 1,
                                                                1, 0,
                                                                0, 1,
                                                                1, 0,
                                                                0, 1 ], 7, 2 ) ] )                                 ],
                                 outgoing = [ EnergyGroupStructure( 0, [ 20., 10., 5, 1e-11 ] ),
                                              EnergyGroupStructure( 1001, [ 20., 10., 1e-11 ] ) ],
                                 outgoing_heating = [ HeatingNumbers( 0, [ 21., 11., 5.1, 3., 4., 6., 7. ] ),
                                                      HeatingNumbers( 1001, [ 25., 15., 9.1, 7., 8., 10., 11. ] ) ],
                                 outgoing_kerma = [ Kerma( 0, [ 210., 110., 51., 30., 40., 60., 70. ] ),
                                                    Kerma( 1001, [ 250., 150., 91., 70., 80., 100., 110. ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a file
        chunk.to_file( 'test.txt' )
        chunk = MultigroupTable.from_file( 'test.txt' )
        verify_chunk( self, chunk )
        os.remove( 'test.txt' )

if __name__ == '__main__' :

    unittest.main()
