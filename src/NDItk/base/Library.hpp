#ifndef NJOY_NDITK_BASE_LIBRARY
#define NJOY_NDITK_BASE_LIBRARY

// system includes
#include <string>
#include <vector>

// other includes
#include "tools/disco/FreeFormatCharacter.hpp"

namespace njoy {
namespace NDItk {
namespace base {

/**
 *  @brief A Library class that holds one or more NDI tables
 */
template< typename Table >
class Library {

protected:

  /* fields */

  std::string header_;

  std::vector<Table> tables_;

public:

  // Default constructor
  Library() = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] tables  a vector of NDI tables
   */
  Library( std::string header, std::vector<Table> tables ) :
    header_( std::move(header) ), tables_( std::move( tables ) ) {}

  /**
   *  @brief Return the number of data tables in the library
   */
  auto numberTables() const { return this->tables_.size(); };

  /**
   *  @brief Return the header in the library
   */
  const std::string& header() const { return this->header_; };

  /**
   *  @brief Return the vector of tables in the library
   */
  const std::vector<Table>& tables() const { return this->tables_; };

  /**
   *  @brief Return the table in the library with the associated index
   *
   *  @param[in] index  the 0-based index of the table in the library file
   */
  const Table& getTable( int index ) const { return this->tables()[index]; };

  /**
   *  @brief Return the table in the library with the associated zaid
   *
   *  @param[in] zaid  the zaid string of the table in the library file
   */
  const Table&  getTable( const std::string& zaid ) const {

    auto pos = std::find_if( this->tables().begin(),
                             this->tables().end(),
                             [&zaid] ( const Table& table ) {

                               return table.metadata().zaid() == zaid;
                             } );
    if ( pos != this->tables().end() ) {

        return *pos;
    }
    Log::error( "The requested zaid \'{}\' has no associated record", zaid );
    throw std::exception();
  }

  /**
   *  @brief Check if there is a table in the library with the associated zaid
   *
   *  @param[in] zaid  the zaid string of the table in the library file
   */
  bool hasTable( const std::string& zaid ) const {

    auto pos = std::find_if( this->tables().begin(),
                             this->tables().end(),
                             [&zaid] ( const Table& table ) {

                               return table.metadata().zaid() == zaid;
                             } );
    if ( pos != this->tables().end() ) {

        return true;
    }
    return false;
  }

  /**
   *  @brief Read the header (if present) and all tables in the library
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    // read until start of first table as signified by the 'zaid' keyword
    Iterator headerStart = iter;

    std::string tableStartKeyword = "zaid";

    std::string keyword;
    while ( ( keyword != tableStartKeyword ) and ( iter != end ) ) {

      keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );
    }

    // 'undo' the last word ("zaid") read by disco
    iter = std::prev( iter, tableStartKeyword.length() );

    // store all of the content before tables in a header string
    this->header_ = std::string( headerStart, iter );
    this->header_.pop_back(); // header picks up an extra newline somehow? --> get rid of it

    // read the tables until the end
    while( iter != end ) {

      Table table;
      table.read( iter, end );

      this->tables_.push_back( table );
    }
  }

  /**
  *   @brief Print the header and each table in the library
  *
  *   @param[in] iter     the current position in the output
  */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    std::ostringstream buffer;

    buffer << this->header();

    for (const auto& entry : this->tables() ) {

      std::string tmp;
      auto tmp_output = std::back_inserter(tmp);
      entry.print( tmp_output );
      buffer << "\n" << tmp;
    }

    for ( auto c : buffer.str() ) { *iter++ = c; }
  }
};

} // namespace base
} // NDItk namespace
} // njoy namespace

#endif
