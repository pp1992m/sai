/*
    This file is part of Leela Zero.
    Copyright (C) 2017-2019 Gian-Carlo Pascutto and contributors

    Leela Zero is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Leela Zero is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Leela Zero.  If not, see <http://www.gnu.org/licenses/>.

    Additional permission under GNU GPL version 3 section 7

    If you modify this Program, or any covered work, by linking or
    combining it with NVIDIA Corporation's libraries from the
    NVIDIA CUDA Toolkit and/or the NVIDIA CUDA Deep Neural
    Network library and/or the NVIDIA TensorRT inference library
    (or a modified version of those libraries), containing parts covered
    by the terms of the respective license agreement, the licensors of
    this Program grant you additional permission to convey the resulting
    work.
*/

#ifndef SMP_H_INCLUDED
#define SMP_H_INCLUDED

#include "config.h"

#include <atomic>

namespace SMP {
    int get_num_cpus();

    class Mutex {
    public:
        Mutex();
        ~Mutex() = default;
        friend class Lock;
    private:
        std::atomic<bool> m_lock;
    };

    class Lock {
    public:
        explicit Lock(Mutex & m);
        ~Lock();
        void lock();
        void unlock();
    private:
        Mutex * m_mutex;
        bool m_owns_lock{false};
    };
}

// Avoids accidentally creating a temporary
#define LOCK(mutex, lock) SMP::Lock lock((mutex))

#endif
