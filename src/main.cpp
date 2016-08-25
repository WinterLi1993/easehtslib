#include <iostream>

#include "htslib/sam.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "glog/logging.h"

#include "easehts.h"

using namespace std;

int sam_read() {
    char filename[] = "/home/zp/work/rnaSeq/easehtslib/data/xx#rg.sam";
    samFile *in = sam_open(filename, "r");
    if (in == NULL) {
        fprintf(stderr, "Error opening \"%s\"\n", filename);
        return EXIT_FAILURE;
    }

    ncic::easehts::SAMTextReader reader(in);
    ncic::easehts::SAMFileHeaderPtr header = reader.GetFileHeader();

    const std::string name = header->GetSequenceDictionary()->GetSequence("XX").getSeqenceName();
    cout << name;
}

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    cout << "shit" << endl;
    sam_read();
    google::ShutdownGoogleLogging();
    return 0;
}