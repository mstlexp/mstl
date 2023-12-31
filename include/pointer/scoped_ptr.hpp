/*
*This file is part of the Mini Thread Library (https://github.com/RoseLeBlood/MiniThread ).
*Copyright (c) 2018-2020 Amber-Sophia Schroeck
*
*The Mini Thread Library is free software; you can redistribute it and/or modify
*it under the terms of the GNU Lesser General Public License as published by
*the Free Software Foundation, version 3, or (at your option) any later version.

*The Mini Thread Library is distributed in the hope that it will be useful, but
*WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
*General Public License for more details.
*
*You should have received a copy of the GNU Lesser General Public
*License along with the Mini Thread  Library; if not, see
*<https://www.gnu.org/licenses/>.
*/

#ifndef _MINLIB_c5301b07_8f99_414e_83fd_742896aab4d6_H_
#define _MINLIB_c5301b07_8f99_414e_83fd_742896aab4d6_H_

#include "../config.hpp"


#include "../algorithm.hpp"
#include "../def.hpp"

namespace mofw {
    namespace pointer {

        template <typename T>
        class basic_scoped_ptr  {
        public:
            using value_type = T;
            using element_type = T;
            using pointer = value_type*;
            using const_value_type = const value_type;
            using self_type = basic_scoped_ptr<value_type>;

            explicit basic_scoped_ptr( pointer pValue = 0 )  : m_pPointer( pValue ) { }
            ~basic_scoped_ptr() { }

            void swap(self_type& b)             { mofw::swap<value_type*>(m_pPointer, b.m_pPointer); }
            void reset( pointer pValue = 0)     { self_type(pValue).swap(*this); }

            pointer get()                       { return m_pPointer; }

            pointer operator -> ()        { assert(m_pPointer != 0); return m_pPointer; }
            value_type& operator *()      { assert(m_pPointer != 0); return *m_pPointer; }

            operator bool()                     { return m_pPointer != 0; }
        private:
            pointer m_pPointer;
        };

        /**
		 * @brief Make a scoped pointer
		 * @tparam T Value type of the pointer.
		 * @tparam Args Argument for the object.
		 */
		template<typename T, typename... Args >
		inline basic_scoped_ptr<T> make_scoped(Args&&... args) {
			return basic_scoped_ptr<T>(new T (mofw::forward<Args>(args)...) );
		}

        template <typename T>
        using scoped_ptr = basic_scoped_ptr<T>;


    } // namespace pointer
} // namespace mofw

#endif
