/**
 *  @brief Generate the subrecords for this record
 */
void generateBlocks() {

  if ( ! this->empty() ) {

    this->moments_.clear();
    for ( unsigned int index = 0; index < this->numberLegendreMoments(); ++index ) {

      const auto size = 1 + this->numberPrimaryGroups() * this->numberOutgoingGroups();
      const auto left = this->values().begin() + index * size;
      const auto right = left + size;
      this->moments_.emplace_back( left, right,
                                   this->numberPrimaryGroups(),
                                   this->numberOutgoingGroups() );
    }
  }
}
