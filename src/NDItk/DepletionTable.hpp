#ifndef NJOY_NDITK_DEPLETION
#define NJOY_NDITK_DEPLETION

// system includes

// other includes
#include "tools/Log.hpp"
#include "NDItk/depletion/Metadata.hpp"
#include "NDItk/depletion/IncidentParticle.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief A product/depletion table
 */
class DepletionTable {

  /* fields */

  depletion::Metadata metadata_;
  std::vector< depletion::IncidentParticle > incident_particles_;

  /* auxiliary functions */

  /**
   *  @brief Verify the depletion data
   *
   *  The following verification tests are performed:
   *    - The number of incident particles must match btw metadata and number of records read
   *    - The number of incident particle records read must be > 0
   */
  void verify() {

    if ( this->metadata_.numberIncidentParticles() != this->numberIncidentParticles() ) {

      Log::error( "Found a different number of incident particle records than indicated in metadata" );
      Log::info( "IncidentParticle records found: {}", this->numberIncidentParticles() );
      Log::info( "incident particles in Metadata: {}", this->metadata_.numberIncidentParticles().value() );
      throw std::exception();
    }

    if ( this->numberIncidentParticles() <= 0 ) {

      Log::error( "Found an invalid number of incident particle records" );
      Log::info( "Found an invalid number of incident particle records: {}", this->numberIncidentParticles() );
      throw std::exception();
    }
  };

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  DepletionTable() :
      metadata_(), incident_particles_() {}

  /**
   *  @brief Constructor
   *
   *  @param[in] zaid              the zaid of the table
   *  @param[in] libname           the library name
   *  @param[in] process           the processing date
   *  @param[in] incident          a vector of IncidentParticle records
   *  @param[in] information       the table information line (optional)
   *  @param[in] source            the source date (optional)
   */
  DepletionTable( std::string zaid,
                  std::string libname,
                  std::string process,
                  std::vector< depletion::IncidentParticle > incident,
                  std::optional< std::string > information = std::nullopt,
                  std::optional< std::string > source = std::nullopt ) :
      metadata_( std::move( zaid ),
                 std::move( libname ),
                 std::move( process ),
                 incident.size(),
                 std::move( information ),
                 std::move( source ) ),
      incident_particles_( std::move( incident ) ) {

    this->verify();
  }

  /* methods */

  /**
   *  @brief Return the metadata of the table
   */
  const depletion::Metadata& metadata() const { return this->metadata_; }

  /**
   *  @brief Return the number of incident particles
   */
  int numberIncidentParticles() const { return this->incident_particles_.size(); }

  /**
   *  @brief Return the record for an incident particle
   *
   * @param[in] particle  the incident particle identifier to find
   */
  const depletion::IncidentParticle&
  incidentParticle( unsigned int particle ) const {

    auto pos = std::lower_bound( this->incident_particles_.begin(),
                                 this->incident_particles_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.incidentIdentifier() < right;
                                 } );
    if ( pos != this->incident_particles_.end() ) {

      if ( pos->incidentIdentifier() == particle ) {

        return *pos;
      }
    }
    Log::error( "The requested incident particle \'{}\' has no associated "
                "record", particle );
    throw std::exception();
  }

  /**
   *  @brief Return the vector containing all incident particle records
   */
  const std::vector< depletion::IncidentParticle >&
  incidentParticles() const { return this->incident_particles_; }

  /**
   *  @brief Read the table data
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    auto tmp_incident = depletion::IncidentParticle();
    std::vector< depletion::IncidentParticle > incident_data;

    std::string keyword;
    while ( ( keyword != "end" ) && ( iter != end ) ) {

      keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );

      // metadata
      if ( this->metadata_.isMetadataKey( keyword ) ) {

        this->metadata_.read( keyword, iter, end );
      }
      // incident particle data
      else if ( keyword == tmp_incident.keyword() ) {

        tmp_incident.read( iter, end );

        incident_data.push_back( tmp_incident );
      }
      // unknown or end keyword
      else {

        if ( keyword != "end" ) {

          Log::error( "Unknown keyword found: \'{}\'", keyword );
          throw std::exception();
        }
      }

      // read over whitespace or until the end
      while ( iter != end && std::isspace( *iter ) ) {

        ++iter;
      }
    }

    this->incident_particles_ = incident_data;

    this->verify();
  };

  /**
   *  @brief Print the NDI table
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->metadata_.print( iter );
    for ( const auto& entry : this->incident_particles_ ) { entry.print( iter ); }
    base::Keyword( "end" ).print( iter );
  };
};

} // NDItk namespace
} // njoy namespace

#endif
