#ifndef NJOY_NDITK_MULTIGROUP_CROSSSECTION
#define NJOY_NDITK_MULTIGROUP_CROSSSECTION

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace multigroup {

/**
 *  @brief A cross section subrecord for multigroup neutron data
 */
class CrossSection : protected base::SubListRecord< CrossSection, double > {

  friend class base::SubListRecord< CrossSection, double >;
  using Parent = base::SubListRecord< CrossSection, double >;

  /* auxiliary functions */

  /**
   *  @brief Verify the cross section data values
   *
   *  The following verification tests are performed:
   *    - there are at least three values
   *    - the reaction identifier looks to be an integer
   *
   *  @param[in] data    the data values in the cross section subrecord
   */
  template < typename Range >
  static void verify( const Range& data ) {

    if ( data.size() < 3 ) {

      Log::error( "Expected at least 3 data values consisting of a reaction identifier,\n"
                  "a Q value and at least one cross section value" );
      Log::info( "Found {} data values", data.size() );
      throw std::exception();
    }

    if ( data[0] - static_cast< int >( std::round( data[0] ) ) != 0 ) {

      Log::error( "Expected an integer value for the reaction identifier" );
      Log::info( "Found {} as the reaction identifier", data[0] );
      throw std::exception();
    }
  }

  /**
   *  @brief Generate the subrecord's data vector
   *
   *  @param[in] reaction    the reaction identifier
   *  @param[in] qvalue      the reaction Q value
   *  @param[in] values      the cross section values
   */
  static std::vector< double >
  generateData( int reaction, double qvalue, std::vector< double > values ) {

    std::vector< double > data( std::move( values ) );
    data.insert( data.begin(), qvalue );
    data.insert( data.begin(), static_cast< double >( reaction ) );
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
    buffer << "    " << static_cast< int >( std::round( x[0] ) )
           << ' ' << std::setprecision( 15 ) << x[1] << '\n';
    x += 2;

    auto full = this->numberGroups() / 5;
    auto partial = this->numberGroups() % 5;

    while ( full-- ) {

      buffer << "    " << std::setprecision( 15 ) << x[0];
      buffer << ' ' << std::setprecision( 15 ) << x[1];
      buffer << ' ' << std::setprecision( 15 ) << x[2];
      buffer << ' ' << std::setprecision( 15 ) << x[3];
      buffer << ' ' << std::setprecision( 15 ) << x[4] << '\n';
      x += 5;
    }

    if ( partial ) {

      buffer << "   ";
      while ( partial-- ) {

        buffer << ' ' << std::setprecision( 15 ) << *x;
        ++x;
      }
      buffer << '\n';
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  };

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] reaction   the reaction number
   *  @param[in] qvalue     the q value
   *  @param[in] values     the cross section values
   */
  CrossSection( int reaction, double qvalue, std::vector< double > values ) :
    Parent( generateData( reaction, qvalue, std::move( values ) ) ) {

    verify( this->values() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the cross section
   *  @param[in] end      the end iterator of the cross section
   */
  CrossSection( Iterator begin, Iterator end ) :
    Parent( begin, end ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the reaction identifier
   */
  int identifier() const { return static_cast< int >( std::round( this->value( 0 ) ) ); }

  /**
   *  @brief Return the reaction Q value
   */
  double qvalue() const { return this->value( 1 ); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const { return this->values( 2, this->numberGroups() ); }

  /**
   *  @brief Return the number of groups defined by this record
   */
  unsigned int numberGroups() const { return this->size() - 2; }

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
