#ifndef NJOY_NDITK_MULTIGROUP_DOWNSCATTERINGLEGENDREMOMENT
#define NJOY_NDITK_MULTIGROUP_DOWNSCATTERINGLEGENDREMOMENT

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
 *  @brief A Legendre moment subrecord for multigroup neutron data using
 *         an upper triangular matrix (deprecated)
 */
class DownScatteringLegendreMoment :
    protected base::SubListRecord< DownScatteringLegendreMoment, double > {

  friend class base::SubListRecord< DownScatteringLegendreMoment, double >;
  using Parent = base::SubListRecord< DownScatteringLegendreMoment, double >;

  /* fields */

  unsigned int groups_;
  std::vector< double > matrix_;

  /* auxiliary functions */

  /**
   *  @brief Verify the Legendre moment values
   *
   *  The following verification tests are performed:
   *    - there are at least two values
   *    - the matrix is the correct size
   *
   *  @param[in] data     the data values in the Legendre moment subrecord
   *  @param[in] groups   the number of groups
   */
  template < typename Range >
  static void verify( const Range& data, std::size_t groups ) {

    if ( data.size() < 2 ) {

      Log::error( "Expected at least 2 data values consisting of a Legendre order\n"
                  "and at least one matrix value" );
      Log::info( "Found {} data values", data.size() );
      throw std::exception();
    }

    if ( data.size() - 1 != groups * ( groups + 1 ) / 2 ) {

      Log::error( "Expected a compressed down scatter matrix for {} groups, "
                  "or with {} elements", groups, groups * ( groups + 1 ) / 2 );
      Log::info( "Found {} matrix elements", data.size() - 1 );
      throw std::exception();
    }
  }

  /**
   *  @brief Generate the subrecord's data vector
   *
   *  @param[in] order     the Legendre order of the moment
   *  @param[in] values    the matrix values
   */
  static std::vector< double >
  generateData( int order, std::vector< double > values ) {

    std::vector< double > data( std::move( values ) );
    data.insert( data.begin(), static_cast< double >( order ) );
    return data;
  }

  /**
   *  @brief Expand the compressed upper triangular matrix into a full square matrix
   *
   *  @param[in] data     the data values in the Legendre moment subrecord
   *  @param[in] groups   the number of groups
   */
  template < typename Range >
  static std::vector< double > generateMatrix( const Range& data, unsigned int groups ) {

    std::vector< double > matrix( groups * groups, 0. );
    std::size_t index = 1;
    for ( unsigned int i = 0; i < groups; ++i ) {

      for ( unsigned int j = i; j < groups; ++j ) {

        matrix[ i * groups + j ] = data[ index ];
        ++index;
      }
    }
    return matrix;
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
    buffer << "    " << static_cast< int >( std::round( *x ) ) << '\n';
    ++x;

    auto full = ( this->size() - 1 ) / 5;
    auto partial = ( this->size() - 1 ) % 5;

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
   *  @param[in] order      the Legendre order of the moment
   *  @param[in] values     the compressed down scatter matrix values
   *  @param[in] groups     the number of groups
   */
  DownScatteringLegendreMoment( int order, std::vector< double > values,
                                std::size_t groups ) :
    Parent( generateData( order, std::move( values ) ) ),
    groups_( groups ) {

    verify( this->values(), this->numberGroups() );
    this->matrix_ = generateMatrix( this->values(), this->numberGroups() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] begin      the begin iterator of the moment data
   *  @param[in] end        the end iterator of the moment data
   *  @param[in] groups     the number of groups
   */
  DownScatteringLegendreMoment( Iterator begin, Iterator end,
                                std::size_t groups ) :
    Parent( begin, end ),
    groups_( groups ) {

    verify( this->values(), this->numberGroups() );
    this->matrix_ = generateMatrix( this->values(), this->numberGroups() );
  }

  /* methods */

  /**
   *  @brief Return the Legendre moment order
   */
  int order() const { return static_cast< int >( std::round( this->value( 0 ) ) ); }

  /**
   *  @brief Return the number of groups defined by this record
   */
  unsigned int numberGroups() const { return this->groups_; }

  /**
   *  @brief Return the number of incident groups defined by this record
   */
  unsigned int numberPrimaryGroups() const { return this->groups_; }

  /**
   *  @brief Return the number of outgoing groups defined by this record
   */
  unsigned int numberOutgoingGroups() const { return this->groups_; }

  /**
   *  @brief Return the full matrix defined by this record
   */
  auto matrix() const {

    return this->matrix_ | njoy::tools::std23::views::chunk( this->numberGroups() );
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
