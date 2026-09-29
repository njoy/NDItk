#ifndef NJOY_NDITK_MULTIGROUP_MULTIPLICITIES
#define NJOY_NDITK_MULTIGROUP_MULTIPLICITIES

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A reaction product multiplicity subrecord for multigroup data
 */
class Multiplicities : protected base::SubListRecord< Multiplicities, int > {

  friend class base::SubListRecord< Multiplicities, int >;
  using Parent = base::SubListRecord< Multiplicities, int >;

  /* auxiliary functions */

  /**
   *  @brief Verify the cross section data values
   *
   *  The following verification tests are performed:
   *    - there are at least two values
   *    - the reaction identifier looks to be an integer
   *
   *  @param[in] data    the data values in the cross section subrecord
   */
  template < typename Range >
  static void verify( const Range& data ) {

    if ( data.size() < 2 ) {

      Log::error( "Expected at least 2 data values consisting of a reaction identifier,\n"
                  "and the number of reaction products" );
      Log::info( "Found {} data values", data.size() );
      throw std::exception();
    }

    if ( data[1] < 0 ) {

      Log::error( "The number of reaction products cannot be less than zero" );
      Log::info( "Found {} as the number of reaction products", data[1] );
      throw std::exception();
    }

    if ( data.size() != 2 + 2 * data[1] ) {

      Log::error( "Expected at least {} data values consisting of a reaction identifier,\n"
                  "the number of reaction products (in this case equal to {}) followed\n"
                  "by {} reaction product identifier and multiplicity value pairs",
                  2 + 2 * data[1], data[1], data[1] );
      Log::info( "Found {} data values", data.size() );
      throw std::exception();
    }
  }

  /**
   *  @brief Generate the subrecord's data vector
   *
   *  @param[in] reaction          the reaction number
   *  @param[in] products          the reaction product identifiers
   *  @param[in] multiplicities    the multiplicity values
   */
  static std::vector< int >
  generateData( int reaction, std::vector< int > products,
                std::vector< int > multiplicities ) {

    auto size = products.size();
    if ( multiplicities.size() != size ) {

      Log::error( "The number of reaction product identifiers and multiplicities "
                  "is inconsistent" );
      Log::info( "Found {} reaction product identifiers", products.size() );
      Log::info( "Found {} multiplicity values", multiplicities.size() );
      throw std::exception();
    }
    std::vector< int > data = { reaction, static_cast< int >( size ) };
    for ( unsigned int i = 0; i < size; ++i ) {

      data.push_back( products[i] );
      data.push_back( multiplicities[i] );
    }
    return data;
  }

  /**
   *  @brief Write the record data
   *
   *  This assumes that the record is not empty.
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void write( OutputIterator& iter ) const {

    std::ostringstream buffer;

    auto x = this->begin();
    buffer << "    " << x[0] << '\n'
           << "    " << x[1] << '\n';
    x += 2;

    auto lines = this->numberReactionProducts();

    while ( lines-- ) {

      buffer << "    " << x[0] << ' ' << x[1] << '\n';
      x += 2;
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  };

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] reaction          the reaction number
   *  @param[in] products          the reaction product identifiers
   *  @param[in] multiplicities    the multiplicity values
   */
  Multiplicities( int reaction, std::vector< int > products,
                  std::vector< int > multiplicities ) :
    Parent( generateData( reaction, std::move( products ), std::move( multiplicities ) ) ) {

    verify( this->values() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the cross section
   *  @param[in] end      the end iterator of the cross section
   */
  Multiplicities( Iterator begin, Iterator end ) :
    Parent( begin, end ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the reaction identifier
   */
  int identifier() const { return this->value( 0 ); }

  /**
   *  @brief Return the number of reaction products
   */
  int numberReactionProducts() const { return this->value( 1 ); }

  /**
   *  @brief Return the reaction product identifiers
   */
  auto reactionProducts() const {

    using namespace njoy::tools;
    return this->values( 2, 2 * this->numberReactionProducts() )
               | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the reaction product multiplicities
   */
  auto multiplicities() const {

    using namespace njoy::tools;
    return this->values( 3, 2 * this->numberReactionProducts() - 1 )
               | std23::views::stride( 2 );
  }

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;
};

} // multigroup namespace
} // NDItk namespace
} // njoy namespace

#endif
