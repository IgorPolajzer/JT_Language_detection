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
        CROATIAN,
        SLOVENIAN,
        UNKNOWN
    };

    static std::string toString(Value v) {
        switch (v) {
            case ENGLISH:  return "English";
            case SPANISH:  return "Spanish";
            case GERMAN:   return "German";
            case CROATIAN: return "Croatian";
            case SLOVENIAN: return "Slovenian";
            case UNKNOWN: return "Unknown";
        }
    }

    static Value fromProfile(const std::string& s) {
        if (s == "en_profile.txt")  return ENGLISH;
        if (s == "es_profile.txt")  return SPANISH;
        if (s == "ge_profile.txt")   return GERMAN;
        if (s == "hr_profile.txt") return CROATIAN;
        if (s == "si_profile.txt") return SLOVENIAN;
        return UNKNOWN;
    }
};


#endif //RV1_LANGUAGE_H