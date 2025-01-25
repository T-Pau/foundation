/*
Location.h -- Location within a File

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

#ifndef LOCATION_H
#define LOCATION_H

#include <optional>
#include <string>

#include "Symbol.h"

class Location {
  public:
    Location() = default;

    explicit Location(const std::string& file_name) : file(file_name) {}

    Location(Symbol file, std::optional<size_t> line_number, std::optional<size_t> start_column, std::optional<size_t> end_column) : file(file), line_number(line_number), start_column(start_column), end_column(end_column) {}

    Location(const Location& start, const Location& end);

    void extend(const Location& end);

    [[nodiscard]] bool empty() const { return file.empty(); }
    bool operator==(const Location &other) const;

    [[nodiscard]] std::string to_string() const;

    Symbol file;
    std::optional<size_t> line_number;
    std::optional<size_t> start_column;
    std::optional<size_t> end_column;
};

template <> struct std::hash<Location> {
    std::size_t operator()(const Location& location) const noexcept {
        return std::hash<Symbol>()(location.file) ^ (std::hash<size_t>()(location.line_number.value_or(0)) << 1) ^ (std::hash<size_t>()(location.start_column.value_or(0)) << 2) ^ (std::hash<size_t>()(location.end_column.value_or(0)) << 3);
    }
};

std::ostream& operator<<(std::ostream& stream, const Location& location);

#endif // LOCATION_H
