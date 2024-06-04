#ifndef NJOY_NDITK_PYTHON_READ
#define NJOY_NDITK_PYTHON_READ

// system includes
#include <string>

// other includes
#include "tools/Log.hpp"
#include "tools/disco/FreeFormatCharacter.hpp"

/**
 *  @brief Read a record from a string (no subtype record)
 *
 *  @param[in] string   the string to read from
 */
template < typename Record, typename... Arguments >
Record read( const std::string& string, Arguments... arguments ) {

  using namespace njoy::tools;
  using namespace njoy::NDItk;

  Record record;
  auto iter = string.begin();
  auto end = string.end();

  base::Keyword key( disco::FreeFormatCharacter::read< std::string >( iter, end ) );
  if ( record.keyword() == key.keyword() ) {

    record.read( iter, end, arguments... );

    //! @todo verify the string is now empty
    return record;
  }
  else {

    Log::error( "The record keyword is not the one expected" );
    Log::info( "Expected: \'{}\'", record.keyword() );
    Log::info( "Found: \'{}\'", key.keyword() );
    throw std::exception();
  }
}

/**
 *  @brief Read a record from a string (particle subtype record)
 *
 *  @param[in] string   the string to read from
 */
template < typename Record, typename... Arguments >
Record readWithParticleSubtype( const std::string& string, Arguments... arguments ) {

  using namespace njoy::tools;
  using namespace njoy::NDItk;

  Record record;
  auto iter = string.begin();
  auto end = string.end();

  base::Keyword key( disco::FreeFormatCharacter::read< std::string >( iter, end ) );
  if ( key.particle().has_value() ) {

    record = Record( key.particle().value() );
  }
  if ( key.keyword() == record.keyword() ) {

    record.read( iter, end, arguments... );

    //! @todo verify the string is now empty
    return record;
  }
  else {

    Log::error( "The record keyword is not the one expected" );
    Log::info( "Expected: \'{}\'", record.keyword() );
    Log::info( "Found: \'{}\'", key.keyword() );
    throw std::exception();
  }
}

/**
 *  @brief Read a record from a string (multiplicity subtype record)
 *
 *  @param[in] string   the string to read from
 */
template < typename Record, typename... Arguments >
Record readWithMultiplicitySubtype( const std::string& string, Arguments... arguments ) {

  using namespace njoy::tools;
  using namespace njoy::NDItk;

  Record record;
  auto iter = string.begin();
  auto end = string.end();

  base::Keyword key( disco::FreeFormatCharacter::read< std::string >( iter, end ) );
  if ( key.multiplicityType().has_value() ) {

    record = Record( key.multiplicityType().value() );
  }
  if ( key.keyword() == record.keyword() ) {

    record.read( iter, end, arguments... );

    //! @todo verify the string is now empty
    return record;
  }
  else {

    Log::error( "The record keyword is not the one expected" );
    Log::info( "Expected: \'{}\'", record.keyword() );
    Log::info( "Found: \'{}\'", key.keyword() );
    throw std::exception();
  }
}

/**
 *  @brief Read a record from a string (fission subtype record)
 *
 *  @param[in] string   the string to read from
 */
template < typename Record, typename... Arguments >
Record readWithFissionSubtype( const std::string& string, Arguments... arguments ) {

  using namespace njoy::tools;
  using namespace njoy::NDItk;

  Record record;
  auto iter = string.begin();
  auto end = string.end();

  base::Keyword key( disco::FreeFormatCharacter::read< std::string >( iter, end ) );
  if ( key.fissionType().has_value() ) {

    record = Record( key.fissionType().value() );
  }
  if ( key.keyword() == record.keyword() ) {

    record.read( iter, end, arguments... );

    //! @todo verify the string is now empty
    return record;
  }
  else {

    Log::error( "The record keyword is not the one expected" );
    Log::info( "Expected: \'{}\'", record.keyword() );
    Log::info( "Found: \'{}\'", key.keyword() );
    throw std::exception();
  }
}

#endif
