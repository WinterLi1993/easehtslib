//
// Created by zp on 8/24/16.
//

#ifndef EASEHTSLIB_SAM_SEQUENCE_DICTIONARY_H
#define EASEHTSLIB_SAM_SEQUENCE_DICTIONARY_H

#include "sam_seqence_record.h"

#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <glog/logging.h>

namespace ncic {

namespace easehts {

/**
 * Collection of SAMSequenceRecords.
 */
class SAMSequenceDictionary {

 public:
  void AddSequenceRecord(const SAMSequenceRecord& sequence_record) {
    sequences_.push_back(sequence_record);
    sequences_map_[sequence_record.getSeqenceName()] = sequences_.size() - 1;
  }

  // XXX you should first decide if hasSequence
  SAMSequenceRecord& GetSequence(const std::string& name) {
    CHECK(HasSequence(name));

    return sequences_[sequences_map_[name]];
  }

  bool HasSequence(const std::string& name) const {
    if (sequences_map_.find(name) != sequences_map_.end()) {
      return true;
    }

    return false;
  }

 private:
  std::vector<SAMSequenceRecord> sequences_;
  // sequence name -> SAMSequenceRecord index
  std::map<std::string, int> sequences_map_;
};

typedef boost::shared_ptr<SAMSequenceDictionary> SAMSequenceDictionaryPtr;

} // easehts
} // ncic

#endif //EASEHTSLIB_SAM_SEQUENCE_DICTIONARY_H
