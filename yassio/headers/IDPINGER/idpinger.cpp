#include <iostream>
#include "hash.cpp"
#include "encryption.cpp"
#include <vector>
#include <ctime>
#include <random>

std::vector<std::string> word_list = {"Apple","Banana","Orange","Mango","Pineapple","Grape","Kiwi","Peach","Plum","Cherry","Strawberry","Raspberry","Blueberry","Blackberry","Watermelon","Cantaloupe","Honeydew","Coconut","Papaya","Guava","Apricot","Fig","Pear","Lemon","Lime","Grapefruit","Avocado","Pomegranate","Lychee","Passionfruit","Dragonfruit","Jackfruit","Rambutan","Durian","Persimmon","Kumquat","Tangerine","Cranberry","Clementine","Nectarine","Tamarillo","Quince","Ugli fruit","Ackee","Bilberry","Feijoa","Gac","Loquat","Pawpaw","Pineberry","Salak","Yangmei","Acai","Camu camu","Noni","Plantain","Prickly pear","Tamarind","Yuzu","Barberry","Blackcurrant","Boysenberry","Cloudberry","Goji berry","Huckleberry","Juniper berry","Loganberry","Salmonberry","Seaberry","Sloe","Bearberry","Bilberry","Cowberry","Crowberry","Elderberry","Garden huckleberry","Gooseberry","Jostaberry","Mulberry","Redcurrant","White currant","Raspberry","Salal berry","Sea grape","Sunberry","Acerola","Bacupari","Black sapote","Burahem","Canistel","Cupua�u","Duku","Jabuticaba","Langsat","Mamey sapote","Mangaba","Mangosteen","Mombin","Sapodilla","Soursop","Star apple","Surinam cherry","Umbu","Wood apple" };

std::string selected_word()
{
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;
    int secure_index = custom_hash(hour, minute) % 100;
    //std::cout << "Secure Index: " << secure_index << std::endl;
    return word_list[secure_index];
}

int rand_key()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,25);
    int rand = dist(rng);
    //std::cout <<"The shift key is  : " << rand << std::endl;
    return rand;
}

int determine_shift(std::string word)
{       
        std::string mword = word;
        std::cout << mword << std::endl;
        int determined_shift = -1;
        std::string base_word = selected_word();
        for (int i = 1; i <= 25; ++i) {
            std::string encrypted_word_proxy = encrypt_word(base_word, i);
            if (encrypted_word_proxy == word) {
                determined_shift = i;
               // std::cout << "The word is : " << encrypted_word_proxy << std::endl;
               // std::cout <<"The shift was : " << i << std::endl;
                break;
            }
    }
    return determined_shift;
}

