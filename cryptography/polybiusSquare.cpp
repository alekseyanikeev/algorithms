#include <iostream>
#include <vector>
#include <locale>
#include <wchar.h>
#include <string.h>
#include <utils.h>

class PolybyusSquare {
public:
    PolybyusSquare() {
        int i = 1;
        int j = 1;
        for (auto begin = tableLetters.begin(), end = tableLetters.end(); begin != end; begin++) {
            keysTable.insert({begin->first, j*10 + i});
            if (i == SIZE_TABLE) {
                j++;
                i = 1;
            }
            i++;
        } 
    }
    const std::vector<int> encrypt(const std::wstring& textToEncrypt);
    const std::wstring decrypt(const std::vector<int>& ecnryptedText);

private:
    const std::map<const wchar_t, const int> tableLetters = {
        {L'\u0410', 472}, {L'\u0411', 473}, {L'\u0412',  474}, {L'\u0413', 475}, {L'\u0414', 476}, {L'\u0415', 477}, {L'\u0416', 478},
        {L'\u0417', 479}, {L'\u0418', 480},  {L'\u0419', 481}, {L'\u041A', 482}, {L'\u041B', 483}, {L'\u041C', 484}, {L'\u041D', 485},
        {L'\u041E', 486}, {L'\u041F', 487}, {L'\u0420', 488}, {L'\u0421', 489}, {L'\u0422', 490}, {L'\u0423', 491},
        {L'\u0424', 492}, {L'\u0425', 493}, {L'\u0426', 494}, {L'\u0427', 495},	{L'\u0428', 496}, {L'\u0429', 497}, {L'\u042A', 498},
        {L'\u042B', 499}, {L'\u042C', 500}, {L'\u042D', 501}, {L'\u042E', 502}, {L'\u042F', 503}
    };
    std::map<const wchar_t, const int> keysTable;
    const int SIZE_TABLE = 6;
};

const std::vector<int> PolybyusSquare::encrypt(const std::wstring& decryptedText) {
    std::vector<int> ecryptedText;
    for (wchar_t letter: decryptedText)
        ecryptedText.push_back(keysTable.find(letter)->second);
    return ecryptedText;
}

const std::wstring PolybyusSquare::decrypt(const std::vector<int>& ecnryptedText) {
    std::wstring decryptedText{};
    for (size_t value: ecnryptedText)
        decryptedText.push_back(utils::getKeyByValue(keysTable, value));

    return decryptedText;
}

int main() {
    std::wstring decryptedText = L"АБВГД";
    PolybyusSquare ps;
    std::vector<int> encryptedText = ps.encrypt(decryptedText);
    for (auto value: encryptedText)
        std::cout << value << "\n";

    std::cout << "decrypted: " << utils::ws2s(ps.decrypt(encryptedText)) << "\n";
    return 0;
}