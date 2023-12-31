/**
 * @file
 * This file is part of the Mini Thread Library (https://github.com/RoseLeBlood/MiniThread ).
 * @author Copyright (c) 2021 Amber-Sophia Schroeck
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

#ifndef _MINLIB_BASIC_ENDIAN_H_
#define _MINLIB_BASIC_ENDIAN_H_

#include "config.hpp"
#include "functional.hpp"

namespace mofw {
	namespace endian  {
		enum class order {
			little,
			big,
			native
		};
		enum class align {
			no,
			yes
		};
	}
	/**
	 * @brief Get the underlying endian architecture?
	 * @return If true then is the underlying architecture is big endian and false if not.
	 */
    struct system_endian {
    	/**
		 * @brief Get the underlying endian architecture?
		 * @return The underlying endian architecture.
		 */
    	endian::order operator() const noexcept {
			short tester = 0x0001;
			return  (*(char*)&tester != 0) ? endian::order::little : endian::order::big;
    	}
    }
}



#endif // _MINLIB_BASIC_ENDIAN_H_
