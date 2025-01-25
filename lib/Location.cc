/*
Location.cc --

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

#include "Location.h"

Location::Location(const Location& start, const Location& end) : Location(start) { extend(end); }

void Location::extend(const Location& end) {
    if (empty()) {
        *this = end;
    }
    else if (file == end.file && line_number == end.line_number && end_column < end.end_column) {
        end_column = end.end_column;
    }
}


std::string Location::to_string() const {
    if (!file) {
        return "";
    }
    auto s = file.str();
    if (line_number) {
        s += ":" + std::to_string(*line_number);
        if (start_column) {
            s += "." + std::to_string(*start_column);
        }
    }
    return s;
}


bool Location::operator==(const Location& other) const {
    return file == other.file && line_number == other.line_number && start_column == other.start_column && end_column == other.end_column;
}

std::ostream& operator<<(std::ostream& stream, const Location& location) {
    stream << location.to_string();
    return stream;
}
