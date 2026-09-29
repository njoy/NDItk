#ifndef NJOY_NDITK_COMMENTBLOCK
#define NJOY_NDITK_COMMENTBLOCK

// system includes
#include <string>
#include <sstream>
#include <iomanip>

// other includes
#include "NDItk/base/Record.hpp"
#include "tools/disco/FreeFormatCharacter.hpp"

namespace njoy {
namespace NDItk {

/**
 *  @brief An NDI record containing a block of comments
 */
class CommentBlock : protected base::Record {

protected:

  std::string comment_;

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   */
  CommentBlock() :
      base::Record( base::Keyword( "comment" ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] keyword   the keyword of the record
   *  @param[in] value     the string content of the record
   */
  CommentBlock( std::string value ) :
      base::Record( base::Keyword( "comment" ) ),
      comment_(value) {}

  /* methods */

  using base::Record::keyword;

  /**
   *  @brief Read the record data
   *
   *  @param[in] iter   the current position in the input
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end ) {

    // read until start of first table as signified by the 'zaid' keyword
    Iterator start = iter;

    std::string endCommentKeyword = "end_comment";

    std::string keyword;
    while ( ( keyword != endCommentKeyword ) and ( iter != end ) ) {

      keyword = njoy::tools::disco::FreeFormatCharacter::read< std::string >( iter, end );
    }

    Iterator stop = iter;

    // 'undo' the last word ("end_comment") read by disco
    stop = std::prev( stop, endCommentKeyword.length() );

    this->comment_ = std::string( start, stop );
  }

  /**
   *  @brief  Print the record data
   *
   *  @param[in] iter   the current position in the output
   */
  template< typename OutputIterator >
  void print( OutputIterator& iter ) const {

    std::ostringstream buffer;
    buffer << this->keyword() << "\n" << this->comment_ << "end_comment\n";

    for ( auto c : buffer.str() ) { *iter++ = c; }
  }

  /**
   *  @brief  Return the string content of the comment block
   */
  const std::string& comment() const { return this->comment_; }
};

} // NDItk namespace
} // njoy namespace

#endif
