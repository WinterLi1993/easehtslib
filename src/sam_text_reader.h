//
// Created by zp on 8/24/16.
//

#ifndef EASEHTSLIB_SAMREADER_H
#define EASEHTSLIB_SAMREADER_H

#include "reader.h"
#include "sam_sequence_dictionary.h"
#include "sam_file_header.h"

#include <string>
#include <map>
#include <htslib/sam.h>

namespace ncic {

namespace easehts {

class SAMTextReader {
 public:
  // Prepare to read a SAM text file.
  SAMTextReader(samFile* fp) : fp_(fp) {
    ReadHeader();
  }

  const SAMFileHeaderPtr& GetFileHeader() const {
    return file_header_;
  }

 private:
  void ReadHeader();
 private:
  SAMFileHeaderPtr file_header_;
  samFile *fp_;
};


} // easehts
} // ncic

#endif //EASEHTSLIB_SAMREADER_H
