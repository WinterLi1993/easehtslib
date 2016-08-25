//
// Created by zp on 8/24/16.
//

#ifndef EASEHTSLIB_READER_H
#define EASEHTSLIB_READER_H

#include "utils.h"

#include <string>

namespace ncic {

namespace easehts {

// The base class of sam/bam file
class SamReader {
 public:
 private:
};

typedef struct FileType {
  std::string name; // typename such as SAM
  std::string file_extension; // file extension .sam
  std::string index_extension; // index extension .bai

  const static FileType SRA_TYPE;
  const static FileType CRAM_TYPE;
  const static FileType BAM_TYPE;
  const static FileType SAM_TYPE;

} FileType;

} // easehts
} // ncic

#endif //EASEHTSLIB_READER_H
