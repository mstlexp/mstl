/*
*This file is part of the Mini Thread Library (https://github.com/RoseLeBlood/MiniThread ).
*Copyright (c) 2021 Amber-Sophia Schroeck
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
#include "config.hpp"
#include "atomic_counter.hpp"


namespace mn {

	atomic_counter::atomic_counter()
		: m_atomicCount(0) { }

	atomic_counter::atomic_counter(const atomic_counter::value_type& counter)
		: m_atomicCount(counter) { }

	atomic_counter::atomic_counter(const atomic_counter& other)
		: m_atomicCount(other.m_atomicCount.load() ) { }


	atomic_counter& atomic_counter::operator = (const atomic_counter& counter) {
		m_atomicCount.store(counter.m_atomicCount.load());
		return *this;
	}


	atomic_counter& atomic_counter::operator = (const atomic_counter::value_type& value) {
		m_atomicCount.store(value);
		return *this;
	}
}

