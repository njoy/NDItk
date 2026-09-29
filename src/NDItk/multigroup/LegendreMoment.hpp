#ifndef NJOY_NDITK_MULTIGROUP_LEGENDREMOMENT
#define NJOY_NDITK_MULTIGROUP_LEGENDREMOMENT

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
 *  @brief A Legendre moment subrecord for multigroup neutron data
 */
class LegendreMoment : protected base::SubListRecord< LegendreMoment, double > {

  friend class base::SubListRecord< LegendreMoment, double >;
  using Parent = base::SubListRecord< LegendreMoment, double >;

  /* fields */

  unsigned int incident_;
  unsigned int outgoing_;

  /* auxiliary functions */

  /**
   *  @brief Verify the Legendre moment values
   *
   *  The following verification tests are performed:
   *    - there are at least two values
   *    - the matrix is the correct size
   *
   *  @param[in] data    the data values in the Legendre moment subrecord
   */
  template < typename Range >
  static void verify( const Range& data,
                      std::size_t incident, std::size_t outgoing ) {

    if ( data.size() < 2 ) {

      Log::error( "Expected at least 2 data values consisting of a Legendre order\n"
                  "and at least one matrix value" );
      Log::info( "Found {} data values", data.size() );
      throw std::exception();
    }

    if ( data.size() - 1  != incident * outgoing ) {

      Log::error( "Expected a matrix of size {} by {}, or with {} elements",
                  incident, outgoing, incident * outgoing );
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
   *  @param[in] values     the matrix values
   *  @param[in] incident   the number of incident groups
   *  @param[in] outgoing   the number of outgoing groups
   */
  LegendreMoment( int order, std::vector< double > values,
                  std::size_t incident, std::size_t outgoing ) :
    Parent( generateData( order, std::move( values ) ) ),
    incident_( incident ), outgoing_( outgoing ) {

    verify( this->values(), this->numberPrimaryGroups(), this->numberOutgoingGroups() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] order      the Legendre order of the moment
   *  @param[in] values     the matrix values
   *  @param[in] incident   the number of incident groups
   */
  LegendreMoment( int order, std::vector< double > values, std::size_t incident ) :
    LegendreMoment( order, std::move( values ), incident, incident ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin      the begin iterator of the cross section
   *  @param[in] end        the end iterator of the cross section
   *  @param[in] incident   the number of incident groups
   *  @param[in] outgoing   the number of outgoing groups
   */
  LegendreMoment( Iterator begin, Iterator end,
                  std::size_t incident, std::size_t outgoing ) :
    Parent( begin, end ),
    incident_( incident ), outgoing_( outgoing ) {

    verify( this->values(), this->numberPrimaryGroups(), this->numberOutgoingGroups() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] begin      the begin iterator of the cross section
   *  @param[in] end        the end iterator of the cross section
   *  @param[in] incident   the number of incident groups
   */
  LegendreMoment( Iterator begin, Iterator end, std::size_t incident ) :
    LegendreMoment( begin, end, incident, incident ) {}

  /* methods */

  /**
   *  @brief Return the Legendre moment order
   */
  int order() const { return static_cast< int >( std::round( this->value( 0 ) ) ); }

  /**
   *  @brief Return the number of incident groups defined by this record
   */
  unsigned int numberPrimaryGroups() const { return this->incident_; }

  /**
   *  @brief Return the number of outgoing groups defined by this record
   */
  unsigned int numberOutgoingGroups() const { return this->outgoing_; }

  /**
   *  @brief Return the matrix defined by this record
   */
  auto matrix() const {

    using namespace njoy::tools;
    return this->values( 1, this->size() - 1 )
               | std23::views::chunk( this->numberOutgoingGroups() );
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
