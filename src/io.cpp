//
// Created by bczhc on 8/21/21.
//

#include "io.h"
#include "string"

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
