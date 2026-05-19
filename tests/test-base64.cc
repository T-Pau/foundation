#include <catch2/catch_test_macros.hpp>

#include "Base64.h"


TEST_CASE( "Base64 encoding and decoding", "[base64]" ) {
    Base64Encoder encoder;
    encoder.encode("Hello, World!");
    encoder.finish();
    REQUIRE( encoder.str() == "SGVsbG8sIFdvcmxkIQ==" );
}
