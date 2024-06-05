# standard imports
import unittest

# third party imports

# local imports
from NDItk.multigroup import FissionNeutronSpectrumMatrix
from NDItk.multigroup import FissionType

class Test_NDItk_multigroup_FissionNeutronSpectrumMatrix( unittest.TestCase ) :
    """Unit test for the FissionNeutronSpectrumMatrix class."""

    chunk_values = [   1,   2,   3,   4,   5,   6,   7,
                     1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1,
                     1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2,
                     1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3,
                     1.4, 2.4, 3.4, 4.4, 5.4, 6.4, 7.4,
                     1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5,
                     1.6, 2.6, 3.6, 4.6, 5.6, 6.6, 7.6 ]
    chunk_string = ( 'chi_mat_pr\n'
                     '    1 2 3 4 5\n'
                     '    6 7 1.1 2.1 3.1\n'
                     '    4.1 5.1 6.1 7.1 1.2\n'
                     '    2.2 3.2 4.2 5.2 6.2\n'
                     '    7.2 1.3 2.3 3.3 4.3\n'
                     '    5.3 6.3 7.3 1.4 2.4\n'
                     '    3.4 4.4 5.4 6.4 7.4\n'
                     '    1.5 2.5 3.5 4.5 5.5\n'
                     '    6.5 7.5 1.6 2.6 3.6\n'
                     '    4.6 5.6 6.6 7.6\n' )

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
            self.assertAlmostEqual( 1.1, chunk.values[7] )
            self.assertAlmostEqual( 2.1, chunk.values[8] )
            self.assertAlmostEqual( 3.1, chunk.values[9] )
            self.assertAlmostEqual( 4.1, chunk.values[10] )
            self.assertAlmostEqual( 5.1, chunk.values[11] )
            self.assertAlmostEqual( 6.1, chunk.values[12] )
            self.assertAlmostEqual( 7.1, chunk.values[13] )
            self.assertAlmostEqual( 1.2, chunk.values[14] )
            self.assertAlmostEqual( 2.2, chunk.values[15] )
            self.assertAlmostEqual( 3.2, chunk.values[16] )
            self.assertAlmostEqual( 4.2, chunk.values[17] )
            self.assertAlmostEqual( 5.2, chunk.values[18] )
            self.assertAlmostEqual( 6.2, chunk.values[19] )
            self.assertAlmostEqual( 7.2, chunk.values[20] )
            self.assertAlmostEqual( 1.3, chunk.values[21] )
            self.assertAlmostEqual( 2.3, chunk.values[22] )
            self.assertAlmostEqual( 3.3, chunk.values[23] )
            self.assertAlmostEqual( 4.3, chunk.values[24] )
            self.assertAlmostEqual( 5.3, chunk.values[25] )
            self.assertAlmostEqual( 6.3, chunk.values[26] )
            self.assertAlmostEqual( 7.3, chunk.values[27] )
            self.assertAlmostEqual( 1.4, chunk.values[28] )
            self.assertAlmostEqual( 2.4, chunk.values[29] )
            self.assertAlmostEqual( 3.4, chunk.values[30] )
            self.assertAlmostEqual( 4.4, chunk.values[31] )
            self.assertAlmostEqual( 5.4, chunk.values[32] )
            self.assertAlmostEqual( 6.4, chunk.values[33] )
            self.assertAlmostEqual( 7.4, chunk.values[34] )
            self.assertAlmostEqual( 1.5, chunk.values[35] )
            self.assertAlmostEqual( 2.5, chunk.values[36] )
            self.assertAlmostEqual( 3.5, chunk.values[37] )
            self.assertAlmostEqual( 4.5, chunk.values[38] )
            self.assertAlmostEqual( 5.5, chunk.values[39] )
            self.assertAlmostEqual( 6.5, chunk.values[40] )
            self.assertAlmostEqual( 7.5, chunk.values[41] )
            self.assertAlmostEqual( 1.6, chunk.values[42] )
            self.assertAlmostEqual( 2.6, chunk.values[43] )
            self.assertAlmostEqual( 3.6, chunk.values[44] )
            self.assertAlmostEqual( 4.6, chunk.values[45] )
            self.assertAlmostEqual( 5.6, chunk.values[46] )
            self.assertAlmostEqual( 6.6, chunk.values[47] )
            self.assertAlmostEqual( 7.6, chunk.values[48] )

            self.assertAlmostEqual(   1, chunk.matrix[0][0] )
            self.assertAlmostEqual(   2, chunk.matrix[0][1] )
            self.assertAlmostEqual(   3, chunk.matrix[0][2] )
            self.assertAlmostEqual(   4, chunk.matrix[0][3] )
            self.assertAlmostEqual(   5, chunk.matrix[0][4] )
            self.assertAlmostEqual(   6, chunk.matrix[0][5] )
            self.assertAlmostEqual(   7, chunk.matrix[0][6] )
            self.assertAlmostEqual( 1.1, chunk.matrix[1][0] )
            self.assertAlmostEqual( 2.1, chunk.matrix[1][1] )
            self.assertAlmostEqual( 3.1, chunk.matrix[1][2] )
            self.assertAlmostEqual( 4.1, chunk.matrix[1][3] )
            self.assertAlmostEqual( 5.1, chunk.matrix[1][4] )
            self.assertAlmostEqual( 6.1, chunk.matrix[1][5] )
            self.assertAlmostEqual( 7.1, chunk.matrix[1][6] )
            self.assertAlmostEqual( 1.2, chunk.matrix[2][0] )
            self.assertAlmostEqual( 2.2, chunk.matrix[2][1] )
            self.assertAlmostEqual( 3.2, chunk.matrix[2][2] )
            self.assertAlmostEqual( 4.2, chunk.matrix[2][3] )
            self.assertAlmostEqual( 5.2, chunk.matrix[2][4] )
            self.assertAlmostEqual( 6.2, chunk.matrix[2][5] )
            self.assertAlmostEqual( 7.2, chunk.matrix[2][6] )
            self.assertAlmostEqual( 1.3, chunk.matrix[3][0] )
            self.assertAlmostEqual( 2.3, chunk.matrix[3][1] )
            self.assertAlmostEqual( 3.3, chunk.matrix[3][2] )
            self.assertAlmostEqual( 4.3, chunk.matrix[3][3] )
            self.assertAlmostEqual( 5.3, chunk.matrix[3][4] )
            self.assertAlmostEqual( 6.3, chunk.matrix[3][5] )
            self.assertAlmostEqual( 7.3, chunk.matrix[3][6] )
            self.assertAlmostEqual( 1.4, chunk.matrix[4][0] )
            self.assertAlmostEqual( 2.4, chunk.matrix[4][1] )
            self.assertAlmostEqual( 3.4, chunk.matrix[4][2] )
            self.assertAlmostEqual( 4.4, chunk.matrix[4][3] )
            self.assertAlmostEqual( 5.4, chunk.matrix[4][4] )
            self.assertAlmostEqual( 6.4, chunk.matrix[4][5] )
            self.assertAlmostEqual( 7.4, chunk.matrix[4][6] )
            self.assertAlmostEqual( 1.5, chunk.matrix[5][0] )
            self.assertAlmostEqual( 2.5, chunk.matrix[5][1] )
            self.assertAlmostEqual( 3.5, chunk.matrix[5][2] )
            self.assertAlmostEqual( 4.5, chunk.matrix[5][3] )
            self.assertAlmostEqual( 5.5, chunk.matrix[5][4] )
            self.assertAlmostEqual( 6.5, chunk.matrix[5][5] )
            self.assertAlmostEqual( 7.5, chunk.matrix[5][6] )
            self.assertAlmostEqual( 1.6, chunk.matrix[6][0] )
            self.assertAlmostEqual( 2.6, chunk.matrix[6][1] )
            self.assertAlmostEqual( 3.6, chunk.matrix[6][2] )
            self.assertAlmostEqual( 4.6, chunk.matrix[6][3] )
            self.assertAlmostEqual( 5.6, chunk.matrix[6][4] )
            self.assertAlmostEqual( 6.6, chunk.matrix[6][5] )
            self.assertAlmostEqual( 7.6, chunk.matrix[6][6] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'chi_mat_pr', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 49, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = FissionNeutronSpectrumMatrix( type = FissionType.Prompt,
                                              values = [   1,   2,   3,   4,   5,   6,   7,
                                                         1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1,
                                                         1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2,
                                                         1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3,
                                                         1.4, 2.4, 3.4, 4.4, 5.4, 6.4, 7.4,
                                                         1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5,
                                                         1.6, 2.6, 3.6, 4.6, 5.6, 6.6, 7.6 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = FissionNeutronSpectrumMatrix.from_string( self.chunk_string, 7 )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
