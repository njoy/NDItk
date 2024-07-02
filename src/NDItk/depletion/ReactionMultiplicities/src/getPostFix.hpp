static std::string getPostFix( const ReactionMultiplicityType& type ) {

  return type == ReactionMultiplicityType::All
             ? std::string( "all" )
             : type == ReactionMultiplicityType::Few
                   ? std::string( "few" )
                   : std::string( "rmo" );
}
