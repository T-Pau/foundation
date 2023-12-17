/*
Command.cc -- 

Copyright (C) Dieter Baron

The authors can be contacted at <assembler@tpau.group>

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

#include "Command.h"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

#include "config.h"

#include "Exception.h"

std::string Command::header = " -- " PACKAGE " by " PACKAGE_AUTHOR;
std::string Command::footer = "Report bugs to " PACKAGE_BUGREPORT ".";
std::string Command::version = VERSION;

Command::Command(const std::vector<Commandline::Option>& options, std::string arguments, const std::string& name): commandline(options, std::move(arguments), name + header, footer, version) {
}


int Command::run(int argc, char *const *argv) {
    try {
        program_name = argv[0];
        arguments = commandline.parse(argc, argv);

        if (arguments.arguments.size() < minimum_arguments() || arguments.arguments.size() > maximum_arguments()) {
            commandline.usage(false, stderr);
            throw Exception();
        }

        process();
        create_output();
    }
    catch (std::exception& ex) {
        if (strlen(ex.what()) > 0) {
            std::cerr << program_name << ": " << ex.what() << std::endl;
        }
        return 1;
    }

    return 0;
}
