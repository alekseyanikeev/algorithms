#include <iostream>
#include <vector>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <utils.h>

constexpr int SIZE_OF_KEYS = 33;

const std::map<const wchar_t, const int> keysTable = {
    {L'\u0410', 472}, {L'\u0411', 473}, {L'\u0412',  474}, {L'\u0413', 475}, {L'\u0414', 476}, {L'\u0415', 477}, {L'\u0416', 478},
    {L'\u0417', 479}, {L'\u0418', 480},  {L'\u0419', 481}, {L'\u041A', 482}, {L'\u041B', 483}, {L'\u041C', 484}, {L'\u041D', 485},
    {L'\u041E', 486}, {L'\u041F', 487}, {L'\u0420', 488}, {L'\u0421', 489}, {L'\u0422', 490}, {L'\u0423', 491},
    {L'\u0424', 492}, {L'\u0425', 493}, {L'\u0426', 494}, {L'\u0427', 495},	{L'\u0428', 496}, {L'\u0429', 497}, {L'\u042A', 498},
    {L'\u042B', 499}, {L'\u042C', 500}, {L'\u042D', 501}, {L'\u042E', 502}, {L'\u042F', 503}
};

const int getValueByKey(const std::map<const wchar_t, const int>& keysTable, const wchar_t key) {
    auto iterValue = keysTable.find(key);
    if (iterValue != keysTable.end())
        return iterValue->second;
    return -1;
}



const std::wstring encrypt(const std::map<const wchar_t, const int>& keysTable, const std::wstring& textToEncrypt) {
    std::vector<int> values;
    for (const wchar_t key: textToEncrypt)
        values.push_back(getValueByKey(keysTable, key));

    std::wstring decryptedText = {};
    for (auto value: values)
        decryptedText.push_back(utils::getKeyByValue(keysTable, 472 +  503 - value));

    return decryptedText;
}

const std::wstring decrypt(const std::map<const wchar_t, const int>& keysTable, const std::wstring& textToDecrypt){
    return encrypt(keysTable, textToDecrypt);  
}

const std::wstring encryptCaesar(const std::map<const wchar_t, const int>& keysTable, const std::wstring& textToEncrypt, const int keyOffset) {
    std::vector<int> values;
    for (const wchar_t key: textToEncrypt)
        values.push_back(getValueByKey(keysTable, key));

    std::wstring decryptedText = {};
    for (auto value: values) {
        auto offset = value + keyOffset;
        if (offset > 503)
            offset = offset - 503 + 472; 
        decryptedText.push_back(utils::getKeyByValue(keysTable, offset));
    }

    return decryptedText;
}

const std::wstring decryptCaesar(const std::map<const wchar_t, const int>& keysTable, const std::wstring& textToDecrypt, const int keyOffset) {
    std::vector<int> values;
    for (const wchar_t key: textToDecrypt)
        values.push_back(getValueByKey(keysTable, key));

    std::wstring decryptedText = {};
    for (auto value: values) {
        auto offset = value - keyOffset;
        if (offset < 472)
            offset = offset + 503 - 472; 
        decryptedText.push_back(utils::getKeyByValue(keysTable, offset));
    }

    return decryptedText;  
}

int main() {
    std::wstring decryptedText = L"АБВГД";
    std::wstring encryptedText = encryptCaesar(keysTable, decryptedText, 1);
    std::cout << "encrypted text: " << utils::ws2s(encryptedText) << "\n";
    std::cout << "decrypted text: " << utils::ws2s(decryptCaesar(keysTable, encryptedText, 1)) << "\n";

    return 0;
}
