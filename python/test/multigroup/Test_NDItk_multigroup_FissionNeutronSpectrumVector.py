# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import FissionNeutronSpectrumVector
from NDItk.multigroup import FissionType

class Test_NDItk_multigroup_FissionNeutronSpectrumVector( unittest.TestCase ) :
    """Unit test for the FissionNeutronSpectrumVector class."""

    chunk_values = [ 1, 2, 3, 4, 5, 6, 7 ]
    chunk_string = (  'chi_vec_pr\n'
                      '    1 2 3 4 5\n'
                      '    6 7\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( FissionType.Prompt, chunk.type )
            self.assertEqual( 7, chunk.number_groups )
            self.assertAlmostEqual( 1, chunk.values[0] )
            self.assertAlmostEqual( 2, chunk.values[1] )
            self.assertAlmostEqual( 3, chunk.values[2] )
            self.assertAlmostEqual( 4, chunk.values[3] )
            self.assertAlmostEqual( 5, chunk.values[4] )
            self.assertAlmostEqual( 6, chunk.values[5] )
            self.assertAlmostEqual( 7, chunk.values[6] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'chi_vec_pr', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 7, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = FissionNeutronSpectrumVector( type = FissionType.Prompt,
                                              values = [ 1, 2, 3, 4, 5, 6, 7 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = FissionNeutronSpectrumVector.from_string( self.chunk_string, 7 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
