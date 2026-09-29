#ifndef NJOY_NDITK_BASE_COLUMNDATA
#define NJOY_NDITK_BASE_COLUMNDATA

// system includes
#include <iomanip>
#include <sstream>

// other includes
#include "tools/std23/views.hpp"
#include "NDItk/base/SubListRecord.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief Sublist for storing and accessing column-formatted data.
 */
template< typename T, int ncol >
class ColumnData : protected SubListRecord< ColumnData<T,ncol>, T > {

  friend class SubListRecord< ColumnData<T,ncol>, T >;
  using Parent = SubListRecord< ColumnData<T,ncol>, T >;

  /* auxiliary functions */

  /**
   *  @brief Verify the column data
   *
   *  The following verification tests are performed:
   *    - there are the correct number of columns
   *
   *  @param[in] data    the data values in the subrecord
   */
  template < typename Range >
  static void verify( const Range& data ) {

    if ( data.size() % ncol != 0 ) {

      Log::error( "The columns must have data of equal length" );
      Log::info(
        "Found {} data points, which can not be subdivided into {} equal-length columns",
        data.size(), ncol
      );
      throw std::exception();
    }
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

    auto indentLevel  = 1;
    auto indentPrefix = [](int n){ return std::string(2*n, ' '); };
    auto maskFirst    = [](int i){ return ( (i == 0) ? 1 : 0 );  };

    std::ostringstream buffer;
    buffer << std::setprecision(15);

    auto nrow = this->size() / this->numberColumns();

    for (int i=0; i < nrow; ++i) {

      for (int j=0; j < this->numberColumns(); ++j) {

        buffer << indentPrefix( (indentLevel-1)*maskFirst(i) + 1 )
               << this->value( i*this->numberColumns() + j );
      }

      buffer << "\n";
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  };

public:

  using Iterator = typename Parent::Iterator;

  /* constructor */

  /**
   *  @brief Default constructor
   */
  ColumnData() = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] data     the data to be interpreted as columns
   */
  ColumnData( std::vector<T> data ) :
    Parent( std::move(data) ) {

    verify( this->values() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the column data
   *  @param[in] end      the end iterator of the column data
   */
  ColumnData( Iterator begin, Iterator end ) :
    Parent( begin, end ) {

    verify( this->values() );
  }

  /**
   *  @brief Return the number of columns
   */
  auto numberColumns() const { return ncol; }

  /**
   *  @brief Return the number of rows
   */
  auto numberRows() const { return this->size() / ncol; }

  /**
   *  @brief Return a view of a column's data
   */
  auto column( size_t index ) const {

    if ( index > ncol ) {

      Log::error( "The requested index is greater than the number of columns" );
      Log::info( "Requested index {} but there are {} columns", index, ncol );
      throw std::exception();
    }

    return this->values( index, this->size() ) | njoy::tools::std23::views::stride( ncol );
  }

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;
  using Parent::print;
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
