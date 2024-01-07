add_library(foundation STATIC
        Base64.cc
        Commandline.cc
        Command.cc
        Exception.cc
        Util.cc
)

target_include_directories(foundation PRIVATE ${PROJECT_BINARY_DIR})

