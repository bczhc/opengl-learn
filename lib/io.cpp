//
// Created by bczhc on 8/21/21.
//

#include "io.h"
#include "string"
#include "types.h"
#include "exception.h"

Option<std::string> readLine(FILE *fp) {
    bool eof = true;
    std::string line;
    char c;
    while (fread(&c, 1, 1, fp) != 0) {
        eof = false;
        if (c == '\n') {
            break;
        }
        line.push_back(c);
    }
    if (eof) return Option<std::string>::getNone();
    return Option(line);
}

std::string readFileToString(const char* path) {
    FILE *fp = fopen(path, "rb");
    if (fp == nullptr) {
        throw IOException("Cannot open file");
    }
    std::string read;
    u8 buf[4096];
    usize readLen;
    while ((readLen = fread(buf, 1, 4096, fp)) != 0) {
        read.append((const char *) buf, readLen);
    }
    fclose(fp);
    return read;
}
