#ifndef NJOY_NDITK_MULTIGROUP_METADATA
#define NJOY_NDITK_MULTIGROUP_METADATA

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
namespace multigroup {

/**
 *  @brief Metadata associated with multigroup neutron data
 */
class Metadata {

  /* fields */

  base::SingleStringRecord zaid_;
  base::InformationRecord information_;
  base::SingleStringRecord library_name_;
  base::SingleStringRecord source_date_;
  base::SingleStringRecord process_date_;
  base::SingleRealRecord awr_;
  base::SingleRealRecord atomic_weight_;
  base::SingleRealRecord temperature_;
  base::SingleRealRecord dilution_;
  base::SingleIntegerRecord primary_groups_;
  base::SingleIntegerRecord outgoing_particles_;
  std::vector< base::SingleIntegerRecord > outgoing_groups_;
  base::SingleIntegerRecord legendre_order_;
  std::vector< base::SingleIntegerRecord > outgoing_legendre_order_;
  base::SingleIntegerRecord upscatter_groups_;
  base::SingleIntegerRecord downscatter_groups_;
  base::SingleIntegerRecord number_reactions_;

  /* auxiliary functions */

  /**
   *  @brief A helper function to generate the secondary group recors
   */
  static std::vector< base::SingleIntegerRecord >
  generateSecondaryGroups( const std::map< unsigned int, unsigned int >& outgoing ) {

    std::vector< base::SingleIntegerRecord > data;
    data.reserve( outgoing.size() );
    for ( auto&& entry : outgoing ) {

      data.emplace_back( base::Keyword( "num_grps", entry.first ), entry.second );
    }
    return data;
  }

