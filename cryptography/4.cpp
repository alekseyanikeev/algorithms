#include <iostream>
#include <string>
#include <map>

class tClass {
public: 
    tClass() {
        char symbol = 'A';
        int i = 0;
        int j = 0;
        int offset = 1;
        for (int i = 0; i < numbersEnglish; i++) {
            std::map<char, int> row{};
            for (int j = 0; j < numbersEnglish; i++)
                row.insert({symbol + (offset + i > 22 ? 22 - offset + i: offset + i), i});
            keysTable.insert({symbol + j, row});
            offset++;
        }
    }

    const std::string encrypt(const std::string& decryptedText, const int offset);
    const std::string decrypt(const std::string& encrtyptedText, const int offset);

private:
    const int numbersEnglish = 22;
    std::map<char, std::map<char, int>> keysTable{};

};

const std::string tClass::encrypt(const std::string& decryptedtext, const int offset) {
    for (char symbol: decryptedtext)
    return{};
}

const std::string tClass::decrypt(const std::string& encryptedText, const int offset) {
    return {};
}

int main() {
    return 0;
}