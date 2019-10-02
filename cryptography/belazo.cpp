#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "utils.h"


class Arguments {
public:
    Arguments(int argc, char *argv[], const int sizeOfArg = 5) {
        USAGE = "Usage: " + std::string((const char*)argv[0]) + " [options]\n" +
            HELP + " Display this information.\n" +
            KEY + "<value> Key to encrypt.\n" +
            TEXT + "<value> Text to encrypt.";

        if (argc != sizeOfArg)
            return;

        for (size_t i = 0; i < argc; i++)
            _argv.push_back((const char*)argv[i]);

        std::tuple<std::string, std::string> args = checkArg();
        key = std::get<0>(args);
        textToEncrypt = std::get<1>(args);
    }

    std::string textToEncrypt;
    std::string key;
    std::string USAGE;
    bool isHelp = 0;
private:
    
    int _argc;
    std::vector<std::string> _argv;

    const std::string KEY = "--key";
    const std::string SHORT_KEY = "-k";
    const std::string TEXT = "--text";
    const std::string SHORT_TEXT = "-t";
    const std::string HELP = "--help";
    const std::string SHORT_HELP = "-h";

    enum ARGS { NNAME = 0, NKEY = 1, NKEY_VALUE = 2, NTEXT = 3, NTEXT_VALUE = 4};

    std::tuple<std::string, std::string> checkArg() {
        if (_argv.at(ARGS::NKEY).compare(KEY) || _argv.at(ARGS::NKEY).compare(SHORT_KEY)) {
            if (_argv.at(ARGS::NTEXT).compare(TEXT) || _argv.at(ARGS::NTEXT).compare(SHORT_TEXT))
                return {_argv.at(ARGS::NKEY_VALUE), _argv.at(ARGS::NTEXT_VALUE)};
            if (_argv.at(ARGS::NKEY).compare(HELP) || _argv.at(ARGS::NKEY).compare(SHORT_HELP))
                isHelp = 1;
        }

        return {};
    }
};

class Belazo {
public:
    Belazo() = default;
    Belazo(const std::string& key, const std::string& textToEncrypt) : key(key), _key(utils::s2ws(key)), _textToEncrypt(utils::s2ws(textToEncrypt)) {
        wchar_t symbol = L'\u0410';
        for (size_t i = 0; i < sizeOfAlphabet; i++) {
            uAlphabet.push_back(symbol);
            uAlphabetMap.insert({textToEncrypt[i], (int)symbol});
            symbol++;
        }

        int keySize = _key.size();
        size_t keyPosition = 0;
        for (size_t i = 0, lengthText = _textToEncrypt.size(); i < lengthText; i++) {
            if (!(keyPosition < keySize))
                keyPosition = 0;
            keys.push_back(_key.at(keyPosition++));
        }

        symbol = L'\u0410';
        size_t endOffAlphabet = symbol + sizeOfAlphabet;
        size_t offsetAlphabet = symbol;
        for (size_t i = 0; i < key.size() + 1; i++) {
            std::vector<wchar_t> row{};
            std::map<int, wchar_t> rowMap{}; 
            for (size_t iAplhabet = 0; iAplhabet < sizeOfAlphabet; iAplhabet++) {
                if (i == 0) {
                    if (offsetAlphabet + iAplhabet < endOffAlphabet) {
                    row.push_back((wchar_t)offsetAlphabet + iAplhabet);
                    rowMap.insert({(wchar_t)offsetAlphabet + iAplhabet, (int)offsetAlphabet + iAplhabet});
                    }
                    else {
                        row.push_back((wchar_t)((int)offsetAlphabet + (int)iAplhabet) - sizeOfAlphabet);
                        rowMap.insert({(wchar_t)((int)offsetAlphabet + (int)iAplhabet) - sizeOfAlphabet, ((int)offsetAlphabet + (int)iAplhabet) - sizeOfAlphabet});
                    }
                } else {
                    if (offsetAlphabet + iAplhabet < endOffAlphabet) {
                        row.push_back((wchar_t)offsetAlphabet + iAplhabet - 1);
                        rowMap.insert({(wchar_t)offsetAlphabet + iAplhabet - 1, (int)offsetAlphabet + iAplhabet - 1});
                    }
                    else {
                        row.push_back((wchar_t)((int)offsetAlphabet + (int)iAplhabet) - sizeOfAlphabet - 1);
                        rowMap.insert({(wchar_t)((int)offsetAlphabet + (int)iAplhabet) - sizeOfAlphabet -1, ((int)offsetAlphabet + (int)iAplhabet) - sizeOfAlphabet - 1});
                    }
                }
                
            }
            tableKeysToEncrypt.insert({key[i], rowMap});
            tableKeys.push_back(row);
            offsetAlphabet = _key[i] + 1;
        }
        std::cout << "table keys: \n";
        for (auto row : tableKeys) {
            std::wstring rowString = {};
            for (wchar_t symbol : row)
                rowString.push_back(symbol);
            std::cout << utils::ws2s(rowString) << "\n";
        }
    };

