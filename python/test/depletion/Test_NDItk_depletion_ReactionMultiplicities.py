# standard imports
import unittest

# third party imports

# local imports
from NDItk.depletion import ReactionMultiplicities
from NDItk.depletion import Multiplicities
from NDItk.depletion import ReactionMultiplicityType

class Test_NDItk_depletion_ReactionMultiplicities( unittest.TestCase ) :
    """Unit test for the ReactionMultiplicities class."""

    chunk_values = [ 2, 2, 1, 1, 92235, 1, 16, 2, 1, 2, 92234, 1 ]
    chunk_string = ( 'rprod\n'
                     '    2\n'
                     '    2\n'
                     '    1 1\n'
                     '    92235 1\n'
                     '    16\n'
                     '    2\n'
                     '    1 2\n'
                     '    92234 1\n' )

    chunk_typed_string = ( 'rprod_all\n'
                           '    2\n'
                           '    2\n'
                           '    1 1\n'
                           '    92235 1\n'
                           '    16\n'
                           '    2\n'
                           '    1 2\n'
                           '    92234 1\n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.number_reactions )

            self.assertEqual( True, chunk.has_reaction( 2 ) )
            self.assertEqual( True, chunk.has_reaction( 16 ) )
            self.assertEqual( False, chunk.has_reaction( 102 ) )

            self.assertEqual( 2, chunk.reactions[0].identifier )
            self.assertEqual( 2, chunk.reactions[0].number_reaction_products )
            self.assertEqual( 2, len( chunk.reactions[0].reaction_products ) )
            self.assertEqual( 2, len( chunk.reactions[0].multiplicities ) )
            self.assertEqual(     1, chunk.reactions[0].reaction_products[0] )
            self.assertEqual( 92235, chunk.reactions[0].reaction_products[1] )
            self.assertEqual(     1, chunk.reactions[0].multiplicities[0] )
            self.assertEqual(     1, chunk.reactions[0].multiplicities[1] )

            self.assertEqual( 16, chunk.reactions[1].identifier )
            self.assertEqual( 2, chunk.reactions[1].number_reaction_products )
            self.assertEqual( 2, len( chunk.reactions[1].reaction_products ) )
            self.assertEqual( 2, len( chunk.reactions[1].multiplicities ) )
            self.assertEqual(     1, chunk.reactions[1].reaction_products[0] )
            self.assertEqual( 92234, chunk.reactions[1].reaction_products[1] )
            self.assertEqual(     2, chunk.reactions[1].multiplicities[0] )
            self.assertEqual(     1, chunk.reactions[1].multiplicities[1] )

            multiplicities = chunk.reaction( 2 )
            self.assertEqual( 2, multiplicities.identifier )
            self.assertEqual( 2, multiplicities.number_reaction_products )
            self.assertEqual( 2, len( multiplicities.reaction_products ) )
            self.assertEqual( 2, len( multiplicities.multiplicities ) )
            self.assertEqual(     1, multiplicities.reaction_products[0] )
            self.assertEqual( 92235, multiplicities.reaction_products[1] )
            self.assertEqual(     1, multiplicities.multiplicities[0] )
            self.assertEqual(     1, multiplicities.multiplicities[1] )

            multiplicities = chunk.reaction( 16 )
            self.assertEqual( 2, multiplicities.number_reaction_products )
            self.assertEqual( 2, len( multiplicities.reaction_products ) )
            self.assertEqual( 2, len( multiplicities.multiplicities ) )
            self.assertEqual(     1, multiplicities.reaction_products[0] )
            self.assertEqual( 92234, multiplicities.reaction_products[1] )
            self.assertEqual(     2, multiplicities.multiplicities[0] )
            self.assertEqual(     1, multiplicities.multiplicities[1] )

            self.assertEqual( self.chunk_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'rprod', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 12, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        def verify_chunk_typed( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.number_reactions )

            self.assertEqual( True, chunk.has_reaction( 2 ) )
            self.assertEqual( True, chunk.has_reaction( 16 ) )
            self.assertEqual( False, chunk.has_reaction( 102 ) )

            self.assertEqual( 2, chunk.reactions[0].identifier )
            self.assertEqual( 2, chunk.reactions[0].number_reaction_products )
            self.assertEqual( 2, len( chunk.reactions[0].reaction_products ) )
            self.assertEqual( 2, len( chunk.reactions[0].multiplicities ) )
            self.assertEqual(     1, chunk.reactions[0].reaction_products[0] )
            self.assertEqual( 92235, chunk.reactions[0].reaction_products[1] )
            self.assertEqual(     1, chunk.reactions[0].multiplicities[0] )
            self.assertEqual(     1, chunk.reactions[0].multiplicities[1] )

            self.assertEqual( 16, chunk.reactions[1].identifier )
            self.assertEqual( 2, chunk.reactions[1].number_reaction_products )
            self.assertEqual( 2, len( chunk.reactions[1].reaction_products ) )
            self.assertEqual( 2, len( chunk.reactions[1].multiplicities ) )
            self.assertEqual(     1, chunk.reactions[1].reaction_products[0] )
            self.assertEqual( 92234, chunk.reactions[1].reaction_products[1] )
            self.assertEqual(     2, chunk.reactions[1].multiplicities[0] )
            self.assertEqual(     1, chunk.reactions[1].multiplicities[1] )

            multiplicities = chunk.reaction( 2 )
            self.assertEqual( 2, multiplicities.identifier )
            self.assertEqual( 2, multiplicities.number_reaction_products )
            self.assertEqual( 2, len( multiplicities.reaction_products ) )
            self.assertEqual( 2, len( multiplicities.multiplicities ) )
            self.assertEqual(     1, multiplicities.reaction_products[0] )
            self.assertEqual( 92235, multiplicities.reaction_products[1] )
            self.assertEqual(     1, multiplicities.multiplicities[0] )
            self.assertEqual(     1, multiplicities.multiplicities[1] )

            multiplicities = chunk.reaction( 16 )
            self.assertEqual( 2, multiplicities.number_reaction_products )
            self.assertEqual( 2, len( multiplicities.reaction_products ) )
            self.assertEqual( 2, len( multiplicities.multiplicities ) )
            self.assertEqual(     1, multiplicities.reaction_products[0] )
            self.assertEqual( 92234, multiplicities.reaction_products[1] )
            self.assertEqual(     2, multiplicities.multiplicities[0] )
            self.assertEqual(     1, multiplicities.multiplicities[1] )

            self.assertEqual( self.chunk_typed_string, chunk.to_string() )

            # verify the record
            self.assertEqual( 'rprod_all', chunk.keyword )
            self.assertEqual( False, chunk.empty )
            self.assertEqual( 12, chunk.size )

            values = chunk.values
            for index in range( chunk.size ) :

                self.assertAlmostEqual( self.chunk_values[index], values[index] )

        # the data is given explicitly
        chunk = ReactionMultiplicities(
                  multiplicities = [ Multiplicities( 2, [ 1, 92235 ], [ 1, 1 ] ),
                                     Multiplicities( 16, [ 1, 92234 ], [ 2, 1 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ReactionMultiplicities.from_string( self.chunk_string, 2 )

        verify_chunk( self, chunk )

        # the data is given explicitly with a multiplicty type
        chunk = ReactionMultiplicities(
                  type = ReactionMultiplicityType.All,
                  multiplicities = [ Multiplicities( 2, [ 1, 92235 ], [ 1, 1 ] ),
                                     Multiplicities( 16, [ 1, 92234 ], [ 2, 1 ] ) ] )

        verify_chunk_typed( self, chunk )

        # the data is read from a string
        chunk = ReactionMultiplicities.from_string( self.chunk_typed_string, 2 )

        verify_chunk_typed( self, chunk )

if __name__ == '__main__' :

    unittest.main()
