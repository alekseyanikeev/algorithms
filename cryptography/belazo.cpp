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
    Belazo(const std::string& key, const std::string& textToEncrypt) : _key(utils::s2ws(key)), _textToEncrypt(utils::s2ws(textToEncrypt)) {
        wchar_t symbol = L'\u0410';
        for (size_t i = 0; i < sizeOfAlphabet; i++)
            uAlphabet.push_back(symbol++);

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
            for (size_t iAplhabet = 0; iAplhabet < sizeOfAlphabet; iAplhabet++) {
                if (offsetAlphabet + iAplhabet < endOffAlphabet) {
                    row.push_back((wchar_t)offsetAlphabet + iAplhabet);
                }
                else {
                    row.push_back((wchar_t)((int)offsetAlphabet + (int)iAplhabet) - sizeOfAlphabet);
                }
            }
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

    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);

private:
    std::wstring uAlphabet{}; 
    std::wstring _key;
    std::wstring _textToEncrypt;
    std::wstring keys;
    std::vector<std::vector<wchar_t>> tableKeys;
    const size_t sizeOfAlphabet = 32;
};

int main(int argc, char *argv[]) {
    Arguments arguments(argc, argv);
    if (arguments.key.empty() || arguments.isHelp || arguments.textToEncrypt.empty()) {
        std::cout << arguments.USAGE << "\n";
        return 0;
    } 
    else {
        Belazo belazo(arguments.key, arguments.textToEncrypt);
    }
    return 0;
}
