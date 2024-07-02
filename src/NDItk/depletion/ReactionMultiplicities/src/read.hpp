  /**
   *  @brief Read the record data
   *
 *  @param[in,out] iter        an iterator to the current position in the input
 *  @param[in,out] end         an iterator to the end of the input
 *  @param[in,out] reactions   the number of reactions
   */
  template< typename Iterator >
  void read( Iterator& iter, const Iterator& end, std::size_t reactions ) {

    // read in the data
    this->reactions_ = reactions;
    std::vector< int > data;
    while ( reactions-- ) {

      data.push_back( njoy::tools::disco::FreeFormatInteger::read< int >( iter, end ) );
      data.push_back( njoy::tools::disco::FreeFormatInteger::read< int >( iter, end ) );
      int number = data.back();
      if ( number < 0 ) {

        Log::error( "The number of reaction products cannot be less than zero" );
        Log::info( "Found {} as the number of reaction products", data[1] );
        throw std::exception();
      }
      else {

        number *= 2;
        while ( number-- ) {

          data.push_back( njoy::tools::disco::FreeFormatInteger::read< int >( iter, end ) );
        }
      }
    }
    this->data() = data;
    this->generateBlocks();

    // verify
    verify( this->reactions() );
  };
