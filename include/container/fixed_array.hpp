/**
 * @file
 * @brief Class for a fixed array.
 * This file is part of the Mini Thread Library (https://github.com/RoseLeBlood/MiniThread ).
 * @author Copyright (c) 2018 Amber-Sophia Schroeck
 * @par License
 * The Mini Thread Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3, or (at your option) any later version.
 *
 * The Mini Thread Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the Mini Thread  Library; if not, see
 * <https://www.gnu.org/licenses/>.
 */
#ifndef __MINILIB_CONTAINER_FIXED_ARRAY_H__
#define __MINILIB_CONTAINER_FIXED_ARRAY_H__

#include "../config.hpp"

# include <cassert>
# include <typeinfo>

#include "algorithm.hpp"
#include "../allocator.hpp"
#include "../def.hpp"
#include "../functional.hpp"
#include "../typetraits.hpp"

#include "../utils/mn_utils.hpp"


namespace mofw {
	namespace container {



		/**
		 * @brief A standard container for storing a fixed size sequence of elements.
		 * @note Sets support random access iterators.
		 *
		 * @tparam  T  Type of element.
		 * @tparam  N  Number of elements.
		 * @ingroup container
		 */
		template<typename T, size_t N>
		class basic_fixed_array {
		public:
			using self_type = basic_fixed_array<T, N>;

			using value_type = T;
			using pointer = T*;
			using const_pointer = const T*;
			using reference = T&;
			using const_reference = const T&;
			using iterator = T*;
			using const_iterator = const T*;

			using size_type = mofw::size_t;
			using difference_type = mofw::ptrdiff_t;

			basic_fixed_array() { if(is_pointer<T>::value) fill(nullptr); else fill(T()); }
			basic_fixed_array(const value_type& val) 	{ fill(val); }
			basic_fixed_array(const self_type& other) {
				memcpy(m_nData, other.m_nData, sizeof(m_nData));
			}


			iterator  		begin() noexcept 			{ return &m_nData[0]; }
			constexpr const_iterator 	begin() const noexcept
				{ return (m_nData[0]); }

			iterator  		end() noexcept 				{ return (m_nData[N-1]); }
			constexpr const_iterator 	end() const noexcept
				{ return (m_nData[N-1]); }

			reference 		front() noexcept 			{ return (m_nData[0]); }
      		const_reference front() const noexcept		{ return (m_nData[0]); }

      		reference 		back() noexcept 			{ return (m_nData[N-1]); }
			const_reference back() const noexcept 		{ return (m_nData[N-1]); }

			size_type 		size() const noexcept 		{ return N; }

			reference 		at(size_type pos) 			{ return m_nData[pos]; }
			const_reference at(size_type pos) const 	{ return m_nData[pos]; }

			void fill(const value_type& val) {
				mofw::fill_n<value_type>(begin(), N, val);
			}

			void swap(self_type& other) noexcept  {
				swap_ranges(begin(), end(), other.begin());
			}

			reference operator[](size_type pos) noexcept {
				return m_nData[pos]; }

      		constexpr const_reference operator[](size_type pos) const noexcept {
      			return m_nData[pos];
			}

			bool is_equele(const self_type& other) {
				for(int i = 0; i<N; i++)
					if(m_nData[i] != other.m_nData[i]) return false;
				return true;
			}

		private:
			value_type m_nData[N];
		};

		// Array comparisons.
		template<typename T, size_t N>
		inline bool  operator == (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
			return a.is_equele(b);
		}

		template<typename T, size_t N>
		inline bool  operator != (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
			return !(a.is_equele(b));
		}


 		template<typename T, size_t N>
		inline bool  operator < (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
			for(int i = 0; i<N; i++)
				if(a[i] >= b[i]) return false;
			return true;
		}

		template<typename T, size_t N>
		inline bool  operator <= (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
			for(int i = 0; i<N; i++)
				if(a[i] > b[i]) return false;
			return true;
		}

		template<typename T, size_t N>
		inline bool  operator > (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
			for(int i = 0; i<N; i++)
				if(a[i] <= b[i]) return false;
			return true;
		}

		template<typename T, size_t N>
		inline bool  operator >= (const basic_fixed_array<T, N>& a, const basic_fixed_array<T, N>& b) {
			for(int i = 0; i<N; i++)
				if(a[i] < b[i]) return false;
			return true;
		}

		template<typename T, size_t N>
		inline void swap (basic_fixed_array<T, N>& a, basic_fixed_array<T, N>& b) {
			a.swap(b);
		}

		template<typename T, size_t N>
		inline void fill (basic_fixed_array<T, N>& a, const int val) {
			a.fill(val);
		}

		template<typename T, size_t N>
		inline void zero (basic_fixed_array<T, N>& a) {
			a.fill(0);
		}

		template<typename T, size_t N>
		using fixed_array = basic_fixed_array<T, N>;
	}
}

#endif // __MINILIB_CONTAINER_ARRAY_H__
