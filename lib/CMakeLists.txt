add_library(foundation STATIC
        Base64.cc
        Commandline.cc
        Command.cc
        DiagnosticOutput.cc
        Exception.cc
        FileReader.cc
        FileSource.cc
        Location.cc
        Path.cc
        Symbol.cc
        Util.cc
)

target_include_directories(foundation PRIVATE ${PROJECT_BINARY_DIR})

