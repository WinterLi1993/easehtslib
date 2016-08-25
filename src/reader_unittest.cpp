//
// Created by zp on 8/24/16.
//

#include "sam_text_reader.h"

#include <gtest/gtest.h>

TEST(test_define, normal) {
  EXPECT_EQ(ncic::easehts::BAM_TYPE.name, "BAM");
}