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
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <stdio.h>
#include <esp_attr.h>

#include "mutex.hpp"

namespace mofw {
  //-----------------------------------
  //  construtor
  //-----------------------------------
  basic_mutex::basic_mutex() : basic_semaphore() {

    #if( configSUPPORT_STATIC_ALLOCATION == 1 )
      m_pSpinlock = xSemaphoreCreateMutexStatic(&m_SemaphoreBasicBuffer);
    #else
      m_pSpinlock = xSemaphoreCreateMutex();
    #endif


    if (m_pSpinlock) {
      unlock();
    } else {
      MN_THROW_LOCK_EXP(ERR_MUTEX_CANTCREATEMUTEX);
    }
  }

  basic_mutex::basic_mutex(const basic_mutex& other)
  	: basic_semaphore(other) { }

  //-----------------------------------
  //  deconstrutor
  //-----------------------------------
  basic_mutex::~basic_mutex() {
    if (m_pSpinlock != NULL)
      vSemaphoreDelete(m_pSpinlock);
  }

  //-----------------------------------
  //  lock
  //-----------------------------------
  int basic_mutex::lock(unsigned int timeout) {
    BaseType_t success;

    if (xPortInIsrContext()) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        success = xSemaphoreTakeFromISR( m_pSpinlock, &xHigherPriorityTaskWoken );
        if(xHigherPriorityTaskWoken)
          _frxt_setup_switch();
    } else {
      success = xSemaphoreTake((QueueHandle_t)m_pSpinlock, timeout);
    }

    if(success != pdTRUE ) {
      return ERR_MUTEX_LOCK;
    }
    m_isLocked = true;
    return ERR_MUTEX_OK;
  }

  //-----------------------------------
  //  unlock
  //-----------------------------------
  int basic_mutex::unlock() {
    BaseType_t success;

    if (xPortInIsrContext()) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        success = xSemaphoreGiveFromISR( m_pSpinlock, &xHigherPriorityTaskWoken );
        if(xHigherPriorityTaskWoken)
          _frxt_setup_switch();
    } else {
        success = xSemaphoreGive(m_pSpinlock);
    }

    if(success != pdTRUE ) {
      return ERR_MUTEX_UNLOCK;
    }
    m_isLocked = false;
    return ERR_MUTEX_OK;
  }
}
