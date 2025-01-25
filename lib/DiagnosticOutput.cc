/*
DiagnosticOutput.cc --

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

#include "DiagnosticOutput.h"

#include "FileReader.h"

DiagnosticOutput DiagnosticOutput::global;

const char* DiagnosticOutput::diagnostics_severity_name(Severity severity) {
    switch (severity) {
        case NOTICE:
            return "notice";

        case WARNING:
            return "warning";

        case ERROR:
            return "error";
    }

    throw Exception("invalid severity");
}

DiagnosticOutput::Stream DiagnosticOutput::output(Symbol category, Severity severity, const Location& location) {
    auto output = begin_message(category, severity, location);
    return { *this, location, diagnostics_file, output };
}

void DiagnosticOutput::output(Symbol category, Severity severity, const Location& location, const std::string& message) {
    if (begin_message(category, severity, location)) {
        diagnostics_file << message << std::endl;
        end_message(location);
    }
}

bool DiagnosticOutput::begin_message(Symbol category, Severity severity, const Location& location) {
    if (ignored_categories.contains(category)) {
        return false;
    }
    if (severity >= fail_serverity) {
        fail_flag = true;
    }
    if (!location.empty()) {
        diagnostics_file << location << ": ";
    }
    diagnostics_file << diagnostics_severity_name(severity) << ": ";

    return true;
}

void DiagnosticOutput::end_message(const Location& location) const {
    if (location.empty() && !location.line_number) {
        return;
    }

    try {
        const auto& line = FileReader::global.get_line(location.file, *location.line_number);
        diagnostics_file << line << std::endl;

        if (location.start_column) {
            auto width = size_t{1};
            if (location.end_column && location.end_column > location.start_column) {
                width = *location.end_column - *location.start_column;
            }

            size_t position = 0;
            for (size_t i = 0; i < location.start_column; i++) {
                diagnostics_file << ' ';
                position += 1;
                if (line[i] == '\t') {
                    while (position % 8 != 0) {
                        diagnostics_file << ' ';
                        position += 1;
                    }
                }
            }
            for (size_t i = 0; i < width; i++) {
                diagnostics_file << '^';
                position += 1;
                if (line[i] == '\t') {
                    while (position % 8 != 0) {
                        diagnostics_file << '^';
                        position += 1;
                    }
                }
            }
            diagnostics_file << std::endl;
        }
    } catch (...) {
    }
}

DiagnosticOutput::Stream::~Stream() {
    *this << std::endl;
    diagnostic_output.end_message(location);
}
