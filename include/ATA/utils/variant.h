#ifndef ATA_VARIANT_H
#define ATA_VARIANT_H
#include "ATA/config.h"
#if __cplusplus >= 201703L
    #include <variant>
#else
    #include "ATA/utils/any.h"
#endif

namespace ata
{
#if __cplusplus >= 201703L
    template <typename... Types>
#else
    template <typename FirstType, typename... OtherTypes>
#endif
    class Variant
    {
    public:
        Variant() :
#if __cplusplus >= 201703L
            m_variant{}
#else
            m_any{FirstType{}}
#endif
        {
        }

        template <typename T>
        Variant(const T& value) :
#if __cplusplus >= 201703L
            m_variant{value}
#else
            m_any{value}
#endif
        {
        }

        template <typename T>
        T& get()
        {
#if __cplusplus >= 201703L
            return std::get<T>(m_variant);
#else
            return *any_cast<T>(&m_any);
#endif
        }

        template <typename T>
        const T& get() const
        {
#if __cplusplus >= 201703L
            return std::get<T>(m_variant);
#else
            return any_cast<T>(m_any);
#endif
        }

    private:

#if __cplusplus >= 201703L
        std::variant<Types...> m_variant;
#else
        ata::Any m_any;
#endif
    };
}
#endif

