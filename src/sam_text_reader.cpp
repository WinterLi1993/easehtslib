//
// Created by zp on 8/24/16.
//

#include "sam_text_reader.h"
#include "sam_text_header_codec.h"

namespace ncic {

namespace easehts {

void SAMTextReader::ReadHeader() {
  SAMTextHeaderCodec codec;
  file_header_ = codec.Parse(fp_);
}

} // easehts
} // ncic
