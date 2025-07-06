#ifndef ATA_UTF_H
#define ATA_UTF_H
#include "ATA/config.h"
#include <cstdint>
#include <string>
#include <array>

namespace ata 
{
    namespace utf 
	{
        template <typename CharT>
        void encodeCharUtf8(char32_t input, std::basic_string<CharT>& outStrUtf8)
        {
            if (input < 128)
            {
                outStrUtf8.push_back(static_cast<CharT>(input));
                return;
            }

            if ((input > 0x0010FFFF) || ((input >= 0xD800) && (input <= 0xDBFF)))
                return;

            std::size_t bytestoWrite;
            if (input <  0x800)
                bytestoWrite = 2;
            else if (input <  0x10000)
                bytestoWrite = 3;
            else if (input <= 0x0010FFFF)
                bytestoWrite = 4;
            else
                return;

            static const std::uint8_t firstByteMask[5] = { 0, 0, 0xC0, 0xE0, 0xF0 };
            std::array<CharT, 4> bytes;
            if (bytestoWrite == 4) { bytes[3] = static_cast<CharT>((input | 0x80) & 0xBF); input >>= 6; }
            if (bytestoWrite >= 3) { bytes[2] = static_cast<CharT>((input | 0x80) & 0xBF); input >>= 6; }
            if (bytestoWrite >= 2) { bytes[1] = static_cast<CharT>((input | 0x80) & 0xBF); input >>= 6; }
            if (bytestoWrite >= 1) { bytes[0] = static_cast<CharT>(input | firstByteMask[bytestoWrite]); }

            outStrUtf8.append(bytes.begin(), bytes.begin() + bytestoWrite);
        }

        template <typename CharIt>
        CharIt decodeCharUtf8(CharIt inputCharIt, CharIt inputEndIt, std::u32string& outStrUtf32)
        {
            if (static_cast<std::uint8_t>(*inputCharIt) < 128)
            {
                outStrUtf32.push_back(static_cast<char32_t>(static_cast<std::uint8_t>(*inputCharIt)));
                return ++inputCharIt;
            }

            static const std::uint32_t offsetsMap[6] = { 0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080 };
            static const std::uint8_t trailingMap[128] =
            {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
            };

            const std::uint8_t trailingBytes = trailingMap[static_cast<std::uint8_t>(*inputCharIt) - 128];
            const std::uint32_t offset = offsetsMap[trailingBytes];
            const auto remainingBytes = std::distance(inputCharIt, inputEndIt) - 1;
            if (remainingBytes >= static_cast<decltype(remainingBytes)>(trailingBytes))
            {
                char32_t outputChar = 0;
                for (std::uint8_t i = 0; i < trailingBytes; ++i)
                {
                    outputChar += static_cast<char32_t>(static_cast<std::uint8_t>(*inputCharIt++));
                    outputChar <<= 6;
                }

                outputChar += static_cast<char32_t>(static_cast<std::uint8_t>(*inputCharIt++));
                outputChar -= offset;
                outStrUtf32.push_back(outputChar);
            }
            else
                inputCharIt = inputEndIt;

            return inputCharIt;
        }


#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        inline std::u8string UTF32_to_UTF8(const std::u32string& strUtf32)
        {
            std::u8string outStrUtf8;
            outStrUtf8.reserve(strUtf32.length() + 1);
            for (const char32_t& codepoint : strUtf32)
                encodeCharUtf8(codepoint, outStrUtf8);

            return outStrUtf8;
        }
#endif
        template <typename CharIt>
        std::u32string UTF8_to_UTF32(CharIt inputBegin, CharIt inputEnd)
        {
            std::u32string outStrUtf32;
            outStrUtf32.reserve(static_cast<std::size_t>((inputEnd - inputBegin) + 1));

            auto it = inputBegin;
            while (it < inputEnd)
                it = decodeCharUtf8(it, inputEnd, outStrUtf32);

            return outStrUtf32;
        }

        template <typename U16CharIt>
        std::u32string UTF16_to_UTF32(U16CharIt inputBegin, U16CharIt inputEnd)
        {
            std::u32string outStrUtf32;
            outStrUtf32.reserve((inputEnd - inputBegin) + 1);

            auto it = inputBegin;
            while (it < inputEnd)
            {
                const char16_t first = *it++;
                if ((first < 0xD800) || (first > 0xDBFF))
                {
                    outStrUtf32.push_back(static_cast<char32_t>(first));
                    continue;
                }

                if (it == inputEnd)
                    break;

                const char16_t second = *it++;
                if ((second >= 0xDC00) && (second <= 0xDFFF))
                    outStrUtf32.push_back(((static_cast<char32_t>(first) - 0xD800) << 10) + (static_cast<char32_t>(second) - 0xDC00) + 0x0010000);
            }


            return outStrUtf32;
        }

        template <typename WCharIt>
        std::u32string Wide_to_UTF32(WCharIt inputBegin, WCharIt inputEnd)
        {
            std::u32string outStrUtf32;
            outStrUtf32.reserve((inputEnd - inputBegin) + 1);

            for (auto it = inputBegin; it != inputEnd; ++it)
                outStrUtf32.push_back(static_cast<char32_t>(*it));


            return outStrUtf32;
        }

        inline std::string UTF32_to_Latin1(const std::u32string& strUtf32)
        {
            std::string outStr;
            outStr.reserve(strUtf32.length() + 1);
            for (const char32_t codepoint : strUtf32)
            {
                if (codepoint < 256)
                    outStr.push_back(static_cast<char>(codepoint));
            }

            return outStr;
        }

        inline std::string UTF32_to_StdStringUTF8(const std::u32string& strUtf32)
        {
            std::string outStrUtf8;
            outStrUtf8.reserve(strUtf32.length() + 1);
            for (const char32_t codepoint : strUtf32)
                encodeCharUtf8(codepoint, outStrUtf8);

            return outStrUtf8;
        }

        inline std::wstring UTF32_to_Wide(const std::u32string& strUtf32)
        {
            std::wstring outStr;
            outStr.reserve(strUtf32.length() + 1);

#if defined(__cpp_if_constexpr) && (__cpp_if_constexpr >= 201606L)
            if constexpr (sizeof(wchar_t) == 4)
#else
            if (sizeof(wchar_t) == 4)
#endif
            {
                for (const char32_t codepoint : strUtf32)
                    outStr.push_back(static_cast<wchar_t>(codepoint));
            }
            else
            {
                for (const char32_t codepoint : strUtf32)
                {
                    if ((codepoint < 0xD800) || ((codepoint > 0xDFFF) && (codepoint <= 0xFFFF)))
                        outStr.push_back(static_cast<wchar_t>(codepoint));
                }
            }

            return outStr;
        }

        inline std::u16string UTF32_to_UTF16(const std::u32string& strUtf32)
        {
            std::u16string outStrUtf16;
            outStrUtf16.reserve(strUtf32.length() + 1);

            for (const char32_t codepoint : strUtf32)
            {
                if (codepoint <= 0xFFFF)
                {
                    if ((codepoint < 0xD800) || (codepoint > 0xDFFF))
                        outStrUtf16.push_back(static_cast<char16_t>(codepoint));

                    continue;
                }
                else if (codepoint > 0x0010FFFF)
                    continue;
                outStrUtf16.push_back(static_cast<char16_t>(((codepoint - 0x0010000) >> 10)     + 0xD800));
                outStrUtf16.push_back(static_cast<char16_t>(((codepoint - 0x0010000) & 0x3FFUL) + 0xDC00));
            }

            return outStrUtf16;
        }
    }
}
#endif
