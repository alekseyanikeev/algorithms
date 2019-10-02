#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
#include <iterator>
#include <tuple>


class Tritemio {
public: 
    Tritemio() = default;
    Tritemio(const int alphabetOffset, const int widthOffset) {
        int row = 1;
        int column = 1;
        for (size_t index = 0, size = tableLetters.size(); index < size; index++) {
            if ((index + alphabetOffset) < size)
                keysTable.insert({std::get<0>(tableLetters.at(index + alphabetOffset)), row * 10 + column});    
            else
                keysTable.insert({std::get<0>(tableLetters.at(size - (index + alphabetOffset))), row * 10 + column});

            if (column == widthOffset) {
                row++;
                column = 1;
            } else
                column++;
        }
    }

    const std::vector<const int> encrypt(const std::wstring& decryptedText);
    const std::wstring decrypt(const std::vector<const int>& encrtyptedText);

private:
    const std::vector<std::tuple<const wchar_t, const int>> tableLetters = {
        {L'\u0410', 472}, {L'\u0411', 473}, {L'\u0412',  474}, {L'\u0413', 475}, {L'\u0414', 476}, {L'\u0415', 477}, {L'\u0416', 478},
        {L'\u0417', 479}, {L'\u0418', 480},  {L'\u0419', 481}, {L'\u041A', 482}, {L'\u041B', 483}, {L'\u041C', 484}, {L'\u041D', 485},
        {L'\u041E', 486}, {L'\u041F', 487}, {L'\u0420', 488}, {L'\u0421', 489}, {L'\u0422', 490}, {L'\u0423', 491},
        {L'\u0424', 492}, {L'\u0425', 493}, {L'\u0426', 494}, {L'\u0427', 495},	{L'\u0428', 496}, {L'\u0429', 497}, {L'\u042A', 498},
        {L'\u042B', 499}, {L'\u042C', 500}, {L'\u042D', 501}, {L'\u042E', 502}, {L'\u042F', 503}
    };
    const int numbersEnglish = 22;
    std::map<const wchar_t, const int> keysTable;

};

const std::vector<const int> Tritemio::encrypt(const std::wstring& decryptedText) {
    std::vector<int> encryptedText{};
    auto end = keysTable.end();
    for (auto key : decryptedText) {
        auto valueIter = keysTable.find(key);
        if (valueIter != end)
            encryptedText.push_back(valueIter->second);
        else
            return {};
    }

}

const std::wstring Tritemio::decrypt(const std::vector<const int>& encrtyptedText) {
    std::wstring dectypredText{}; 
    for (auto value : encrtyptedText) {
        wchar_t key = utils::getKeyByValue(keysTable, value);
        if (key != NULL)
            dectypredText.push_back(key);
        else
            return {};
    }

    return dectypredText;
}