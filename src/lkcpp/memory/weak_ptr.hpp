#pragma once

#include "lkcpp/memory/shared_ptr.hpp"

namespace lkcpp
{
    template <class T>
    class weak_ptr
    {
    public:
        weak_ptr() = default;
        weak_ptr(weak_ptr const &) = default;
        weak_ptr(weak_ptr &&) = default;
        weak_ptr &operator=(weak_ptr const &) = default;
        weak_ptr &operator=(weak_ptr &&) = default;

        weak_ptr(lkcpp::shared_ptr<T> const &shared);
        weak_ptr(lkcpp::shared_ptr<T> &&shared);
        virtual ~weak_ptr();

        void reset();
        lkcpp::size_t use_count() const;
        lkcpp::shared_ptr<T> lock() const;

    private:
        T *m_t = nullptr;
        lkcpp::size_t *m_ref_count = nullptr;
        lkcpp::size_t m_size = 0;
    };

    template <class T>
    weak_ptr<T>::weak_ptr(lkcpp::shared_ptr<T> const &shared)
        : m_t(shared.m_t), m_ref_count(shared.m_ref_count), m_size(shared.m_size) {}

    template <class T>
    weak_ptr<T>::weak_ptr(lkcpp::shared_ptr<T> &&shared)
        : m_t(shared.m_t), m_ref_count(shared.m_ref_count), m_size(shared.m_size) {}

    template <class T>
    weak_ptr<T>::~weak_ptr()
    {
        reset();
    }

    template <class T>
    void weak_ptr<T>::reset()
    {
        m_t = nullptr;
        m_ref_count = nullptr;
        m_size = 0;
    }

    lkcpp::size_t use_count() const
    {
        if (m_ref_count)
        {
            return *m_ref_count;
        }
        else
        {
            return 0;
        }
    }

    template <class T>
    inline lkcpp::shared_ptr<T> weak_ptr<T>::lock() const
    {
        return lkcpp::shared_ptr<T>(m_t, m_size);
    }
}