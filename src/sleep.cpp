// *** ADDED BY HEADER FIXUP ***
#include <ctime>
// *** END ***
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
#include "config.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>

#include <esp_log.h>
#include <esp_err.h>
#include <nvs_flash.h>
#include <esp_system.h>
#include <esp_spi_flash.h>
#include <esp_attr.h>
#include <esp_partition.h>
#include <sys/time.h>

#include "sleep.hpp"

MN_EXTERNC_BEGINN

namespace mofw {
	#if 0
	//-----------------------------------
	//  sleep
	//-----------------------------------
	unsigned sleep(unsigned int secs) {
		vTaskDelay( (secs * 1000) / ((TickType_t) 1000 / configTICK_RATE_HZ));
		return 0;
	}



	//-----------------------------------
	//  usleep
	//-----------------------------------
	int usleep(useconds_t usec) {
		vTaskDelay(usec / ((TickType_t) 1000000 / configTICK_RATE_HZ));
		return 0;
	}

	//-----------------------------------
	//  nsleep
	//-----------------------------------
	int IRAM_ATTR nsleep(const struct timespec *req, struct timespec *rem) {
		struct timeval start, end;

		if ((req->tv_nsec < 0) || (req->tv_nsec > 999999999)) {
			errno = EINVAL;

			return -1;
		}

		// Get time in msecs
		uint32_t msecs;

		msecs  = req->tv_sec * 1000;
		msecs += (req->tv_nsec + 999999) / 1000000;

		if (rem != NULL) {
			gettimeofday(&start, NULL);
		}

		vTaskDelay(msecs / portTICK_PERIOD_MS);

		if (rem != NULL) {
			rem->tv_sec = 0;
			rem->tv_nsec = 0;

			gettimeofday(&end, NULL);

			uint32_t elapsed = (end.tv_sec - start.tv_sec) * 1000
							+ ((end.tv_usec - start.tv_usec) / 1000000);

			if (elapsed < msecs) {
				if (elapsed > 1000) {
					rem->tv_sec = elapsed / 1000;
					elapsed -= rem->tv_sec * 1000;
					rem->tv_nsec = elapsed * 1000000;
				}
			}
		}
		errno = EINTR;


		return 0;
	}

#endif // 0

	//-----------------------------------
	//  ndelay
	//-----------------------------------
	void ndelay(const timespan_t& req, timespan_t* rem) {
		struct timeval start, end;
		// Get time in msecs
		uint32_t msecs = req.get_total_milliseconds();

		if ( (msecs > 999999999)) {
			errno = EINVAL; /* Invalid argument */
			return;
		}

		gettimeofday(&start, NULL);

		vTaskDelay( req.to_ticks() );

		gettimeofday(&end, NULL);

		uint32_t elapsed = (end.tv_sec - start.tv_sec) * 1000
							+ ((end.tv_usec - start.tv_usec) / 1000000);

		if(rem != NULL)
			*rem = timespan_t(elapsed);
	}
	unsigned int delay_until( timespan_t& tsPreviousWakeTime, const unsigned int& uiTimeIncrement) {
		int _ticks = tsPreviousWakeTime.to_ticks();
		vTaskDelayUntil( (TickType_t*)&_ticks, uiTimeIncrement);

		tsPreviousWakeTime = timespan_t::from_ticks((_ticks));

		errno = EINTR; /* Interrupted system call */

		return _ticks;
	}
	//-----------------------------------
	//  delay
	//-----------------------------------
	void delay(const timespan_t& ts) {
		vTaskDelay( ts.to_ticks() );
	}
}

MN_EXTERNC_END
