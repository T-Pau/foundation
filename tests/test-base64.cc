#include <catch2/catch_test_macros.hpp>

#include "Base64.h"


TEST_CASE( "Base64 encoding and decoding", "[base64]" ) {
    tpau::cpp_kernal::Base64StringEncoder encoder;
    encoder.encode("Hello, World!");
    auto result = encoder.end();
    REQUIRE( result == "SGVsbG8sIFdvcmxkIQ==" );
}