    std::wstring encrypt(const std::string& text);
    std::wstring decrypt(const std::wstring& text);

private:
    std::wstring uAlphabet{};
    std::map<char, int> uAlphabetMap{}; 
    std::string key;
    std::wstring _key;
    std::wstring _textToEncrypt;
    std::wstring keys;
    std::map<wchar_t, std::map<int, wchar_t>> tableKeysToEncrypt;
    std::vector<std::vector<wchar_t>> tableKeys;
    const size_t sizeOfAlphabet = 32;
};

std::wstring Belazo::encrypt(const std::string& text) {
    std::wstring result{};
    std::wstring inputData = utils::s2ws(text);
    auto keysString = utils::ws2s(keys);
    for (size_t keyIndex = 0; keyIndex < keysString.size(); keyIndex++) {
        const auto& ctype = std::use_facet< std::ctype<wchar_t> >( std::locale() ) ;
        
        // 1) Находим строку для замены std::map<int, wchar_t>
        wchar_t * tw ;
        char *tc = new char(keysString[keyIndex]); 
        std::cout << "res of convertonig: " << mbstowcs(tw, tc, 1) << std::endl;
        auto rowToReplacement =  tableKeysToEncrypt.find(tw[0]);
        if (rowToReplacement == tableKeysToEncrypt.end()) {
            continue;
        } else {
            std::cout << "finding key map\n" ;
        }
        // 2) Ищем индекс по первой строке(не измененной)
        auto  symbolChar = uAlphabetMap.find(text[keyIndex]);
        if (symbolChar == uAlphabetMap.end()) {
            continue;
        }
        
        // 3) ищем символ юникод  из мапы по индексу
        auto resWcharIter = rowToReplacement->second.find(symbolChar->second);
        if (resWcharIter != rowToReplacement->second.end()) {
            result.push_back(resWcharIter->second);
        }
    }


    for (size_t i = 0; i <  text.size(); i++) {
        for (size_t j = 0; j < utils::ws2s(keys).size(); j++) {
            if (text[i] == (int)_key[j]) {
                for (size_t ti = 0; ti < tableKeys[0].size(); ti++) {
                    if (tableKeys[0][ti] == _key[j]) {
                        for (size_t tii = 0; tii < tableKeys.size(); tii++) {
                            for (size_t tij = 0; tij < tableKeys[tii].size(); tij++) {
                                if (tableKeys[tii][tij] == _key[j]) {
                                    result.push_back(tableKeys[tii][ti]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    /*std::map<int, wchar_t> secondLevel{};

    for (size_t i = 0; i <  text.size(); i++) {
        auto iter = tableKeysToEncrypt.find(keys[i]);
        if (iter != tableKeysToEncrypt.end()) {
            secondLevel = iter->second; 
            auto iterToInt = uAlphabetMap.find(text[i]);
            if (iterToInt != uAlphabetMap.end()) {
                result.push_back((int)iterToInt->second);
                auto secondIter = secondLevel.find((int)iterToInt->second);
                if (secondIter != secondLevel.end())
                    result.push_back((wchar_t)secondIter->second);
            }
        }
    }
    */
    return result;
}

std::wstring Belazo::decrypt(const std::wstring& text) {
    std::wstring result{};
    std::map<int, wchar_t> secondLevel{};

    for (size_t i = 0; i <  text.size(); i++) {
        auto iter = tableKeysToEncrypt.find(keys[i]);
        if (iter != tableKeysToEncrypt.end()) {
            secondLevel = iter->second; 
            auto iterToInt = uAlphabetMap.find(text[i]);
            if (iterToInt != uAlphabetMap.end()) {
                result.push_back((int)iterToInt->second);
                auto secondIter = secondLevel.find((int)iterToInt->second);
                if (secondIter != secondLevel.end())
                    result.push_back((wchar_t)secondIter->second);
            }
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    Arguments arguments(argc, argv);
    if (arguments.key.empty() || arguments.isHelp || arguments.textToEncrypt.empty()) {
        std::cout << arguments.USAGE << "\n";
        return 0;
    } 
    else {
        Belazo belazo(arguments.key, arguments.textToEncrypt);
        std::cout << "\n" << " encryptedText: " << utils::ws2s(belazo.encrypt(arguments.textToEncrypt)) << std::endl;
        std::cout << "\n" << " decryptedText: " << arguments.textToEncrypt << std::endl;
    }
    return 0;
}