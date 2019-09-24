#include <iostream>
#include <string>
#include <vector>
#include <tuple>

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

int main(int argc, char *argv[]) {
    Arguments arguments(argc, argv);
    if (arguments.key.empty() || arguments.isHelp || arguments.textToEncrypt.empty()) {
        std::cout << arguments.USAGE << "\n";
        return 0;
    } 
    else {
        std::cout << "keys: " << arguments.key << "\ntext: " << arguments.textToEncrypt << "\n";
    }
    return 0;
}