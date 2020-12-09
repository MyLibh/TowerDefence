#ifndef __UTILITY_HPP_INCLUDED__
#define __UTILITY_HPP_INCLUDED__

#include <set>

template <typename _T, typename _Pred>
void discard_if(std::set<_T>& s, _Pred pred)
{
    for (auto it = std::begin(s); it != std::end(s);)
        if (pred(*it))
            it = s.erase(it);
        else
            ++it;
}

#endif /* !__UTILITY_HPP_INCLUDED__ */