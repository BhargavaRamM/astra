// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.
#ifndef ASTRA_SIGNAL_LISTENER_H
#define ASTRA_SIGNAL_LISTENER_H

#include "astra_signal.hpp"
#include <cstddef>

namespace astra {

    template<typename TSignal>
    class signal_listener
    {
    public:
        using callback_id = std::size_t;
        using callback_type = typename TSignal::callback_type;

        signal_listener(TSignal signal, callback_type callback)
            : signal_(signal),
              callback_(callback)
        {
            signal += callback_;
        }

        ~signal_listener()
        {
            signal_ -= id_;
        }

    private:
        callback_id id_;
        std::function<callback_type> callback_;
        TSignal signal_;
    };

}

#endif /* ASTRA_SIGNAL_LISTENER_H */
