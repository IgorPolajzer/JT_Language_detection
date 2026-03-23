//
// Created by igork on 22/03/2026.
//

#ifndef RV1_TOKEN_H
#define RV1_TOKEN_H
#include <string>
#include <vector>


class Token {
    std::string value;
    std::vector<std::pair<int, std::string>> nGrams;
    
public:
    static constexpr int MAX_N_GRAM_LENGTH = 5;

    Token(const std::string &value) {
        this->value = value;
    }

    void setNgrams(std::vector<std::pair<int, std::string>> nGrams) {this->nGrams = nGrams;}

    std::string getValue() {return value;}
    std::vector<std::pair<int, std::string>> getNgrams() {return nGrams;}

    void createNgrams();
};


#endif //RV1_TOKEN_H