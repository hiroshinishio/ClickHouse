#include <iostream>
#include <string>
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

// This is a basic implementation of the RIPEMD160 function using OpenSSL.
// It includes a simple main function to demonstrate its usage.
// The function takes a string input and returns the RIPEMD160 hash as a hex string.
// Note: Ensure OpenSSL is installed and linked correctly when compiling this code.