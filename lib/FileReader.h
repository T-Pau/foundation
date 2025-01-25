/*
FileReader.h -- Read File into Array of Lines

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

#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Symbol.h"

class FileReader {
public:
    const std::vector<std::string>& read(Symbol file_name, bool optional = false);
    [[nodiscard]] std::string read_binary(Symbol file_name, bool optional = false);

    [[nodiscard]] const std::string& get_line(Symbol file, size_t line_number) const;
    [[nodiscard]] std::vector<Symbol> file_names() const;

    static FileReader global;

private:
    static std::vector<std::string> empty_file;

    std::unordered_set<Symbol> binary_files;
    std::unordered_map<Symbol,std::vector<std::string>> files;
};


#endif // FILEREADER_H
