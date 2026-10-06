#ifndef NJOY_NDITK_DEPLETION_PRODUCT
#define NJOY_NDITK_DEPLETION_PRODUCT

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/IntegerListRecord.hpp"
#include "NDItk/depletion/Multiplicities.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief A product record for depletion data
 */
class Product : protected base::IntegerListRecord {

  /* fields */

  Multiplicities multiplicities_;

  /* auxiliary functions */

  /**
   *  @brief Generate the record's data vector
   *
   *  @param[in] multiplicities   a depletion::Multiplicities SubListRecord
   */
  static std::vector< int > generateData( Multiplicities  multiplicities ) {

    // generate the data vector
    std::vector< int > data;
    data.insert( data.end(), multiplicities.begin(), multiplicities.end() );

    return data;
  }

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  Product() :
      IntegerListRecord( base::Keyword( "product" ) ),
      multiplicities_() {}

  /**
   *  @brief Constructor
   *
   *  @param[in] multiplicities   a depletion::Multiplicities SubListRecord
   */
  Product( Multiplicities multiplicities ) :
      IntegerListRecord( base::Keyword( "product" ),
                         generateData( std::move( multiplicities ) ) ),
      multiplicities_( this->begin(), this->end() ) {}

  /**
   *  @brief Copy constructor
   */
  Product( const Product& base ) :
      IntegerListRecord( base ),
      multiplicities_( this->begin(), this->end() ) {}

  /**
   *  @brief Move constructor
   */
  Product( Product&& base ) :
      IntegerListRecord( std::move( base ) ),
      multiplicities_( this->begin(), this->end() ) {}

  /**
   *  @brief Copy assignment
   */
  Product& operator=( const Product& base ) {

    if ( this != &base ) {

      base::IntegerListRecord::operator=( base );
      this->multiplicities_ = Multiplicities( this->begin(), this->end() );
    }
    return *this;
  }

  /**
   *  @brief Move assignment
   */
  Product& operator=( Product&& base ) {

    if ( this != &base ) {

      base::IntegerListRecord::operator=( std::move( base ) );
      this->multiplicities_ = Multiplicities( this->begin(), this->end() );
    }
    return *this;
  }

  /* methods */

  /**
   *  @brief Return the reaction product identifier
   */
  int reactionProduct() const { return this->multiplicities_.reactionProduct(); }

  /**
   *  @brief Return the number of reactions with this product
   */
  int numberReactions() const { return this->multiplicities_.numberReactions(); }

  /**
   *  @brief Return the reaction identifiers
   */
  auto reactionIdentifiers() const { return this->multiplicities_.reactionIdentifiers(); }

  /**
   *  @brief Return the reaction multiplicities
   */
  auto multiplicities() const { return this->multiplicities_.multiplicities(); }

  using base::IntegerListRecord::keyword;
  using base::IntegerListRecord::values;
  using base::IntegerListRecord::size;
  using base::IntegerListRecord::empty;
  using base::IntegerListRecord::begin;
  using base::IntegerListRecord::end;

  /*
   *  @brief Read the record data
   *
   *  @param[in,out] iter        an iterator to the current position in the input
   *  @param[in,out] end         an iterator to the end of the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    std::vector< int > data;
    data.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
    data.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
    auto numberReactions = data.back();

    for ( int i=0; i < numberReactions; ++i ) {

      data.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
      data.push_back( njoy::tools::disco::FreeFormatInteger::read<int>( iter, end ) );
    }

    this->data() = data;

    this->multiplicities_ = Multiplicities( this->begin(), this->end() );
  }

  /**
   *  @brief Print the record (if it is not empty)
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    if ( ! this->empty() ) {

      auto indentLevel  = 2;
      auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

      for ( auto c : indentPrefix(indentLevel) + this->keyword() + "\n" ) {
        *iter++ = c;
      }

      this->multiplicities_.print( iter );
    }
  };
};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
