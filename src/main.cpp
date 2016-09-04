#include <iostream>

#include "htslib/sam.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>

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

    ncic::easehts::SAMBAMNormalReader reader(in);


    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    cout << stoi("22");
    cout << "shit" << endl;
    sam_read();
    google::ShutdownGoogleLogging();

    return 0;
}