  /**
   *  @brief A helper function to generate the secondary group recors
   */
  static std::vector< base::SingleIntegerRecord >
  generateSecondaryLegendreOrder( const std::map< unsigned int, unsigned int >& outgoing ) {

    std::vector< base::SingleIntegerRecord > data;
    data.reserve( outgoing.size() );
    for ( auto&& entry : outgoing ) {

      data.emplace_back( base::Keyword( "pn_order", entry.first ), entry.second );
    }
    return data;
  }

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
               information_(),
               library_name_( base::Keyword( "library_name" ) ),
               source_date_( base::Keyword( "date_source" ) ),
               process_date_( base::Keyword( "date_processed" ) ),
               awr_( base::Keyword( "awr" ) ),
               atomic_weight_( base::Keyword( "at_wgt" ) ),
               temperature_( base::Keyword( "temp" ) ),
               dilution_( base::Keyword( "sig_0" ) ),
               primary_groups_( base::Keyword( "num_grps" ) ),
               outgoing_particles_( base::Keyword( "num_sec_parts" ) ),
               outgoing_groups_(),
               legendre_order_( base::Keyword( "pn_order" ) ),
               outgoing_legendre_order_(),
               upscatter_groups_( base::Keyword( "up_grps" ) ),
               downscatter_groups_( base::Keyword( "down_grps" ) ),
               number_reactions_( base::Keyword( "num_reac" ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] zaid                 the zaid of the table
   *  @param[in] libname              the library name
   *  @param[in] process              the processing date
   *  @param[in] awr                  the atomic weight ratio of the target
   *                                  (with respect to the neutron mass)
   *  @param[in] temperature          the temperature of the target
   *  @param[in] dilution             the dilution (aka sigma0)
   *  @param[in] groups               the number of groups in the primary group structure
   *  @param[in] outgoing_groups      the number of groups in the outgoing group structures
   *  @param[in] reactions            the number of reactions defined in the table
   *  @param[in] legendre             the number of legendre moments in the scattering matrix
   *  @param[in] outgoing_legendre    the number of legendre moments in the outgoing
   *                                  production matrices
   *  @param[in] information          the table information line (optional)
   *  @param[in] source               the source date (optional)
   *  @param[in] weight               the atomic weight of the target (optional)
   *  @param[in] upscatter            the number of upscatter groups (optional)
   *  @param[in] downscatter          the number of downscatter groups (optional)
   */
  Metadata( std::string zaid, std::string libname, std::string process,
            double awr, double temperature, double dilution,
            unsigned int groups,
            unsigned int reactions, unsigned int legendre,
            const std::map< unsigned int, unsigned int >& outgoing_groups,
            const std::map< unsigned int, unsigned int >& outgoing_legendre,
            std::optional< std::string > information = std::nullopt,
            std::optional< std::string > source = std::nullopt,
            std::optional< double  > weight = std::nullopt,
            std::optional< int > upscatter = std::nullopt,
            std::optional< int > downscatter = std::nullopt ) :
      zaid_( base::Keyword( "zaid" ), std::move( zaid ) ),
      information_( information.has_value()
                    ? base::InformationRecord( std::move( information.value() ) )
                    : base::InformationRecord() ),
      library_name_( base::Keyword( "library_name" ), std::move( libname ) ),
      source_date_( source.has_value()
                    ? base::SingleStringRecord( base::Keyword( "date_source" ), std::move( source.value() ) )
                    : base::SingleStringRecord( base::Keyword( "date_source" ) ) ),
      process_date_( base::Keyword( "date_processed" ), std::move( process ) ),
      awr_( base::Keyword( "awr" ), awr ),
      atomic_weight_( weight.has_value()
                      ? base::SingleRealRecord( base::Keyword( "at_wgt" ), weight.value() )
                      : base::SingleRealRecord( base::Keyword( "at_wgt" ) ) ),
      temperature_( base::Keyword( "temp" ), temperature ),
      dilution_( base::Keyword( "sig_0" ), dilution ),
      primary_groups_( base::Keyword( "num_grps" ), groups ),
      outgoing_particles_( outgoing_groups.size() > 0
                           ? base::SingleIntegerRecord( base::Keyword( "num_sec_parts" ), outgoing_groups.size() )
                           : base::SingleIntegerRecord( base::Keyword( "num_sec_parts" ) ) ),
      outgoing_groups_( generateSecondaryGroups( outgoing_groups ) ),
      legendre_order_( base::SingleIntegerRecord( base::Keyword( "pn_order" ), legendre ) ),
      outgoing_legendre_order_( generateSecondaryLegendreOrder( outgoing_legendre ) ),
      upscatter_groups_( upscatter.has_value()
                         ? base::SingleIntegerRecord( base::Keyword( "up_grps" ), upscatter.value() )
                         : base::SingleIntegerRecord( base::Keyword( "up_grps" ) ) ),
      downscatter_groups_( downscatter.has_value()
                           ? base::SingleIntegerRecord( base::Keyword( "down_grps" ), downscatter.value() )
                           : base::SingleIntegerRecord( base::Keyword( "down_grps" ) ) ),
      number_reactions_( base::Keyword( "num_reac" ), reactions ) {}

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
           ( keyword == this->awr_.keyword() ) ||
           ( keyword == this->atomic_weight_.keyword() ) ||
           ( keyword == this->temperature_.keyword() ) ||
           ( keyword == this->dilution_.keyword() ) ||
           ( keyword == this->number_reactions_.keyword() ) ||
           ( keyword.find( this->primary_groups_.keyword() ) == 0 ) ||
           ( keyword == this->outgoing_particles_.keyword() ) ||
           ( keyword.find( this->legendre_order_.keyword() ) == 0 ) ||
           ( keyword == this->upscatter_groups_.keyword() ) ||
           ( keyword == this->downscatter_groups_.keyword() );
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
   *  @brief Return the atomic weight ratio of the target (with respect
   *         to the neutron mass)
   */
  decltype(auto) atomicWeightRatio() const { return this->awr_.data(); }

  /**
   *  @brief Return the atomic weight of the target
   */
  decltype(auto) atomicWeight() const { return this->atomic_weight_.data(); }

  /**
   *  @brief Return the temperature of the target
   */
  decltype(auto) temperature() const { return this->temperature_.data(); }

  /**
   *  @brief Return the dilution (aka sigma0)
   */
  decltype(auto) dilution() const { return this->dilution_.data(); }

  /**
   *  @brief Return the number of groups in the primary group structure
   */
  decltype(auto) numberGroups() const { return this->primary_groups_.data(); }

  /**
   *  @brief Return the number of outgoing particles
   */
  decltype(auto) numberOutgoingParticles() const { return this->outgoing_particles_.data(); }

  /**
   *  @brief Return the number of groups in the outgoing group structure
   *         for a given particle
   *
   *  @param[int] particle   the outgoing particle identifier
   */
  decltype(auto) numberOutgoingGroups( unsigned int particle ) const {

    auto pos = std::lower_bound( this->outgoing_groups_.begin(),
                                 this->outgoing_groups_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_groups_.end() ) {

      if ( pos->particle() == particle ) {

        return pos->data();
      }
    }
    Log::error( "The requested outgoing particle \'{}\' is not present", particle );
    throw std::exception();
  }

  /**
   *  @brief Return the number of reactions defined in the table
   */
  decltype(auto) numberReactions() const { return this->number_reactions_.data(); }

  /**
   *  @brief Return the number of Legendre moments defined in the table
   */
  decltype(auto) numberLegendreMoments() const {

    return this->legendre_order_.data();
  }

  /**
   *  @brief Return the number of Legendre moments defined in the table
   *         for a given particle
   *
   *  @param[int] particle   the outgoing particle identifier
   */
  decltype(auto) numberOutgoingLegendreMoments( unsigned int particle ) const {

    auto pos = std::lower_bound( this->outgoing_legendre_order_.begin(),
                                 this->outgoing_legendre_order_.end(),
                                 particle,
                                 [] ( auto&& left, auto&& right ) {

                                   return left.particle() < right;
                                 } );
    if ( pos != this->outgoing_legendre_order_.end() ) {

      if ( pos->particle() == particle ) {

        return pos->data();
      }
    }
    Log::error( "The requested outgoing particle \'{}\' is not present", particle );
    throw std::exception();
  }

  /**
   *  @brief Return the number of upscatter groups defined in the table
   */
  decltype(auto) numberUpscatterGroups() const {

    return this->upscatter_groups_.data();
  }

  /**
   *  @brief Return the number of downscatter groups defined in the table
   */
  decltype(auto) numberDownscatterGroups() const {

    return this->downscatter_groups_.data();
  }

  /**
   *  @brief Read the metadata record content
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( const std::string& keyword, Iterator& iter, const Iterator& end ) {

    if      ( keyword == this->zaid_.keyword() )               { readRecord( this->zaid_, iter, end ); }
    else if ( keyword == this->information_.keyword() )        { readRecord( this->information_, iter, end ); }
    else if ( keyword == this->library_name_.keyword() )       { readRecord( this->library_name_, iter, end ); }
    else if ( keyword == this->source_date_.keyword() )        { readRecord( this->source_date_, iter, end ); }
    else if ( keyword == this->process_date_.keyword() )       { readRecord( this->process_date_, iter, end ); }
    else if ( keyword == this->awr_.keyword() )                { readRecord( this->awr_, iter, end ); }
    else if ( keyword == this->atomic_weight_.keyword() )      { readRecord( this->atomic_weight_, iter, end ); }
    else if ( keyword == this->temperature_.keyword() )        { readRecord( this->temperature_, iter, end ); }
    else if ( keyword == this->dilution_.keyword() )           { readRecord( this->dilution_, iter, end ); }
    else if ( keyword == this->number_reactions_.keyword() )   { readRecord( this->number_reactions_, iter, end ); }
    else if ( keyword == this->upscatter_groups_.keyword() )   { readRecord( this->upscatter_groups_, iter, end ); }
    else if ( keyword == this->downscatter_groups_.keyword() ) { readRecord( this->downscatter_groups_, iter, end ); }
    else if ( keyword == this->outgoing_particles_.keyword() ) { readRecord( this->outgoing_particles_, iter, end ); }
    else if ( keyword.find( this->primary_groups_.keyword() ) == 0 ) {

      if ( keyword == this->primary_groups_.keyword() ) {

        readRecord( this->primary_groups_, iter, end );
      }
      else {

        base::Keyword secondary( keyword );
        auto pos = std::lower_bound( this->outgoing_groups_.begin(),
                                     this->outgoing_groups_.end(),
                                     secondary.particle(),
                                     [] ( auto&& left, auto&& right ) {

                                       return left.particle() < right;
                                     } );
        if ( pos != this->outgoing_groups_.end() ) {

          if ( pos->particle() == secondary.particle() ) {

            Log::error( "Duplicate keyword found: \'{}\'", secondary.keyword() );
            throw std::exception();
          }
        }
        pos = this->outgoing_groups_.insert( pos, base::SingleIntegerRecord( std::move( secondary ) ) );
        readRecord( *pos, iter, end );
      }
    }
    else if ( keyword.find( this->legendre_order_.keyword() ) == 0 ) {

      if ( keyword == this->legendre_order_.keyword() ) {

        readRecord( this->legendre_order_, iter, end );
      }
      else {

        base::Keyword secondary( keyword );
        auto pos = std::lower_bound( this->outgoing_legendre_order_.begin(),
                                     this->outgoing_legendre_order_.end(),
                                     secondary.particle(),
                                     [] ( auto&& left, auto&& right ) {

                                       return left.particle() < right;
                                     } );
        if ( pos != this->outgoing_legendre_order_.end() ) {

          if ( pos->particle() == secondary.particle() ) {

            Log::error( "Duplicate keyword found: \'{}\'", secondary.keyword() );
            throw std::exception();
          }
        }
        pos = this->outgoing_legendre_order_.insert( pos, base::SingleIntegerRecord( std::move( secondary ) ) );
        readRecord( *pos, iter, end );
      }
    }
    else {

      Log::error( "Record with keyword \'{}\' is not part of the "
                  "multigroup metadata", keyword );
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
    this->awr_.print( iter );
    this->atomic_weight_.print( iter );
    this->temperature_.print( iter );
    this->dilution_.print( iter );
    this->primary_groups_.print( iter );
    this->number_reactions_.print( iter );
    this->legendre_order_.print( iter );
    this->upscatter_groups_.print( iter );
    this->downscatter_groups_.print( iter );
    this->outgoing_particles_.print( iter );
    for ( const auto& entry : this->outgoing_groups_ ) { entry.print( iter ); }
    for ( const auto& entry : this->outgoing_legendre_order_ ) { entry.print( iter ); }
  };
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
