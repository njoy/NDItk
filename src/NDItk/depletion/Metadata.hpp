#ifndef NJOY_NDITK_DEPLETION_METADATA
#define NJOY_NDITK_DEPLETION_METADATA

// system includes
#include <map>

// other includes
#include "tools/Log.hpp"
#include "NDItk/base/InformationRecord.hpp"
#include "NDItk/base/SingleIntegerRecord.hpp"
#include "NDItk/base/SingleRealRecord.hpp"
#include "NDItk/base/SingleStringRecord.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief Metadata associated with production/depletion data table
 */
class Metadata {

  /* fields */

  base::SingleStringRecord zaid_;
  base::InformationRecord information_;
  base::SingleStringRecord library_name_;
  base::SingleStringRecord source_date_;
  base::SingleStringRecord process_date_;
  base::SingleIntegerRecord number_incident_;

  /* auxiliary functions */

  /**
   *  @brief A helper function to read a metadata record
   */
  template < typename Record, typename Iterator >
  static void readRecord( Record& record, Iterator& iter, const Iterator& end ) {

    if ( ! record.empty() ) {

      Log::error( "Duplicate keyword found: \'{}\'", record.keyword() );
      throw std::exception();
    }
    record.read( iter, end );
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  Metadata() : zaid_( base::Keyword( "zaid" ) ),
               information_( ),
               library_name_( base::Keyword( "library_name" ) ),
               source_date_( base::Keyword( "date_source" ) ),
               process_date_( base::Keyword( "date_processed" ) ),
               number_incident_( base::Keyword( "num_inc_parts" ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] zaid                 the zaid of the table
   *  @param[in] libname              the library name
   *  @param[in] process              the processing date
   *  @param[in] incident             the number of incident particles
   *  @param[in] information          the table information line (optional)
   *  @param[in] source               the source date (optional)
   */
  Metadata(
      std::string zaid,
      std::string libname,
      std::string process,
      int incident,
      std::optional< std::string > information = std::nullopt,
      std::optional< std::string > source = std::nullopt ):
          zaid_( base::Keyword( "zaid" ), std::move( zaid ) ),
          information_( information.has_value()
                      ? base::InformationRecord( std::move( information.value() ) )
                      : base::InformationRecord() ),
          library_name_( base::Keyword( "library_name" ), std::move( libname ) ),
          source_date_( source.has_value()
                      ? base::SingleStringRecord( base::Keyword( "date_source" ), std::move( source.value() ) )
                      : base::SingleStringRecord( base::Keyword( "date_source" ) ) ),
          process_date_( base::Keyword( "date_processed" ), std::move( process ) ),
          number_incident_( base::Keyword( "num_inc_parts" ), incident ) {}

  /* methods */

  /**
   *  @brief Return whether or not a given key corresponds to a metadata key
   */
  bool isMetadataKey( const std::string& keyword ) const {

    return ( keyword == this->information_.keyword() ) ||
           ( keyword == this->zaid_.keyword() ) ||
           ( keyword == this->library_name_.keyword() ) ||
           ( keyword == this->source_date_.keyword() ) ||
           ( keyword == this->process_date_.keyword() ) ||
           ( keyword == this->number_incident_.keyword() );
  }

  /**
   *  @brief Return the zaid of the table
   */
  decltype(auto) zaid() const { return this->zaid_.data(); }

  /**
   *  @brief Return the table information line
   */
  decltype(auto) information() const { return this->information_.data(); }

  /**
   *  @brief Return the library name
   */
  decltype(auto) libraryName() const { return this->library_name_.data(); }

  /**
   *  @brief Return the source date
   */
  decltype(auto) sourceDate() const { return this->source_date_.data(); }

  /**
   *  @brief Return the processing date
   */
  decltype(auto) processingDate() const { return this->process_date_.data(); }

  /**
   *  @brief Return the number of incident particles
   */
  decltype(auto) numberIncidentParticles() const { return this->number_incident_.data(); }

  /**
   *  @brief Read the metadata record content
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( const std::string& keyword, Iterator& iter, const Iterator& end ) {

    if      ( keyword == this->zaid_.keyword() )            { readRecord( this->zaid_, iter, end ); }
    else if ( keyword == this->information_.keyword() )     { readRecord( this->information_, iter, end ); }
    else if ( keyword == this->library_name_.keyword() )    { readRecord( this->library_name_, iter, end ); }
    else if ( keyword == this->source_date_.keyword() )     { readRecord( this->source_date_, iter, end ); }
    else if ( keyword == this->process_date_.keyword() )    { readRecord( this->process_date_, iter, end ); }
    else if ( keyword == this->number_incident_.keyword() ) { readRecord( this->number_incident_, iter, end ); }
    else {

      Log::error( "Record with keyword \'{}\' is not part of the "
                  "depletion metadata", keyword );
      throw std::exception();
    }
  };

  /**
   *  @brief Print the metadata
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->zaid_.print( iter );
    this->information_.print( iter );
    this->library_name_.print( iter );
    this->source_date_.print( iter );
    this->process_date_.print( iter );
    this->number_incident_.print( iter );
  };
};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
