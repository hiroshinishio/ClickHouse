#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <openssl/ripemd.h>

std::string RIPEMD160(const std::string &input) {
    unsigned char hash[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160_CTX ctx;
    RIPEMD160_Init(&ctx);
    RIPEMD160_Update(&ctx, input.c_str(), input.size());
    RIPEMD160_Final(hash, &ctx);

    std::stringstream ss;
    for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int main() {
    std::string input = "Hello, World!";
    std::string output = RIPEMD160(input);
    std::cout << "RIPEMD160(\"" << input << "\") = " << output << std::endl;
    return 0;
}

// Unit test
void test_ripemd160() {
    std::vector<std::pair<std::string, std::string>> test_cases = {
        {"", "9c1185a5c5e9fc54612808977ee8f548b2258d31"},
        {"a", "0bdc9d2d256b3ee9daae347be6f4dc835a467ffe"},
        {"abc", "8eb208f7e05d987a9b04b1a3e8a2e3f1f7c4e3d8"},
        {"message digest", "5d0689ef49d2fae572b881b123a85ffa21595f36"},
        {"abcdefghijklmnopqrstuvwxyz", "f71c27109c692c1b56bbdceb5b9d2865b3708dbc"},
        {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", "12a053384a9c0c88e405a06c27dcf49ada62eb2b"},
        {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", "b0e20b6e3116640286ed3a87a5713079b21f5189"},
        {"12345678901234567890123456789012345678901234567890123456789012345678901234567890", "9b752e45573d4b39f4dbd3323cab82bf63326bfb"}
    };

    for (const auto &test_case : test_cases) {
        std::string result = RIPEMD160(test_case.first);
        if (result != test_case.second) {
            std::cerr << "Test failed for input: " << test_case.first << std::endl;
            std::cerr << "Expected: " << test_case.second << ", Got: " << result << std::endl;
        }
    }
}