# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import ScatteringMatrix
from NDItk.multigroup import LegendreMoment

class Test_NDItk_multigroup_ScatteringMatrix( unittest.TestCase ) :
    """Unit test for the ScatteringMatrix class."""

    chunk_values = [ 0,
                     1, 2, 3, 4, 5, 6, 7, 8, 9,
                     1,
                     11, 12, 13, 14, 15, 16, 17, 18, 19 ]
    chunk_string = ( 'pn_full\n'
                     '    0\n'
                     '    1 2 3 4 5\n'
                     '    6 7 8 9\n'
                     '    1\n'
                     '    11 12 13 14 15\n'
                     '    16 17 18 19\n' )
    chunk_outgoing_values = [ 0,
                     1, 2, 3, 4, 5, 6,
                     1,
                     11, 12, 13, 14, 15, 16 ]
    chunk_outgoing_string = ( 'pn_prod_full_1001\n'
                              '    0\n'
                              '    1 2 3 4 5\n'
                              '    6\n'
                              '    1\n'
                              '    11 12 13 14 15\n'
                              '    16\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( None, chunk.particle )
            self.assertEqual( 3, chunk.number_primary_groups )
            self.assertEqual( 3, chunk.number_outgoing_groups )
            self.assertEqual( 2, chunk.number_legendre_moments )

            self.assertEqual( True, chunk.has_moment( 0 ) )
            self.assertEqual( True, chunk.has_moment( 1 ) )
            self.assertEqual( False, chunk.has_moment( 102 ) )

            self.assertEqual( 0, chunk.moments[0].order )
            self.assertAlmostEqual( 1, chunk.moments[0].matrix[0][0] )
            self.assertAlmostEqual( 2, chunk.moments[0].matrix[0][1] )
            self.assertAlmostEqual( 3, chunk.moments[0].matrix[0][2] )
            self.assertAlmostEqual( 4, chunk.moments[0].matrix[1][0] )
            self.assertAlmostEqual( 5, chunk.moments[0].matrix[1][1] )
            self.assertAlmostEqual( 6, chunk.moments[0].matrix[1][2] )
            self.assertAlmostEqual( 7, chunk.moments[0].matrix[2][0] )
            self.assertAlmostEqual( 8, chunk.moments[0].matrix[2][1] )
            self.assertAlmostEqual( 9, chunk.moments[0].matrix[2][2] )

            self.assertEqual( 1, chunk.moments[1].order )
            self.assertAlmostEqual( 11, chunk.moments[1].matrix[0][0] )
            self.assertAlmostEqual( 12, chunk.moments[1].matrix[0][1] )
            self.assertAlmostEqual( 13, chunk.moments[1].matrix[0][2] )
            self.assertAlmostEqual( 14, chunk.moments[1].matrix[1][0] )
            self.assertAlmostEqual( 15, chunk.moments[1].matrix[1][1] )
            self.assertAlmostEqual( 16, chunk.moments[1].matrix[1][2] )
            self.assertAlmostEqual( 17, chunk.moments[1].matrix[2][0] )
            self.assertAlmostEqual( 18, chunk.moments[1].matrix[2][1] )
            self.assertAlmostEqual( 19, chunk.moments[1].matrix[2][2] )

            moment = chunk.moment( 0 )
            self.assertEqual( 0, moment.order )
            self.assertAlmostEqual( 1, moment.matrix[0][0] )
            self.assertAlmostEqual( 2, moment.matrix[0][1] )
            self.assertAlmostEqual( 3, moment.matrix[0][2] )
            self.assertAlmostEqual( 4, moment.matrix[1][0] )
            self.assertAlmostEqual( 5, moment.matrix[1][1] )
            self.assertAlmostEqual( 6, moment.matrix[1][2] )
            self.assertAlmostEqual( 7, moment.matrix[2][0] )
            self.assertAlmostEqual( 8, moment.matrix[2][1] )
            self.assertAlmostEqual( 9, moment.matrix[2][2] )

            moment = chunk.moment( 1 )
            self.assertEqual( 1, moment.order )
            self.assertAlmostEqual( 11, moment.matrix[0][0] )
            self.assertAlmostEqual( 12, moment.matrix[0][1] )
            self.assertAlmostEqual( 13, moment.matrix[0][2] )
            self.assertAlmostEqual( 14, moment.matrix[1][0] )
            self.assertAlmostEqual( 15, moment.matrix[1][1] )
            self.assertAlmostEqual( 16, moment.matrix[1][2] )
            self.assertAlmostEqual( 17, moment.matrix[2][0] )
            self.assertAlmostEqual( 18, moment.matrix[2][1] )
            self.assertAlmostEqual( 19, moment.matrix[2][2] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'pn_full', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 20, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        def verify_outgoing_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1001, chunk.particle )
            self.assertEqual( 3, chunk.number_primary_groups )
            self.assertEqual( 2, chunk.number_outgoing_groups )
            self.assertEqual( 2, chunk.number_legendre_moments )

            self.assertEqual( True, chunk.has_moment( 0 ) )
            self.assertEqual( True, chunk.has_moment( 1 ) )
            self.assertEqual( False, chunk.has_moment( 102 ) )

            self.assertEqual( 0, chunk.moments[0].order )
            self.assertAlmostEqual( 1, chunk.moments[0].matrix[0][0] )
            self.assertAlmostEqual( 2, chunk.moments[0].matrix[0][1] )
            self.assertAlmostEqual( 3, chunk.moments[0].matrix[1][0] )
            self.assertAlmostEqual( 4, chunk.moments[0].matrix[1][1] )
            self.assertAlmostEqual( 5, chunk.moments[0].matrix[2][0] )
            self.assertAlmostEqual( 6, chunk.moments[0].matrix[2][1] )

            self.assertEqual( 1, chunk.moments[1].order )
            self.assertAlmostEqual( 11, chunk.moments[1].matrix[0][0] )
            self.assertAlmostEqual( 12, chunk.moments[1].matrix[0][1] )
            self.assertAlmostEqual( 13, chunk.moments[1].matrix[1][0] )
            self.assertAlmostEqual( 14, chunk.moments[1].matrix[1][1] )
            self.assertAlmostEqual( 15, chunk.moments[1].matrix[2][0] )
            self.assertAlmostEqual( 16, chunk.moments[1].matrix[2][1] )

            moment = chunk.moment( 0 )
            self.assertEqual( 0, moment.order )
            self.assertAlmostEqual( 1, moment.matrix[0][0] )
            self.assertAlmostEqual( 2, moment.matrix[0][1] )
            self.assertAlmostEqual( 3, moment.matrix[1][0] )
            self.assertAlmostEqual( 4, moment.matrix[1][1] )
            self.assertAlmostEqual( 5, moment.matrix[2][0] )
            self.assertAlmostEqual( 6, moment.matrix[2][1] )

            moment = chunk.moment( 1 )
            self.assertEqual( 1, moment.order )
            self.assertAlmostEqual( 11, moment.matrix[0][0] )
            self.assertAlmostEqual( 12, moment.matrix[0][1] )
            self.assertAlmostEqual( 13, moment.matrix[1][0] )
            self.assertAlmostEqual( 14, moment.matrix[1][1] )
            self.assertAlmostEqual( 15, moment.matrix[2][0] )
            self.assertAlmostEqual( 16, moment.matrix[2][1] )

            self.assertEqual( self.chunk_outgoing_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'pn_prod_full_1001', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 14, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_outgoing_values[index], values[index] )

        # the data is given explicitly for a production matrix
        chunk = ScatteringMatrix(
                  moments = [ LegendreMoment( 0, [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ], 3 ),
                              LegendreMoment( 1, [ 11, 12, 13, 14, 15, 16, 17, 18, 19 ], 3 ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ScatteringMatrix.from_string( self.chunk_string, 3, 2 )

        verify_chunk( self, chunk )

        # the data is given explicitly for a production matrix
        chunk = ScatteringMatrix(
                  particle = 1001,
                  moments = [ LegendreMoment( 0, [ 1, 2, 3, 4, 5, 6 ], 3, 2 ),
                              LegendreMoment( 1, [ 11, 12, 13, 14, 15, 16 ], 3, 2 ) ] )

        verify_outgoing_chunk( self, chunk )

        # the data is read from a string
        chunk = ScatteringMatrix.from_string( self.chunk_outgoing_string, 3, 2, 2 )

        verify_outgoing_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
