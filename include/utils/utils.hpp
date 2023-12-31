/**
 * This file is part of the Mini Thread Library (https://github.com/RoseLeBlood/MiniThread ).
 * Copyright (c) 2021 Amber-Sophia Schroeck
 *
 * The Mini Thread Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3, or (at your option) any later version.

 * The Mini Thread Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the Mini Thread  Library; if not, see
 * <https://www.gnu.org/licenses/>.
*/

#ifndef MINLIB_STL_UTILS_H_
#define MINLIB_STL_UTILS_H_

#include <string.h>

#include "inttokey.hpp"
#include "../defines.hpp"
#include "../def.hpp"

#include "random.hpp"
#include "random_lfsr.hpp"
#include "ramdom_xorshift.hpp"

namespace mofw {
    namespace internal {

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void copy_n(const T* first, mofw::size_t n, T* result, int_to_type<false>) {
            const T* last = first + n;

            while (first != last) {
                switch (n & 0x3) {
                    case 0: *result++ = *first++;
                    case 3: *result++ = *first++;
                    case 2: *result++ = *first++;
                    case 1: *result++ = *first++;
                }
            }
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void copy_n(const T* first, mofw::size_t n, T* result, int_to_type<true>) {
            assert(result >= first + n || result < first);
            memcpy(result, first, n * sizeof(T));
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void copy(const T* first, const T* last, T* result, int_to_type<false>) {
            T* localResult = result;
            while (first != last)
                *localResult++ = *first++;
        }
        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void copy(const T* first, const T* last, T* result, int_to_type<true>) {
            const mofw::size_t n = reinterpret_cast<const char*>(last) - reinterpret_cast<const char*>(first);
            memcpy(result, first, n);
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline void move_n(const T* from, mofw::size_t n, T* result, int_to_type<false>) {
            for (int i = int(n) - 1; i >= 0; --i)
                    result[i] = from[i];
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline void move_n(const T* first, mofw::size_t n, T* result, int_to_type<true>) {
            memmove(result, first, n * sizeof(T));
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline void move(const T* first, const T* last, T* result, int_to_type<false>) {
            result += (last - first);
            while (--last >= first)
                    *(--result) = *last;
        }
        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline  void move(const T* first, const T* last, T* result, int_to_type<true>) {
            const mofw::size_t n = reinterpret_cast<uintptr_t>(last) - reinterpret_cast<uintptr_t>(first);
            memmove(result, first, n);
        }


        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void copy_construct_n(const T* first, mofw::size_t n, T* result, int_to_type<false>) {
            for (size_t i = 0; i < n; ++i)
                new (result + i) T(first[i]);
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void copy_construct_n(const T* first, mofw::size_t n, T* result, int_to_type<true>) {
            assert(result >= first + n || result < first);
            memcpy(result, first, n * sizeof(T));
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void destruct_n(T* first, mofw::size_t n, int_to_type<false>) {
            sizeof(first);
            for (size_t i = 0; i < n; ++i)
                    (first + i)->~T();
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline void destruct_n(T*, mofw::size_t, int_to_type<true>) {
            // Nothing to do, no destructor needed.
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void destruct(T* mem, int_to_type<false>) {
            sizeof(mem);
            mem->~T();
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline void destruct(T*, int_to_type<true>) {
             // Nothing to do, no destructor needed.
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void construct(T* mem, int_to_type<false>) {
            new (mem) T();
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline void construct(T*, int_to_type<true>) {
            // Nothing to do
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline void copy_construct(T* mem, const T& orig, int_to_type<false>) {
            new (mem) T(orig);
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline void copy_construct(T* mem, const T& orig, int_to_type<true>) {
            mem[0] = orig;
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        void construct_n(T* to, mofw::size_t count, int_to_type<false>) {
            sizeof(to);
            for (size_t i = 0; i < count; ++i)
                    new (to + i) T();
        }

        MN_TEMPLATE_FULL_DECL_ONE(typename, T)
        inline void construct_n(T*, int, int_to_type<true>) {
            // trivial ctor, nothing to do.
        }

        MN_TEMPLATE_FULL_DECL_TWO(class, TIter, class, TPred)
        void test_ordering(TIter first, TIter last, const TPred& pred) {
        	sizeof(first); sizeof(last); sizeof(pred);
        }

        MN_TEMPLATE_FULL_DECL_THREE(typename, T1, typename, T2, class, TPred)
        inline bool debug_pred(const TPred& pred, const T1& a, const T2& b) {
         	return pred(a, b);
        }

		struct in_place_type_tag {};
		struct in_place_index_tag {};

		struct in_place_type {};
    } // Intarnal

    MN_TEMPLATE_FULL_DECL_ONE(typename, T)
    struct less {
        bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs < rhs;
        }
	};
	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
    struct greater {
        bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs > rhs;
        }
	};
	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
    struct equal_to {
        bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs == rhs;
        }
	};
	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
	struct not_equal_to {
        bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs != rhs;
        }
	};


	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
	struct greater_equal  {
		bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs >= rhs;
        }
	};

	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
	struct less_equal  {
		bool operator()(const T& lhs, const T& rhs) const noexcept {
            return lhs <= rhs;
        }
	};

	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
	struct negate  {
		T operator()(const T& a) const noexcept {
            return -a;
        }
	};

	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
	struct plus  {
		T operator()(const T& a, const T& b) const noexcept {
            return a + b;
        }
	};

	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
	struct minus  {
		T operator()(const T& a, const T& b) const noexcept {
            return a - b;
        }
	};

	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
	struct multiplies  {
		T operator()(const T& a, const T& b) const noexcept {
            return a * b;
        }
	};

	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
	struct divides {
		T operator()(const T& a, const T& b) const noexcept {
            return a / b;
        }
	};

	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
	struct modulus {
		T operator()(const T& a, const T& b) const noexcept {
            return a % b;
        }
	};



	MN_TEMPLATE_FULL_DECL_ONE(typename, T)
    T nexthigher(T k) noexcept  {
		k--;
		for (unsigned int i=1; i< sizeof(T) * 8; i <<= 1)
			k |= (k >> i);
		return k+1;
	}


	template <typename T>
	struct inc {
		using value_type = T;
		value_type operator()(value_type x) const { return ++x; }
	};

	template <typename T>
	struct dec {
		using value_type = T;
		value_type operator()(value_type x) const { return --x; }
	};

	template <typename T, typename R>
	inline R _reinterpret_cast(T* p) {
		return static_cast<R>(static_cast<void*>(p));
	}

	template <typename T, typename R>
	inline const R _const_reinterpret_cast(const T* p) {
		return static_cast<const R>(static_cast<const void*>(p));
	}

	using random_xorshift = basic_ramdom_xorshift;
	using random_lfsr = basic_random_lfsr;

	using default_random_engine = random_xorshift;
}

#endif
