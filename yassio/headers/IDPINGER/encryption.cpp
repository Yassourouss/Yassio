#include "encryption.hpp"
#include <cctype>
#include <iostream>

std::string encrypt_word(const std::string& word, int shift) {
    std::string encrypted_word = word;
    for (char& c : encrypted_word) {
        if (std::isalpha(c)) {
            c = c + shift;
        }
    }
    return encrypted_word;
}

std::string decrypt_word(const std::string& word, int shift) {
    std::string encrypted_word = word;
    for (char& c : encrypted_word) {
        if (std::isalpha(c)) {
            c = c - shift;
    }
    }
    return encrypted_word;
}
