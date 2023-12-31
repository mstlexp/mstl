/*
*This file is part of the Mini Thread Library (https://github.com/RoseLeBlood/MiniThread ).
*Copyright (c) 2018 Amber-Sophia Schroeck
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
#ifndef _MINILIB_SOCKET_BASE_H_
#define _MINILIB_SOCKET_BASE_H_

#include "basic_endpoint.hpp"
#include "basic_dgram_socket.hpp"
#include "basic_multicast_ip_socket.hpp"
#include "basic_stream_ip_socket.hpp"
#include "basic_raw_ip_socket.hpp"

namespace mofw {
	namespace net {
		/**
		 * @brief using basic_ip4_address for ip4_address
		 * @ingroup socket
		 */
		using ip4_address = basic_ip4_address;
		/**
		 * @brief using basic_ip4_endpoint for ip4_endpoint
		 * @ingroup socket
		 */
		using ip4_endpoint = basic_ip4_endpoint;
		/**
		 * @brief using basic_dgram_ip_socket for dgram_ip4_socket
		 * @ingroup socket
		 */
		using dgram_ip4_socket = basic_dgram_ip_socket;

		/**
		 * @brief using basic_multicast_ip_socket for multicast_ip4_socket
		 * @ingroup socket
		 */
		using multicast_ip4_socket = basic_multicast_ip_socket;


		/**
		 * @brief using basic_ip6_address for stream_ip4_socket
		 * @ingroup socket
		 */
		using stream_ip4_socket = basic_stream_ip_socket;

		/**
		 * @brief using basic_raw_ip4_socket for raw_ip4_socket
		 * @ingroup socket
		 */
		using raw_ip4_socket = basic_raw_ip4_socket;
	#if LWIP_UDP && LWIP_UDPLITE
		/**
		 * @brief using basic_dgramlite_ip_socket for dgramlite_ip4_socket
		 * @ingroup socket
		 */
		using dgramlite_ip4_socket = basic_dgramlite_ip_socket;
		/**
		 * @brief using basic_multicast_ip_socket for multicast_ip4_socket
		 * @ingroup socket
		 */
		using multicast_ip4_socket_lite = basic_multicast_lite_ip_socket;
	#endif // LWIP_UDP



#if MN_THREAD_CONFIG_NET_IPADDRESS6_ENABLE == MN_THREAD_CONFIG_YES
		/**
		 * @brief using basic_ip6_address for ip6_address
		 * @ingroup socket
		 */
		using ip6_address = basic_ip6_address;
		/**
		 * @brief using basic_ip6_endpoint for ip6_endpoint
		 * @ingroup socket
		 */
		using ip6_endpoint = basic_ip6_endpoint;
		/**
		 * @brief using basic_dgram_ip6_socket for dgram_ip6_socket
		 * @ingroup socket
		 */
		using dgram_ip6_socket = basic_dgram_ip6_socket;
		/**
		 * @brief using basic_stream_ip6_socket for stream_ip6_socket
		 * @ingroup socket
		 */
		using stream_ip6_socket = basic_stream_ip6_socket;
		/**
		 * @brief using basic_raw_ip6_socket for raw_ip6_socket - - not IMPL
		 * @ingroup socket
		 */
		using raw_ip6_socket = basic_raw_ip6_socket;
	#if LWIP_UDP && LWIP_UDPLITE
		/**
		 * @brief using basic_dgramlite_ip6_socket for dgramlite_ip6_socket
		 * @ingroup socket
		 */
		using dgramlite_ip6_socket = basic_dgramlite_ip6_socket;
	#endif // LWIP_UDP
#endif // MN_THREAD_CONFIG_NET_IPADDRESS6_ENABLE

	}
}

#endif
