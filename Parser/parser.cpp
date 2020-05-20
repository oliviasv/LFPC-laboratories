#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string allWords[1000][2];
int globalPosition = 0;

string checkType(char el) {
    if (el == '>') return "greater_than";
    if (el == '<') return "smaller_than";
    if (el == '=') return "equal";
    if (el == '{') return "left_curly_bracket";
    if (el == '}') return "right_curly_bracket";
    if (el == '[') return "left_square_bracket";
    if (el == ']') return "right_square_bracket";
    if (el == '(') return "left_round_bracket";
    if (el == ')') return "right_round_bracket";
    if (el == ':') return "two_points";
    if (el == '#') return "hash_tag";
    if (el == ';') return "semicolon";
    if (el == '+') return "plus";
    if (el == '-') return "minus";
    if (el == '/') return "divided";
    if (el == '*') return "multiply";
    if (el == '%') return "modulus";
    if (el == '\'') return "quote";
    if (el == ',') return "comma";
    if (el == '.') return "point";

    if (isalpha(el)) return "word";
    if (!isalpha(el)) return "number";
}

void getWordSubItems(string word) {
    string localWord = "";
    for (int i = 0; i < word.size(); i++) {
        if (word[i] != ' ' && word[i] != '\t') {
            if (i < word.size() - 1) {
                if (checkType(word[i]) == checkType(word[i + 1])) {
                    localWord = localWord + word[i];
                } else {
                    if (i == 0) {
                        allWords[globalPosition][0] = word[i];
                        allWords[globalPosition][1] = checkType(word[i]);
                        globalPosition++;
                    } else {
                        localWord = localWord + word[i];
                        allWords[globalPosition][0] = localWord;
                        allWords[globalPosition][1] = checkType(word[i]);
                        globalPosition++;
                        localWord = "";
                    }
                }
            } else {
                if (checkType(word[i]) == checkType(word[i])) {
                    localWord = localWord + word[i];
                    allWords[globalPosition][0] = localWord;
                    allWords[globalPosition][1] = checkType(word[i]);
                    globalPosition++;
                } else {
                    allWords[globalPosition][0] = word[i];
                    allWords[globalPosition][1] = checkType(word[i]);
                    globalPosition++;
                }
            }
        }
    }
}

int main() {
    ifstream infile;
    infile.open("C:\\Users\\olivia\\Desktop\\Parser\\input.txt");
    if (!infile) {
        cerr << "Error opening \"input.txt\".\r\n";
        return 1;
    }

    string input_text;
    while (getline(infile, input_text)) {
        getWordSubItems(input_text);
    }

    for (int i = 0; i < globalPosition; i++) {
        cout << "Token { \n      type: " + allWords[i][1] + ",\n      value: \"" + allWords[i][0] + "\", \n     };\n"
             << endl;
    }

    return 0;
}
