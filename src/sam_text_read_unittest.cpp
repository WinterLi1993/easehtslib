//
// Created by zp on 8/25/16.
//

#include "easehts.h"

#include <gtest/gtest.h>
#include <stdlib.h>

samFile* GetSamFile() {
  char filename[] = "/home/zp/work/rnaSeq/easehtslib/data/xx#rg.sam";
  samFile* in = sam_open(filename, "r");
  if (in == NULL) {
    fprintf(stderr, "Error opening \"%s\"\n", filename);
    exit(1);
  }
  return in;
}

ncic::easehts::SAMTextReader reader(GetSamFile());

TEST(SAMTextReaderTest, Header) {
  ncic::easehts::SAMFileHeaderPtr header = reader.GetFileHeader();
  EXPECT_EQ(header->GetSequenceDictionary()->Size(), 1);
  EXPECT_EQ(header->GetSequenceDictionary()->At(0).getSeqenceName(), "xx");
  EXPECT_EQ(header->GetSequenceDictionary()->At(0).getSequenceLength(), 20);
}