#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void count_chars(const string& s, int& upper, int& lower, int& digit, int& space, int& other, int& words) {
    upper = lower = digit = space = other = words = 0;
    bool in_word = false;
    for (char c : s) {
        if (isupper(c)) {
            upper++;
        }
        else if (islower(c)) {
            lower++;
        }
        else if (isdigit(c)) {
            digit++;
        }
        else if (isspace(c)) {
            space++;
            in_word = false;
        }
        else {
            other++;
        }

        if (isspace(c)) {
            continue;
        }

        if (!in_word) {
            words++;
            in_word = true;
        }
    }
}

string readFilesToString(string text,const string& file)
{
    ifstream infile1(file);
    if (infile1) {
        string line;
        while (getline(infile1, line)) {
            text += line + " ";
        }
    }
    else {
        cerr << "Failed to open file " << file << endl;
        return "";
    }
    return text;
}

int main() {
    string article;
    /*
    单行读入版本
    cout << "Enter an article: "<<endl;
    getline(cin, article);
    */

    //多文件读入版本
    article = readFilesToString(article, "C:\\Users\\princ\\source\\repos\\0318\\Debug\\file1.txt");
    article = readFilesToString(article, "C:\\Users\\princ\\source\\repos\\0318\\Debug\\file2.txt");
    article = readFilesToString(article, "C:\\Users\\princ\\source\\repos\\0318\\Debug\\file3.txt");
    
    cout << "\nString:\n" <<article<< endl;
   
    int upper, lower, digit, space, other, words;
    count_chars(article, upper, lower, digit, space, other, words);

    cout << "Uppercase letters: " << upper << endl;
    cout << "Lowercase letters: " << lower << endl;
    cout << "Digits: " << digit << endl;
    cout << "Spaces: " << space << endl;
    cout << "Other characters: " << other << endl;
    cout << "Words: " << words << endl;
}
