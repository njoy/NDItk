#ifndef NJOY_NDITK_THERMONUCLEAR_INTERPOLATIONREGIONS
#define NJOY_NDITK_THERMONUCLEAR_INTERPOLATIONREGIONS

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "NDItk/base/ColumnData.hpp"

namespace njoy {
namespace NDItk {
namespace thermonuclear {

/**
 *  @brief A subrecord for representing interpolated data regions
 */
class InterpolationRegions : protected base::ColumnData<int, 2> {

  friend class base::ColumnData<int, 2>;
  using Parent = base::ColumnData<int, 2>;

  /* auxiliary functions */

  /**
   *  @brief Verify the interpolation regions
   *
   *  The following verification tests are performed:
   *    - there is at least one region
   *    - there are the correct number of indices and interpolation types
   *    - the indices are valid (the data is in sequential order)
   *
   *  @param[in] data    the data values in the subrecord
   */
  template < typename Range >
  static void verify( const Range& data ) {

    for (int i=3; i < data.size(); ++i) {

      if ( data[i] < 1 ) {

        Log::error( "End indices must be 1-based" );
        Log::info( "Found an index of {}", data[i] );
        throw std::exception();
      }
    }

    for (int i=3; i < data.size(); ++i) {

      if ( data[i] <= data[i-2] ) {

        Log::error( "End indices must have the regions' data being sequential" );
        Log::info( "Found {} and {} adjacent ending indices", data[i-2], data[i] );
        throw std::exception();
      }
    }
  }

  /**
   *  @brief Generate the subrecord's data vector
   *
   *  @param[in] endIndices    a vector of 1-based indices signifying the inclusive end of each region's data
   *  @param[in] interpTypes   a vector of integers specifying the interpolation type for each region
   */
  static std::vector<int>
  generateData( std::vector<int> endIndices, std::vector<int> interpTypes ) {

    if ( endIndices.size() != interpTypes.size() ) {

      Log::error( "The number of indices and interpolation types is inconsistent" );
      Log::info( "Found {} boundary indices", endIndices.size() );
      Log::info( "Found {} interpolation types", interpTypes.size() );
      throw std::exception();
    }

    std::vector<int> data;

    for ( int i = 0; i < endIndices.size(); ++i ) {

      data.push_back( endIndices[i] );
      data.push_back( interpTypes[i] );
    }

    return data;
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   */
  InterpolationRegions() = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] endIndices    a vector of 1-based indices signifying the inclusive end of each region's data
   *  @param[in] interpTypes   a vector of integers specifying the interpolation type for each region
   */
  InterpolationRegions( std::vector<int> endIndices, std::vector<int> interpTypes ) :
    Parent( generateData( std::move(endIndices), std::move(interpTypes) ) ) {

    verify( this->values() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the begin iterator of the interpolation regions
   *  @param[in] end      the end iterator of the interpolation regions
   */
  InterpolationRegions( Iterator begin, Iterator end ) :
    Parent( begin, end ) {

    verify( this->values() );
  }

  /* methods */

  /**
   *  @brief Return the number of interpolation regions
   */
  auto numberInterpolationRegions() const { return this->numberRows(); }

  /**
   *  @brief Return the 1-based indices for the end of each region
   */
  auto boundaries() const { return this->column(0); };

  /**
   *  @brief Return the interpolation types
   */
  auto interpolants() const { return this->column(1); };

  using Parent::values;
  using Parent::size;
  using Parent::empty;
  using Parent::begin;
  using Parent::end;

  /**
   *  @brief Write the record data
   *
   *  This assumes that the record is not empty.
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    auto indentLevel  = 1;
    auto indentPrefix = [](int n){ return std::string(2*n, ' '); };

    std::ostringstream buffer;

    buffer << indentPrefix(indentLevel) << this->numberInterpolationRegions() << "\n";

    for (int i=0; i < this->numberInterpolationRegions(); ++i) {

      buffer << indentPrefix(indentLevel) << this->boundaries()[i]
             << indentPrefix(indentLevel) << this->interpolants()[i] << "\n";
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  };
};

} // thermonuclear namespace
} // NDItk namespace
} // njoy namespace

#endif
