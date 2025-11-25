#include <algorithm>
#include <cassert>
#include <cctype>
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

    char first_letter = text[0];
    text = text.substr(1);
    for (size_t i = 0; i < text.size(); i++) {
        text[i] = tolower(text[i]);
    }
    text.erase(remove_if(text.begin(), text.end(), [](char c) {
        return c == 'h' || c == 'w';
    }), text.end());

    string converted_text;
    char last_added_letter = '\0';
    for (size_t i = 0; i < text.size(); i++) {
        char ch;
        switch(text[i]) {
            case 'b': case 'f': case 'p': case 'v':
                ch = '1';
                break;
            case 'c': case 'g': case 'j': case 'k': case 'q': case 's': case 'x': case 'z':
                ch = '2';
                break;
            case 'd': case 't':
                ch = '3';
                break;
            case 'l':
                ch = '4';
                break;
            case 'm': case 'n':
                ch = '5';
                break;
            case 'r':
                ch = '6';
                break;
            default:
                ch = '\0';
                break;
        }
        if (ch != '\0') {
            if (ch != last_added_letter) {
                converted_text.push_back(ch);
                last_added_letter = ch;
                if (converted_text.size() >= 3) break;
            }
        }
        else {
            last_added_letter = '\0';
        }
    }
    converted_text.insert(0, 1, first_letter);
    if (converted_text.length() != 4){
        converted_text +=  string(4 - converted_text.length(), '0');
    }
    cout << converted_text << "\n";
    return converted_text;
}

int main()
{
    string text1{"ASHCRAFT"};
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