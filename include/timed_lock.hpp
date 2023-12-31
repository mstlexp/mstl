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
#ifndef MINLIB_ESP32_TIMED_LOCK_
#define MINLIB_ESP32_TIMED_LOCK_

#include "config.hpp"

    #include "convar.hpp"
    #include "convar_task.hpp"
    #include "autolock.hpp"

namespace mofw {
    /**
     * \ingroup lock
     */
    template<class TLOCK>
    class basic_timed_lock {
    public:
        /**
         * Construtor
         */
        basic_timed_lock()
            : m_cv(), m_lockObject(), m_bLocked(false)  { }
        /**
         * Deconstrutor
         */
        ~basic_timed_lock() {
            basic_autolock<TLOCK> lock(m_lockObject);
        }
        /**
         *  Lock the timed mutex.
         *
         * @param task The current canvar Task
         * @param Timeout How long to wait to get the Lock until giving up. (default = 0xffffffffUL)
         */
        void lock(basic_convar_task& task, unsigned int timeout = MN_THREAD_CONFIG_TIMEOUT_MUTEX_DEFAULT) {
            basic_autolock<TLOCK> lock(m_lockObject);
            while (m_bLocked) {
                task.wait(m_cv, m_mutex, timeout);
            }
            m_bLocked = true;
        }
        /**
         * Unlock the timed Mutex.
         *
         * @param signal_childs On notify the task, send a notify to the child task?
         */
        void unlock(bool signal_childs = true) {
            basic_autolock<TLOCK> lock(m_lockObject);
            m_bLocked = false;
            m_cv.signal(signal_childs);
        }
    protected:
            convar_t    m_cv;
            TLOCK       m_lockObject;
            bool        m_bLocked;
    };
}

#endif //MINLIB_ESP32_TIMED_LOCK_
