#ifndef NJOY_NDITK_MULTIGROUP_METADATA
#define NJOY_NDITK_MULTIGROUP_METADATA

// system includes

// other includes
#include "NDItk/base/SingleIntegerRecord.hpp"
#include "NDItk/base/SingleRealRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief Metadata associated to a neutron NDI file
 */
class Metadata {

  /* fields */
  base::SingleRealRecord awr_;
  base::SingleRealRecord atomic_weight_;
  base::SingleRealRecord temperature_;
  base::SingleRealRecord dilution_;
  base::SingleIntegerRecord groups_;
  base::SingleIntegerRecord upscatter_;
  base::SingleIntegerRecord downscatter_;
  base::SingleIntegerRecord legendre_order_;

  template < typename Record, typename Iterator >
  static void readRecord( Record& record, Iterator& iter, const Iterator& end ) {

    if ( record.content().has_value() ) {

      throw std::runtime_error( "Duplicate keyword" );
    }
    record.read( iter, end );
  }

public:

  Metadata() : awr_( "awr" ), atomic_weight_( "at_wgt" ), temperature_( "temp" ),
               dilution_( "sig_0" ), groups_( "num_grps" ),
               upscatter_( "up_grps" ), downscatter_( "down_grps" ),
               legendre_order_( "pn_order" ) {}

  Metadata( double awr, double weight, double temperature, double dilution,
            unsigned int groups, unsigned int upscatter, unsigned int downscatter,
            unsigned int order ) :
      awr_( "awr", awr ), atomic_weight_( "at_wgt", weight ), temperature_( "temp", temperature ),
      dilution_( "sig_0", dilution ), groups_( "num_grps", groups ),
      upscatter_( "up_grps", upscatter ), downscatter_( "down_grps", downscatter ),
      legendre_order_( "pn_order", order ) {}

  decltype(auto) atomicWeightRatio() const { return this->awr_.content(); }
  decltype(auto) atomicWeight() const { return this->atomic_weight_.content(); }
  decltype(auto) temperature() const { return this->temperature_.content(); }
  decltype(auto) dilution() const { return this->dilution_.content(); }
  decltype(auto) numberGroups() const { return this->groups_.content(); }
  decltype(auto) numberUpscatterGroups() const { return this->upscatter_.content(); }
  decltype(auto) numberDownscatterGroups() const { return this->downscatter_.content(); }
  decltype(auto) legendreOrder() const { return this->legendre_order_.content(); }

  /**
   *  @brief Read the metadata record content
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( const std::string& keyword, Iterator& iter, const Iterator& end ) {

    if      ( keyword == "awr" )       { readRecord( this->awr_, iter, end ); }
    else if ( keyword == "at_wgt" )    { readRecord( this->atomic_weight_, iter, end ); }
    else if ( keyword == "temp" )      { readRecord( this->temperature_, iter, end ); }
    else if ( keyword == "sig_0" )     { readRecord( this->dilution_, iter, end ); }
    else if ( keyword == "num_grps" )  { readRecord( this->groups_, iter, end ); }
    else if ( keyword == "up_grps" )   { readRecord( this->upscatter_, iter, end ); }
    else if ( keyword == "down_grps" ) { readRecord( this->downscatter_, iter, end ); }
    else if ( keyword == "pn_order" )  { readRecord( this->legendre_order_, iter, end ); }
    else {

      throw std::runtime_error( "Unknown keyword" );
    }
  };

  /**
   *  @brief Print the metadata
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    this->awr_.print( iter );
    this->atomic_weight_.print( iter );
    this->temperature_.print( iter );
    this->dilution_.print( iter );
    this->groups_.print( iter );
    this->upscatter_.print( iter );
    this->downscatter_.print( iter );
    this->legendre_order_.print( iter );
  };
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif