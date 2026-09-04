#include "hash.hpp"

unsigned int custom_hash(int hour, int minute) {
    unsigned int hash = hour;
    hash = (hash << 7) ^ minute;
    hash = (hash << 3) ^ (hash >> 11);
    return hash;
}
