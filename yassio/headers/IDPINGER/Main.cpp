#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "hash.hpp"
#include "encryption.hpp"

int main() {
    std::vector<std::string> word_list = { "Apple","Banana","Orange","Mango","Pineapple","Grape","Kiwi","Peach","Plum","Cherry","Strawberry","Raspberry","Blueberry","Blackberry","Watermelon","Cantaloupe","Honeydew","Coconut","Papaya","Guava","Apricot","Fig","Pear","Lemon","Lime","Grapefruit","Avocado","Pomegranate","Lychee","Passionfruit","Dragonfruit","Jackfruit","Rambutan","Durian","Persimmon","Kumquat","Tangerine","Cranberry","Clementine","Nectarine","Tamarillo","Quince","Ugli fruit","Ackee","Bilberry","Feijoa","Gac","Loquat","Pawpaw","Pineberry","Salak","Yangmei","Acai","Camu camu","Noni","Plantain","Prickly pear","Tamarind","Yuzu","Barberry","Blackcurrant","Boysenberry","Cloudberry","Goji berry","Huckleberry","Juniper berry","Loganberry","Salmonberry","Seaberry","Sloe","Bearberry","Bilberry","Cowberry","Crowberry","Elderberry","Garden huckleberry","Gooseberry","Jostaberry","Mulberry","Redcurrant","White currant","Raspberry","Salal berry","Sea grape","Sunberry","Acerola","Bacupari","Black sapote","Burahem","Canistel","Cupuaçu","Duku","Jabuticaba","Langsat","Mamey sapote","Mangaba","Mangosteen","Mombin","Sapodilla","Soursop","Star apple","Surinam cherry","Umbu","Wood apple" };

    SYSTEMTIME time;
    GetLocalTime(&time);

    int hour = time.wHour;
    int minute = time.wMinute;

    unsigned int secure_index = custom_hash(hour, minute) % 100;
    std::cout << "Secure Index: " << secure_index << std::endl;



    std::string selected_word_proxy = word_list[secure_index];
    std::string selected_word_provider = word_list[secure_index];



    std::string encrypted_word_provider = encrypt_word(selected_word_provider, -3);

    std::cout << "Encrypted word sent to proxy: " << encrypted_word_provider << std::endl;

    int determined_shift = -1;
    for (int i = -25; i <= 25; ++i) {
        std::string encrypted_word_proxy = encrypt_word(selected_word_proxy, i);
        if (encrypted_word_proxy == encrypted_word_provider) {
            determined_shift = i;
            break;
        }
    }

    std::cout << "Determined shift value: ";
    if (determined_shift >= -25 && determined_shift <= 25) {
        std::cout << "Proxy successfully determined the shift value: " << determined_shift << std::endl;
    }
    else {
        std::cout << "Proxy failed to determine the shift value.";
    }
    std::cout << std::endl;


    return 0;
}