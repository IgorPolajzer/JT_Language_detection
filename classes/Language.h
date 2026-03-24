//
// Created by igork on 24/03/2026.
//

#ifndef RV1_LANGUAGE_H
#define RV1_LANGUAGE_H


struct Language {
    enum Value {
        ENGLISH,
        SPANISH,
        GERMAN,
        ITALIAN,
        SLOVENIAN,
        UNKNOWN
    };

    static std::string toString(Value v) {
        switch (v) {
            case ENGLISH:  return "English";
            case SPANISH:  return "Spanish";
            case GERMAN:   return "German";
            case ITALIAN: return "Italian";
            case SLOVENIAN: return "Slovenian";
            case UNKNOWN: return "Unknown";
        }
    }

    static Value fromProfile(const std::string& s) {
        if (s == "en_profile.txt")  return ENGLISH;
        if (s == "es_profile.txt")  return SPANISH;
        if (s == "ge_profile.txt")   return GERMAN;
        if (s == "it_profile.txt") return ITALIAN;
        if (s == "si_profile.txt") return SLOVENIAN;
        return UNKNOWN;
    }
};


#endif //RV1_LANGUAGE_H