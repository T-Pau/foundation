/*
FileSource.cc --

Copyright (C) Dieter Baron

The authors can be contacted at <accelerate@tpau.group>

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. The names of the authors may not be used to endorse or promote
  products derived from this software without specific prior
  written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "FileSource.h"

#include "Exception.h"
#include "FileReader.h"

 FileSource::FileSource(Symbol filename): filename_(filename), lines(FileReader::global.read(filename)) {
 }


void FileSource::expand_location(Location& location) const {
    if (location.file == filename() && location.line_number == line) {
        location.end_column = column;
    }
}

int FileSource::get() {
    if (line >= lines.size()) {
        line = lines.size() + 1;
        return EOF;
    }

    if (column >= lines[line].size()) {
        line += 1;
        column = 0;
        return '\n';
    }

    auto c = lines[line][column];
    column += 1;
    return c;
}

void FileSource::reset_to(const Location& new_location) {
    if (new_location.file != filename()) {
        throw Exception("Can't reset to location in different file.");
    }
    line = new_location.line_number.value_or(1) - 1;
    column = new_location.start_column.value_or(0);
}


void FileSource::unget() {
    if (column == 0) {
        if (line > 0) {
            line -= 1;
            if (line < lines.size()) {
                column = lines[line].size();
            }
        }
        else {
            throw Exception("Can't unget at beginning of file.");
        }
    }
    else {
        column -= 1;
    }
}
