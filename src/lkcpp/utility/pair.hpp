#pragma once

#include "lkcpp/tuple.hpp"

namespace lkcpp
{
    template <class T1, class T2>
    class pair : public tuple<T1, T2>
    {
    public:
        pair() = default;
        pair(pair<T1, T2> const &) = default;
        pair(pair<T1, T2> &&) = default;
        pair &operator=(pair<T1, T2> const &) = default;
        pair &operator=(pair<T1, T2> &&) = default;
        virtual ~pair() = default;

        pair(T1 &&t1, T2 &&t2);

        T1 &first();
        T1 const &first() const;
        T2 &second();
        T2 const &second() const;
    };

    template <class T1, class T2>
    pair<T1, T2>::pair(T1 &&t1, T2 &&t2)
        : tuple<T1, T2>(t1, t2) {}

    template <class T1, class T2>
    T1 &pair<T1, T2>::first()
    {
        return get<0>();
    }

    template <class T1, class T2>
    T1 const &pair<T1, T2>::first() const
    {
        return get<0>();
    }

    template <class T1, class T2>
    T2 &pair<T1, T2>::second()
    {
        return get<1>();
    }

    template <class T1, class T2>
    T2 const &pair<T1, T2>::second() const
    {
        return get<1>();
    }
}