/**
 *  @brief Generate the subrecords for this record
 */
void generateBlocks() {

  if ( ! this->empty() ) {

    this->multiplicities_.clear();
    auto left = this->values().begin();
    for ( unsigned int index = 0; index < this->numberReactions(); ++index ) {

      auto number = *( left + 1 );
      const auto right = left + 2 + 2 * number;
      this->multiplicities_.emplace_back( left, right );
      left = right;
    }
  }
}
