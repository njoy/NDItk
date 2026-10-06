#ifndef NJOY_NDITK_DEPLETION_MULTIPLICITIES
#define NJOY_NDITK_DEPLETION_MULTIPLICITIES

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace depletion {

/**
 *  @brief A reaction product multiplicity subrecord for depletion data
 */
class Multiplicities : protected base::SubListRecord< Multiplicities, int > {

  friend class base::SubListRecord< Multiplicities, int >;
  using Parent = base::SubListRecord< Multiplicities, int >;

  /* auxiliary functions */

  /**
   *  @brief Verify the multiplicity data values
   *
   *  The following verification tests are performed:
   *    - there are at least two values
   *    - the number of multiplicity values are more than zero
   *    - the number of multiplicity data match the declared length
   *
   *  @param[in] data    the data values in the cross section subrecord
   */
  template < typename Range >
  static void verify( const Range& data ) {

    if ( data.size() < 2 ) {

      Log::error( "Expected at least 2 data values consisting of a reaction product,\n"
                  "and the number of reaction identifiers" );
      Log::info( "Found {} data values", data.size() );
      throw std::exception();
    }

    if ( data[1] < 0 ) {

      Log::error( "The number of reaction identifiers cannot be less than zero" );
      Log::info( "Found {} as the number of reaction identifiers", data[1] );
      throw std::exception();
    }

    if ( data.size() != 2 + 2 * data[1] ) {

      Log::error( "Expected at least {} data values consisting of a reactino product,\n"
                  "the number of reaction identifiers (in this case equal to {}) followed\n"
                  "by {} reaction identifier and multiplicity value pairs",
                  2 + 2 * data[1], data[1], data[1] );
      Log::info( "Found {} data values", data.size() );
      throw std::exception();
    }
  }

  /**
   *  @brief Generate the subrecord's data vector
   *
   *  @param[in] reactionProduct      the reaction product zaid
   *  @param[in] reactionIdentifiers  the reaction MTs
   *  @param[in] multiplicities       the multiplicity values
   */
  static std::vector< int >
  generateData( int reactionProduct, std::vector< int > reactionIdentifiers,
                  std::vector< int > multiplicities ) {

    auto size = reactionIdentifiers.size();
    if ( multiplicities.size() != size ) {

      Log::error( "The number of reaction identifiers and multiplicities "
                  "is inconsistent" );
      Log::info( "Found {} reaction identifiers", reactionIdentifiers.size() );
      Log::info( "Found {} multiplicity values", multiplicities.size() );
      throw std::exception();
    }
    std::vector< int > data = { reactionProduct, static_cast< int >( size ) };
    for ( unsigned int i = 0; i < size; ++i ) {

      data.push_back( reactionIdentifiers[i] );
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

    auto indentLevel  = 3;
    auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

    std::ostringstream buffer;

    auto x = this->begin();
    buffer << indentPrefix(indentLevel) << x[0] << '\n'
           << indentPrefix(indentLevel) << x[1] << '\n';
    x += 2;

    auto lines = this->numberReactions();

    while ( lines-- ) {

      buffer << indentPrefix(indentLevel) << x[0] << ' ' << x[1] << '\n';
      x += 2;
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  };

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  Multiplicities() = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] product          the reaction product identifier
   *  @param[in] reactions        the reaction identifiers
   *  @param[in] multiplicities   the multiplicity values
   */
  Multiplicities( int product, std::vector< int > reactions,
                  std::vector< int > multiplicities ) :
    Parent( generateData( product, std::move( reactions ), std::move( multiplicities ) ) ) {

    verify( this->values() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the multiplicity section
   *  @param[in] end      the end iterator of the multiplicity section
   */
  Multiplicities( Iterator begin, Iterator end ) :
    Parent( begin, end ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the reaction product identifier
   */
  int reactionProduct() const { return this->value( 0 ); }

  /**
   *  @brief Return the number of reactions identifiers
   */
  int numberReactions() const { return this->value( 1 ); }

  /**
   *  @brief Return the reaction identifiers
   */
  auto reactionIdentifiers() const {

    using namespace njoy::tools;
    return this->values( 2, 2 * this->numberReactions() )
               | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the reaction multiplicities
   */
  auto multiplicities() const {

    using namespace njoy::tools;
    return this->values( 3, 2 * this->numberReactions() - 1 )
               | std23::views::stride( 2 );
  }

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;
};

} // depletion namespace
} // NDItk namespace
} // njoy namespace

#endif
