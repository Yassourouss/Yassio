#include "encryption.hpp"
#include <cctype>

std::string encrypt_word(const std::string& word, int shift) {
    std::string encrypted_word = word;
    for (char& c : encrypted_word) {
        if (std::isalpha(c)) {
            c = 'A' + (c - 'A' + shift) % 26;
        }
    }
    return encrypted_word;
}
