/**
 *  @brief Read the table data
 *
 *  @param[in] iter   the current position in the input
 */
template< typename Iterator >
void read( Iterator& iter, const Iterator& end ) {

  std::string keyword;
  while ( ( keyword != "end" ) && ( iter != end ) ) {

    keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );

    // metadata
    if ( this->metadata_.isMetadataKey( keyword ) ) {

      this->metadata_.read( keyword, iter, end );
    }
    // primary and outgoing group structure keyword
    else if ( keyword.find( this->primary_structure_.keyword() ) == 0 ) {

      if ( keyword == this->primary_structure_.keyword() ) {

        readPrimaryStructure( iter, end );
      }
      else {

        readOutgoingStructure( keyword, iter, end );
      }
    }
    // velocities
    else if ( keyword == this->velocities_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->velocities_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // flux weights
    else if ( keyword == this->weights_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->weights_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // total cross section
    else if ( keyword == this->total_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->total_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // reaction cross sections
    else if ( keyword == this->xs_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() &&
           this->metadata_.numberReactions().has_value() ) {

        readRecord( this->xs_, iter, end,
                    this->metadata_.numberReactions().value(),
                    this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        if ( ! this->metadata_.numberGroups().has_value() ) {

          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        }
        if ( ! this->metadata_.numberReactions().has_value() ) {

          Log::info( "Required metadata is missing: number of reactions" );
        }
        throw std::exception();
      }
    }
    // scattering matrix
    else if ( keyword == this->scattering_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() &&
           this->metadata_.numberLegendreMoments().has_value() ) {

        readRecord( this->scattering_, iter, end,
                    this->metadata_.numberGroups().value(),
                    this->metadata_.numberLegendreMoments().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        if ( ! this->metadata_.numberGroups().has_value() ) {

          Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        }
        if ( ! this->metadata_.numberLegendreMoments().has_value() ) {

          Log::info( "Required metadata is missing: number of Legendre moments" );
        }
        throw std::exception();
      }
    }
    // average fission energy release
    else if ( keyword == this->release_.keyword() ) {

      readRecord( this->release_, iter, end );
    }
    // prompt fission neutron multiplicity
    else if ( keyword == this->nubar_prompt_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->nubar_prompt_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // delayed fission neutron multiplicity
    else if ( keyword == this->nubar_delayed_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->nubar_delayed_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // total fission neutron multiplicity
    else if ( keyword == this->nubar_total_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->nubar_total_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // prompt fission neutron production
    else if ( keyword == this->production_prompt_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->production_prompt_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // delayed fission neutron production
    else if ( keyword == this->production_delayed_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->production_delayed_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // total fission neutron production
    else if ( keyword == this->production_total_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->production_total_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // prompt fission neutron spectrum vector
    else if ( keyword == this->chi_vector_prompt_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->chi_vector_prompt_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // delayed fission neutron spectrum vector
    else if ( keyword == this->chi_vector_delayed_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->chi_vector_delayed_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // total fission neutron spectrum vector
    else if ( keyword == this->chi_vector_total_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->chi_vector_total_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // prompt fission neutron spectrum matrix
    else if ( keyword == this->chi_matrix_prompt_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->chi_matrix_prompt_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // delayed fission neutron spectrum matrix
    else if ( keyword == this->chi_matrix_delayed_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->chi_matrix_delayed_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // total fission neutron spectrum matrix
    else if ( keyword == this->chi_matrix_total_.keyword() ) {

      if ( this->metadata_.numberGroups().has_value() ) {

        readRecord( this->chi_matrix_total_, iter, end, this->metadata_.numberGroups().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of groups in the primary group structure" );
        throw std::exception();
      }
    }
    // primary and outgoing heating keyword
    else if ( keyword.find( this->primary_heating_.keyword() ) == 0 ) {

      if ( keyword == this->primary_heating_.keyword() ) {

        readPrimaryData( this->primary_heating_, iter, end );
      }
      else {

        readOutgoingData( keyword, this->outgoing_heating_, iter, end );
      }
    }
    // primary and outgoing kerma keyword
    else if ( keyword.find( this->primary_kerma_.keyword() ) == 0 ) {

      if ( keyword == this->primary_kerma_.keyword() ) {

        readPrimaryData( this->primary_kerma_, iter, end );
      }
      else {

        readOutgoingData( keyword, this->outgoing_kerma_, iter, end );
      }
    }
    // outgoing particle types
    else if ( keyword == this->outgoing_particles_.keyword() ) {

      if ( this->metadata_.numberOutgoingParticles().has_value() ) {

        readRecord( this->outgoing_particles_, iter, end,
                    this->metadata_.numberOutgoingParticles().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of outgoing particle types" );
        throw std::exception();
      }
    }
    // outgoing particle transport data
    else if ( keyword == this->outgoing_zaids_.keyword() ) {

      if ( this->metadata_.numberOutgoingParticles().has_value() ) {

        readRecord( this->outgoing_zaids_, iter, end,
                    this->metadata_.numberOutgoingParticles().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of outgoing particle types" );
        throw std::exception();
      }
    }
    // outgoing production matrices
    else if ( keyword.find( "pn_prod_full" ) == 0 ) {

      readOutgoingProductionMatrix( keyword, iter, end );
    }
    // reaction product multiplicities: all
    else if ( keyword == this->product_multiplicities_all_.keyword() ) {

      if ( this->metadata_.numberReactions().has_value() ) {

        readRecord( this->product_multiplicities_all_, iter, end,
                    this->metadata_.numberReactions().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of reactions" );
        throw std::exception();
      }
    }
    // reaction product multiplicities: few
    else if ( keyword == this->product_multiplicities_few_.keyword() ) {

      if ( this->metadata_.numberReactions().has_value() ) {

        readRecord( this->product_multiplicities_few_, iter, end,
                    this->metadata_.numberReactions().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of reactions" );
        throw std::exception();
      }
    }
    // reaction product multiplicities: rmo
    else if ( keyword == this->product_multiplicities_rmo_.keyword() ) {

      if ( this->metadata_.numberReactions().has_value() ) {

        readRecord( this->product_multiplicities_rmo_, iter, end,
                    this->metadata_.numberReactions().value() );
      }
      else {

        Log::error( "Metadata required for the \'\' record was not found", keyword );
        Log::info( "Required metadata is missing: number of reactions" );
        throw std::exception();
      }
    }
    // unknown or end keyword
    else {

      if ( keyword != "end" ) {

        Log::error( "Unknown keyword found: \'{}\'", keyword );
        throw std::exception();
      }
    }

    // read over whitespace or until the end
    while ( std::isspace( *iter ) && iter != end ) {

      ++iter;
    }
  }
  this->verify();
};
