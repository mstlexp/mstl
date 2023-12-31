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
#ifndef MINLIB_ESP32_CONVAR_
#define MINLIB_ESP32_CONVAR_


#include "config.hpp"
#include "mutex.hpp"
#include "autolock.hpp"
#include "autounlock.hpp"

#include <list>

namespace mofw {

        /**
         * Forward declaration. We need to prevent a circular dependency
         * between the basic_convar_task class and the basic_condition_variable class.
         *
         * @ingroup condition-varible
         */
        class basic_task;

        /**
         *  Class implementation of condition variable
         *
         *  A condition variable isn't really a variable. It's a list
         *  of threads.
         *
         *  The design here is that a basic_convar_task "waits", and a condition_variable
         *  "signals". This affects where the public interfaces reside.
         */
        class basic_condition_variable : MN_DEFAULT_CLASS {
            /**
             *  The basic_task class and the basic_condition_variable class are interdependent.
             *  If we allow the basic_task class to access the internals of the
             *  basic_condition_variable, we can reduce the public interface which is a
             *  good thing.
             */
            friend class basic_task;
        public:
            /**
             *  Constructor to create a condition variable.
             */
            basic_condition_variable();

            /**
             *  Signal a thread waiting on this condition_variable (FIFO list).
             */
            void signal();

            /**
             * Signal all threads waiting on this condition_variable.
             */
            void broadcast();

            inline void notify_one() noexcept { // wake up one waiter
				signal();
			}

			inline void notify_all() noexcept { // wake up all waiters
				broadcast();
			}

            int wait(mofw::mutex_t& mx, TickType_t timeOut);

        private:
            /**
             *  Internal helper function to queue a basic_convar_task to
             *  this condition_variable's wait list.
             *
             * @param thread The basic_task to add to the waiting list
             */
            void add_list(basic_task *thread);
        protected:
            /**
             *  Protect the internal condition_variable state.
             */
            mutex_t                            m_mutex;
            /**
             *  Implementation of a wait list of Threads.
             */
            std::list<basic_task*>    m_waitList;
        };

        using convar_t = basic_condition_variable;
}
#endif

