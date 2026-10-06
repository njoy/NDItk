#ifndef NJOY_NDITK_BASE_SUBLISTRECORD
#define NJOY_NDITK_BASE_SUBLISTRECORD

// system includes
#include <vector>
#include <optional>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/views.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @class
 *  @brief The base class for a subrecord from an NDI file
 */
template < typename Derived, typename Type >
class SubListRecord {

public:

  using Iterator = typename std::vector< Type >::const_iterator;

private:

  /* fields */

  std::optional< std::vector< Type > > values_;
  Iterator begin_;
  Iterator end_;
  std::size_t length_;

protected:

  /* auxiliary functions */

  /* constructor */

  SubListRecord() = default;

  SubListRecord( const SubListRecord& base ) {

    *this = base;
  }

  SubListRecord( SubListRecord&& base ) {

    *this = std::move( base );
  }

  SubListRecord( const Iterator& begin, const Iterator& end ) :
    values_( std::nullopt ),
    begin_( begin ), end_( end ),
    length_( std::distance( begin, end ) ) {}

  SubListRecord( std::vector< Type > values ) :
    values_( std::move( values ) ) {

    this->begin_ = this->values_->begin();
    this->end_ = this->values_->end();
    this->length_ = this->values_->size();
  }

  SubListRecord& operator=( const SubListRecord& right ) {

    this->values_ = right.values_;
    if ( this->owner() ) {

      this->begin_ = this->values_->begin();
      this->end_ = this->values_->end();
      this->length_ = this->values_->size();
    }
    else {

      this->begin_ = right.begin_;
      this->end_ = right.end_;
      this->length_ = right.length_;
    }
    return *this;
  }

  SubListRecord& operator=( SubListRecord&& right ) {

    this->values_ = std::move( right.values_ );
    if ( this->owner() ) {

      this->begin_ = this->values_->begin();
      this->end_ = this->values_->end();
      this->length_ = this->values_->size();
    }
    else {

      this->begin_ = right.begin_;
      this->end_ = right.end_;
      this->length_ = right.length_;
    }
    return *this;
  }

  /* methods */

  /**
   *  @brief Check whether or not this record owns the data
   */
  bool owner() const { return this->values_.has_value(); }

  /**
   *  @brief Return the begin iterator to the data of the subrecord
   */
  auto begin() const { return this->begin_; }

  /**
   *  @brief Return the end iterator to the data of the subrecord
   */
  auto end() const { return this->end_; }

  /**
   *  @brief Return the size of the subrecord
   */
  std::size_t size() const { return this->length_; }

  /**
   *  @brief Return an iterator to a data element
   *
   *  @param[in] index   the index
   */
  Iterator iterator( std::size_t index ) const {

    return std::next( this->begin(), index );
  }

  /**
   *  @brief Return the data of the subrecord
   */
  auto values() const {

    return njoy::tools::std20::ranges::subrange( this->begin(), this->end() );
  }

  /**
   *  @brief Return a value from the data
   *
   *  @param[in] index   the index
   */
  const Type& value( std::size_t index ) const {

    return *std::next( this->begin(), index );
  }

  /**
   *  @brief Return a subrange of a given length from the data of the subrecord
   *
   *  @param[in] index    the index
   *  @param[in] length   the length of the subrange
   */
  auto values( std::size_t index, std::size_t length ) const {

    const auto left = this->iterator( index );
    const auto right = length > 0 ? this->iterator( index + length )
                                  : left;
    return njoy::tools::std20::ranges::subrange( left, right );
  }

public:

  /**
   *  @brief Return whether or not the subrecord is empty
   */
  bool empty() const { return this->begin_ == this->end_; }

  /**
   *  @brief Print the subrecord (if it is not empty)
   *
   *  Printing the data contained in the record is delegated to the
   *  derived class which knows how to format the data.
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    if ( ! this->empty() ) {

      static_cast< const Derived* >( this )->write( iter );
    }
  };
};

} // base namespace
} // NDItk namespace
} // njoy namespace

#endif
