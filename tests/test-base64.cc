#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include "Base64.h"


TEST_CASE("Base64StringEncoder", "[base64]") {
    tpau::cpp_kernal::Base64StringEncoder encoder;
    encoder.encode("Hello, World!");
    auto result = encoder.end();
    REQUIRE(result == "SGVsbG8sIFdvcmxkIQ==");
}

TEST_CASE("Base64StreamEncoder", "[base64]") {
    std::stringstream output;
    tpau::cpp_kernal::Base64StreamEncoder encoder(output);
    encoder.encode("Hello, World!");
    encoder.end();
    REQUIRE(output.str() == "SGVsbG8sIFdvcmxkIQ==");
}

TEST_CASE("Base64StreamEncoder with line breaks and indent", "[base64]") {
    std::stringstream output;
    tpau::cpp_kernal::Base64StreamEncoder encoder(output, 4, 2);
    encoder.encode("Hello, World!");
    encoder.end();
    REQUIRE(output.str() == "SGVs\n  bG8s\n  IFdv\n  cmxk\n  IQ==");
}

TEST_CASE("Base64Decoder", "[base64]") {
    tpau::cpp_kernal::Base64Decoder decoder;
    decoder.decode("SGVsbG8sIFdvcmxkIQ==");
    auto result = decoder.end();
    REQUIRE(result == "Hello, World!");
}

TEST_CASE("Base64Decoder with whitespace", "[base64]") {
    tpau::cpp_kernal::Base64Decoder decoder;
    decoder.decode("SGVs\n  bG8s\n  IFdv\n  cmxk\n  IQ==");
    auto result = decoder.end();
    REQUIRE(result == "Hello, World!");
}

TEST_CASE("Base64Decoder with garbage after end marker", "[base64]") {
    tpau::cpp_kernal::Base64Decoder decoder;
    REQUIRE_THROWS_WITH(decoder.decode("SGVsbG8sIFdvcmxkIQ==garbage"), "garbage after end marker in base64 data");
}

TEST_CASE("Base64Decoder with unexpected end marker", "[base64]") {
    tpau::cpp_kernal::Base64Decoder decoder;
    REQUIRE_THROWS(decoder.decode("SGVsbG8sIFdvcmxkIQ==="), "unexpected end marker in base64 data");
}

TEST_CASE("Base64Decoder with illegal characters", "[base64]") {
    tpau::cpp_kernal::Base64Decoder decoder;
    REQUIRE_THROWS(decoder.decode("SGVsbG8$sIFdvcmxkI=="), "invalid character in base64 data");
}
