#include <string>
#include <wchar.h>
#include <codecvt>
#include <locale>
#include <map>


namespace utils {
    __always_inline
    std::wstring s2ws(const std::string& str) {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;

        return converterX.from_bytes(str);
    }

    __always_inline
    std::string ws2s(const std::wstring& wstr) {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;

        return converterX.to_bytes(wstr);
    }

    __always_inline
    const wchar_t getKeyByValue(const std::map<const wchar_t, const int>& keysTable, const int value) {
        for (auto it : keysTable)
            if (it.second == value)
                return it.first;
        return {};
    }
}
