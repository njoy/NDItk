/**
 *  @brief Utility function to extract the particle id from a keyword
 *
 *  Some NDI records use keywords that include a particle id at the end of
 *  the keyword. These are basically of the form xxxxxxxx_yyyyy where yyyyy
 *  are digits that represent the particle id (e.g. 0 for gammas and 1001 for
 *  protons).
 *
 *  @param[in] keyword   the keyword
 */
static std::tuple< std::string,
                   std::optional< std::string >,
                   std::optional< int >,
                   std::optional< depletion::ReactionMultiplicityType >,
                   std::optional< multigroup::FissionType > >
splitKeyword( std::string keyword ) {

  // special cases: sig_0
  if ( "sig_0" == keyword ) {

    return { std::move( keyword ), std::nullopt, std::nullopt, std::nullopt, std::nullopt };
  }
  else {

    // A regex that we will use to detect keywords with trailing particle types.
    // A key is basically xxx_yyy with an optional particle type at the end (the
    // full keyword would be xxx_yyy_0 for the xxx_yyy subtype keyword for gammas).
    // "([a-z]+(?:_[a-z]+)*)" captures the subtype part of the key, i.e. 'xxx_yyy'
    // and "([0-9]+)" captures an optional particle type that must end the string.
    const std::regex key{ "^([a-z]+(?:_[a-z]+)*)(?:_([0-9]+))?$" };

    std::smatch match;
    if ( std::regex_match( keyword, match, key ) ) {

      if ( match[1] == keyword ) {

        const std::array< std::string, 6 > suffixes = { "_all", "_few", "_rmo", "_pr", "_del", "_tot" };
        for ( unsigned int i = 0; i < suffixes.size(); ++i ) {

          if ( keyword.size() >= suffixes[i].size() &&
               keyword.compare( keyword.size() - suffixes[i].size(), suffixes[i].size(), suffixes[i] ) == 0 ) {

            std::string subtype = keyword.substr( 0, keyword.size() - suffixes[i].size() );
            switch ( i ) {

              case 0 : return { std::move( keyword ), std::move( subtype ), std::nullopt, depletion::ReactionMultiplicityType::All, std::nullopt };
              case 1 : return { std::move( keyword ), std::move( subtype ), std::nullopt, depletion::ReactionMultiplicityType::Few, std::nullopt };
              case 2 : return { std::move( keyword ), std::move( subtype ), std::nullopt, depletion::ReactionMultiplicityType::RMO, std::nullopt };
              case 3 : return { std::move( keyword ), std::move( subtype ), std::nullopt, std::nullopt, multigroup::FissionType::Prompt };
              case 4 : return { std::move( keyword ), std::move( subtype ), std::nullopt, std::nullopt, multigroup::FissionType::Delayed };
              case 5 : return { std::move( keyword ), std::move( subtype ), std::nullopt, std::nullopt, multigroup::FissionType::Total };
            }
          }
        }

        return { std::move( keyword ), std::nullopt, std::nullopt, std::nullopt, std::nullopt };
      }
      else {

        return { std::move( keyword ),
                 std::make_optional( std::string( match[1] ) ),
                 std::make_optional( std::stoi( match[2] ) ),
                 std::nullopt ,
                 std::nullopt};
      }
    }

    Log::error( "Unknown keyword found: \'{}\'", keyword );
    throw std::exception();
  }
}
