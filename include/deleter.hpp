/**
 * @file
 * This file is part of the Mini Thread Library (https://github.com/RoseLeBlood/MiniThread ).
 * @author Copyright (c) 2020 Amber-Sophia Schroeck
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
#ifndef __MINLIB_DEFAULT_DELETER_H__
#define __MINLIB_DEFAULT_DELETER_H__

#include "config.hpp"

#include "allocator/basic_deleter.hpp"
#include "allocator.hpp"

#define config_haveDefaultDeleter 1

namespace mofw {
	namespace memory {
		template<typename Type, class TAllocator = default_allocator>
		using default_delete = basic_deleter<Type, TAllocator>;
	}
}
#endif // __MINLIB_DEFAULT_DELETER_H__
