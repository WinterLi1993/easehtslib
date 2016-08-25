//
// Created by zp on 8/24/16.
//

#ifndef EASEHTSLIB_SAM_FILE_HEADER_H
#define EASEHTSLIB_SAM_FILE_HEADER_H

#include "sam_sequence_dictionary.h"

#include <vector>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>

namespace ncic {

namespace easehts {

/**
 * Header information from a SAM or BAM file.
 */
class SAMFileHeader {
 public:
  void SetSequenceDictionary(SAMSequenceDictionaryPtr& sequence_dictionary) {
    sequence_dictionary_ = sequence_dictionary;
  }

  const SAMSequenceDictionaryPtr& GetSequenceDictionary() const {
    return sequence_dictionary_;
  }

  void AddAttributes(const std::map<std::string, std::string> attributes) {
    attributes_.insert(attributes.begin(), attributes.end());
  }

 private:
  SAMSequenceDictionaryPtr sequence_dictionary_;
  std::map<std::string, std::string> attributes_;
};

typedef boost::shared_ptr<SAMFileHeader> SAMFileHeaderPtr;

} // easehts
} // ncic

#endif //EASEHTSLIB_SAM_FILE_HEADER_H
