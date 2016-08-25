//
// Created by zp on 8/24/16.
//

#include "sam_text_header_codec.h"

#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include <htslib/kseq.h>

namespace ncic {

namespace easehts {

std::map<std::string, HeaderRecordType> SAMTextHeaderCodec::ParsedHeaderLine::HEADER_TYPE_MAP =
    SAMTextHeaderCodec::ParsedHeaderLine::InitHeaderTypeMap();

const std::string SAMTextHeaderCodec::FIELD_SEPARATOR = "\t";
const std::string SAMTextHeaderCodec::TAG_KEY_VALUE_SEPARATOR = ":";

SAMFileHeaderPtr SAMTextHeaderCodec::Parse(htsFile *fp) {
  SAMFileHeaderPtr sam_header = boost::make_shared<SAMFileHeader>();
  std::string line;
  while (AdvanceLine(fp, &line)) {
    ParsedHeaderLine parsed_header_line(line);
    switch (parsed_header_line.GetHeaderRecordType()) {
      case SQ:
        ParseSQLine(sam_header, &parsed_header_line);
        break;
      default:
        // TODO other header current no need, you can add the parser if need the header info
        break;
    }
  }
}

/**
  * parse SQ line
  */
void SAMTextHeaderCodec::ParseSQLine(const SAMFileHeaderPtr& sam_header,
                                     ParsedHeaderLine *parsed_header_line) {
  CHECK(parsed_header_line->GetHeaderRecordType() == SQ);

  // the line should has SN field
  LOG_IF(ERROR, !parsed_header_line->HasKey("SN") ||
      !parsed_header_line->HasKey("LN")) << "SQ line don't have SN or LN attribute";

  const std::string& seq_name = parsed_header_line->GetValue("SN");
  const std::string& len_str = parsed_header_line->GetValue("LN");
  // remove the attributes
  parsed_header_line->RemoveKey("SN");
  parsed_header_line->RemoveKey("LN");


  int len = 0;
  try {
    len = boost::lexical_cast<int>(len_str);
  } catch (boost::bad_lexical_cast) {
    LOG(ERROR) << "LN field is not a valid int number" << len_str;
  }
  sam_header->GetSequenceDictionary()->AddSequenceRecord(SAMSequenceRecord(seq_name, len));

  sam_header->AddAttributes(parsed_header_line->GetKeyValuePairs());
}

/** read next header line, if has next, return true and set to line,
   * otherwise return false
   *
   * @param
   *    fp: the sam file
   *    line: the header line
   *
   *  @return
   *     true if has next header line
   */
bool SAMTextHeaderCodec::AdvanceLine(htsFile *fp, std::string* line) {
  while (hts_getline(fp, KS_SEP_LINE, &fp->line) >= 0) {
    if (fp->line.s[0] != HEADER_LINE_START) {
      return false;
    }

    *line = std::string(fp->line.s, fp->line.l);
    return true;
  }
}

SAMTextHeaderCodec::ParsedHeaderLine::ParsedHeaderLine(const std::string &line) {
  std::vector<std::string> fields;

  boost::split(fields, line, boost::is_any_of(FIELD_SEPARATOR));
  CHECK_GT(fields.size(), 1);

  ParseHeaderType(fields[0]);

  for (size_t idx = 1; idx < fields.size(); ++idx) {
    std::vector<std::string> pair;
    boost::split(pair, fields[idx], boost::is_any_of(TAG_KEY_VALUE_SEPARATOR));

    CHECK_LT(pair.size(), 2) << "Bad header format";

    // FIXME here if the filed has more than one TAG_KEY_VALUE_SEPARATOR_CHA such as k:v1:v2, we just store k->v1
    key_value_pairs_[fields[0]] = fields[1];
  }
}

/**
 * parse the header type of the line
 */
void SAMTextHeaderCodec::ParsedHeaderLine::ParseHeaderType(const std::string& type) {
  assert(type[0] == HEADER_LINE_START);

  if (HEADER_TYPE_MAP.find(type) != HEADER_TYPE_MAP.end()) {
    header_type_ = HEADER_TYPE_MAP[type];
  } else {
    header_type_ = NUL;
  }
}

} // easehts
} // ncic