#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

string convertTextToSound(string text);

bool isEqual(string text1, string text2)
{
    string t1 = convertTextToSound(text1);
    string t2 = convertTextToSound(text2);
    return (t1 == t2);
}

string convertTextToSound(string text)
{
    if (text.empty()) {
        return "0000";
    }

    const string kHW = "hw";
    string text_without_hw = "";
    char first_letter = text[0];

    for (size_t i = 1; i < text.size(); i++) {
        if (kHW.find(tolower(text[i])) == string::npos) {
            text_without_hw += text[i];
        }
    }

    const string kVowels = "aeiouy";
    string text_hollow = "";

    for (size_t i = 0; i < text_without_hw.size(); i++) {
        if (kVowels.find(tolower(text_without_hw[i])) == string::npos) {
            text_hollow += text_without_hw[i];
        }
    }

    const string kLettersToOne = "bfpv";
    const string kLettersToTwo = "cgjkqsxz";
    const string kLettersToThree = "dt";
    const string kLettersToFour = "l";
    const string kLettersToFive = "mn";
    const string kLettersToSix = "r";
    string converted_text = "";

    for (size_t i = 0; i < text_hollow.size(); i++) {
        if (kLettersToOne.find(tolower(text_hollow[i])) != string::npos) {
            converted_text += "1";
        } else if (kLettersToTwo.find(tolower(text_hollow[i])) != string::npos) {
            converted_text += "2";
        } else if (kLettersToThree.find(tolower(text_hollow[i])) != string::npos) {
            converted_text += "3";
        } else if (kLettersToFour.find(tolower(text_hollow[i])) != string::npos) {
            converted_text += "4";
        } else if (kLettersToFive.find(tolower(text_hollow[i])) != string::npos) {
            converted_text += "5";
        } else if (kLettersToSix.find(tolower(text_hollow[i])) != string::npos) {
            converted_text += "6";
        }
    }

    string unique_symbols = "";

    if (!converted_text.empty()) {
        char first_occurence = converted_text[0];
        unique_symbols += first_occurence;
        for (size_t i = 0; i < converted_text.size(); i++) {
            if (converted_text[i] != first_occurence) {
                first_occurence = converted_text[i];
                unique_symbols += first_occurence;
            }
        }
    }

    unique_symbols.insert(0, 1, toupper(first_letter));

    if (unique_symbols.length() < 4) {
        unique_symbols += string(4 - unique_symbols.length(), '0');
    } else {
        unique_symbols = unique_symbols.substr(0, 4);
    }

    return unique_symbols;
}

int main()
{
    string text1{"Ashcraft"};
    string text2{"Asccroft"};
    assert (isEqual(text1, text2));
    assert (convertTextToSound("Aschcraft") == string{"A261"});
    assert (isEqual("Brwn", "Brown"));
    assert (isEqual("Claire", "Clare"));
    assert (convertTextToSound("Claire") == string{"C460"});
    assert (convertTextToSound("Fa") == string{"F000"});
    assert(convertTextToSound("Bfpv") == string{"B100"});
    assert(convertTextToSound("Cgjk") == string{"C200"});
    assert(convertTextToSound("Cdt") == string{"C300"});
    assert(convertTextToSound("Cll") == string{"C400"});
    assert(convertTextToSound("Mn") == string{"M500"});
    assert(convertTextToSound("C") == string{"C000"});
    assert(convertTextToSound("AaaaaA") == string{"A000"});
    assert(convertTextToSound("Hwhw") == string{"H000"});
    assert(convertTextToSound("Wshngtn") == string{"W252"});
    assert(convertTextToSound("Washington") == string{"W252"});
    assert(convertTextToSound("") == string{"0000"});
    return 0;
}