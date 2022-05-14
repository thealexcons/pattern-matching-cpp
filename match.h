#ifndef MATCH_H
#define MATCH_H

#include <variant>

namespace pm {
namespace {

template <typename... Ts>
struct overload_set : Ts...
{
    using Ts::operator()...;
};

template <typename... Ts>
overload_set(Ts...) -> overload_set<Ts...>;

} // anonymous namespace

template <typename Variant>
class match
{
public:
    constexpr explicit match(const Variant& variant) : d_variant(variant) {}

    template<typename... Fs>
    constexpr auto on(Fs... fs)
    {
        return std::visit(overload_set { std::forward<Fs>(fs)... }, d_variant);
    }

private:
    Variant d_variant;
};

} // namespace pm

#endif // MATCH_H
