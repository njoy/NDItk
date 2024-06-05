# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import FissionNeutronProduction
from NDItk.multigroup import FissionType

class Test_NDItk_multigroup_FissionNeutronProduction( unittest.TestCase ) :
    """Unit test for the FissionNeutronProduction class."""

    chunk_values = [ 2, 2.1, 2.2, 2.3, 2.4, 5, 7 ]
    chunk_string = (  'nu_sig_f_pr\n'
                      '    2 2.1 2.2 2.3 2.4\n'
                      '    5 7\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( FissionType.Prompt, chunk.type )
            self.assertEqual( 7, chunk.number_groups )
            self.assertAlmostEqual(   2, chunk.values[0] )
            self.assertAlmostEqual( 2.1, chunk.values[1] )
            self.assertAlmostEqual( 2.2, chunk.values[2] )
            self.assertAlmostEqual( 2.3, chunk.values[3] )
            self.assertAlmostEqual( 2.4, chunk.values[4] )
            self.assertAlmostEqual(   5, chunk.values[5] )
            self.assertAlmostEqual(   7, chunk.values[6] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'nu_sig_f_pr', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 7, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = FissionNeutronProduction( type = FissionType.Prompt,
                                          values = [ 2, 2.1, 2.2, 2.3, 2.4, 5, 7 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = FissionNeutronProduction.from_string( self.chunk_string, 7 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
