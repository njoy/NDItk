#ifndef NJOY_NDITK_DEPLETION_TARGET
#define NJOY_NDITK_DEPLETION_TARGET

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/FreeFormatCharacter.hpp"
#include "tools/disco/FreeFormatInteger.hpp"
#include "NDItk/base/Record.hpp"
#include "NDItk/depletion/Product.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief A target record for depletion data
 */
class Target : protected base::Record {

  /* auxiliary functions */

  /**
   *  @brief Verify the vector of depletion products
   *
   *  The following verification tests are performed:
   *    - there is at least one reaction
   *
   *  @param[in] products    the depletion product vector to be verified
   */
  template < typename Range >
  static void verify( const Range& products ) {

    if ( products.size() < 1 ) {

      Log::error( "Expected at least one product, found {}", products.size() );
      throw std::exception();
    }
  }

public:

  /* fields */

  int identifier_;
  std::vector< Product > products_;

  /* constructor */

  /**
   *  @brief Default constructor
   */
  Target():
    Record( base::Keyword( "target" ) ),
    identifier_(),
    products_() {}

  /**
   *  @brief Constructor
   *
   *  @param[in] identifier   target particle identifier
   *  @param[in] products     vector of depletion products
   */
  Target( int identifier, std::vector< Product > products ):
    Record( base::Keyword( "target" ) ),
    identifier_( identifier ),
    products_( std::move(products) ) {

      verify( this->products() );
    }

  /* methods */

  /**
   *  @brief Return the target particle identifier
   */
  int targetIdentifier() const { return this->identifier_; }

  /**
   *  @brief Return the number of products for this target
   */
  int numberProducts() const { return this->products_.size(); }

  /**
   *  @brief Return the product data for this target
   */
  const std::vector< Product >& products() const { return this->products_; }

  using base::Record::keyword;

  /*
   *  @brief Read the record data
   *
   *  @param[in,out] iter        an iterator to the current position in the input
   *  @param[in,out] end         an iterator to the end of the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    std::string keyword;

    // read in target particle identifier
    this->identifier_ = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );

    // "num_products" keyword (not stored as record)
    keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );
    if ( keyword != "num_products" ) {
      Log::error( "Expected the 'num_products' keyword as the second entry in a 'Target' record" );
      Log::info( "Found {} as a keyword instead", keyword );
    }

    // read in number of products
    auto numberProducts = njoy::tools::disco::FreeFormatInteger::read<int>( iter, end );
    if ( numberProducts <= 0 ) {
      Log::error( "Expected at least one 'Product' record in a 'Target' record" );
    }

    // read in the vector of products
    this->products_.resize(numberProducts);
    for ( auto& entry : this->products_ ) {

      // "product" keyword
      keyword = njoy::tools::disco::FreeFormatCharacter::read<std::string>( iter, end );

      if ( keyword != "product" ) {
        Log::error( "Expected the 'product' keyword as the next entry in a 'Target' record" );
        Log::info( "Found {} as a keyword instead", keyword );
      }

      // read in product and add to the data
      entry.read( iter, end );
    }

    verify( this->products() );
  }

  /**
  *   @brief Print the record
  *
  *   @param[in] iter     the current position in the output
  */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    auto indentLevel  = 1;
    auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

    std::ostringstream buffer;

    buffer << indentPrefix(indentLevel) << this->keyword() << "\n";

    buffer << indentPrefix(indentLevel+1) << this->targetIdentifier() << "\n";

    buffer << indentPrefix(indentLevel+1) << "num_products\n";
    buffer << indentPrefix(indentLevel+2) << this->numberProducts() << "\n";

    for (const auto& entry : this->products() ) {

      std::string tmp;
      auto tmp_output = std::back_inserter(tmp);
      entry.print( tmp_output );
      buffer << tmp;
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  }

};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
