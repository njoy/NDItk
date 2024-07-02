# standard imports
import unittest

# third party imports

# local imports
from NDItk.depletion import Multiplicities

class Test_NDItk_depletion_Multiplicities( unittest.TestCase ) :
    """Unit test for the Multiplicities class."""

    chunk_values = [ 16, 2, 1, 2, 92234, 1 ]
    chunk_string = ( '    16\n'
                     '    2\n'
                     '    1 2\n'
                     '    92234 1\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.number_reaction_products )
            self.assertEqual( 2, len( chunk.reaction_products ) )
            self.assertEqual( 2, len( chunk.multiplicities ) )
            self.assertEqual( 16, chunk.identifier )
            self.assertEqual(     1, chunk.reaction_products[0] )
            self.assertEqual( 92234, chunk.reaction_products[1] )
            self.assertEqual(     2, chunk.multiplicities[0] )
            self.assertEqual(     1, chunk.multiplicities[1] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 6, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = Multiplicities( reaction = 16, products = [ 1, 92234 ],
                                multiplicities = [ 2, 1 ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
