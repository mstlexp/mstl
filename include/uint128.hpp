/**
 * @file
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
#ifndef MINLIB_141d5496_b8a8_4aed_a898_4fc5b62195bc_H_
#define MINLIB_141d5496_b8a8_4aed_a898_4fc5b62195bc_H_

#include "config.hpp"

#include <stddef.h>
#include <stdint.h>



namespace mofw {
    struct basic_uint128_t {
        union {
            struct {
                uint64_t high;
                uint64_t low;
            };
            uint64_t value[2];
        };
    };

    using uint128_t       = basic_uint128_t;
    using uint_least128_t = basic_uint128_t;
}

#endif
