# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import Kerma

class Test_NDItk_multigroup_Kerma( unittest.TestCase ) :
    """Unit test for the Kerma class."""

    chunk_values = [ 10, 9, 8, 7, 6, 5, 4 ]
    chunk_string = ( 'kerma\n'
                     '    10 9 8 7 6\n'
                     '    5 4\n' )

    chunk_outgoing_values = [ 10, 9, 8, 7, 6, 5, 4 ]
    chunk_outgoing_string = ( 'kerma_1001\n'
                              '    10 9 8 7 6\n'
                              '    5 4\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( None, chunk.particle )
            self.assertEqual( 7, chunk.number_groups )
            self.assertAlmostEqual( 10, chunk.values[0] )
            self.assertAlmostEqual(  9, chunk.values[1] )
            self.assertAlmostEqual(  8, chunk.values[2] )
            self.assertAlmostEqual(  7, chunk.values[3] )
            self.assertAlmostEqual(  6, chunk.values[4] )
            self.assertAlmostEqual(  5, chunk.values[5] )
            self.assertAlmostEqual(  4, chunk.values[6] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'kerma', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 7, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        def verify_outgoing_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1001, chunk.particle )
            self.assertEqual( 7, chunk.number_groups )
            self.assertAlmostEqual( 10, chunk.values[0] )
            self.assertAlmostEqual(  9, chunk.values[1] )
            self.assertAlmostEqual(  8, chunk.values[2] )
            self.assertAlmostEqual(  7, chunk.values[3] )
            self.assertAlmostEqual(  6, chunk.values[4] )
            self.assertAlmostEqual(  5, chunk.values[5] )
            self.assertAlmostEqual(  4, chunk.values[6] )

            self.assertEqual( self.chunk_outgoing_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'kerma_1001', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 7, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_outgoing_values[index], values[index] )

        # the data is given explicitly
        chunk = Kerma( values = [ 10, 9, 8, 7, 6, 5, 4 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Kerma.from_string( self.chunk_string, 7 )

        verify_chunk( self, chunk )

        # the data is given explicitly for an outgoing particle
        chunk = Kerma( particle = 1001, values = [ 10, 9, 8, 7, 6, 5, 4 ] )

        verify_outgoing_chunk( self, chunk )

        # the data is read from a string for an outgoing particle
        chunk = Kerma.from_string( self.chunk_outgoing_string, 7 )

        verify_outgoing_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
