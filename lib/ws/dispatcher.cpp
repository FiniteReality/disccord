// Copyright (c) 2014 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights 
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
// copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.
//

// MODIFIED BY: sedruk

#include <stdexcept>

#include <disccord/ws/dispatcher.hpp>

namespace disccord
{
    namespace ws
    {
        namespace internal
        {
            dispatcher::dispatcher()
            { }

            dispatcher::~dispatcher()
            { }

            unsigned int dispatcher::add_listener(unsigned int event_id, std::function<void ()> cb)
            {
                if (!cb)
                {
                    throw std::invalid_argument("dispatcher::add_listener: No callbak provided.");
                }
                
                std::lock_guard<std::mutex> lock(mutex);

                unsigned int listener_id = ++last_listener;
                listeners.insert(std::make_pair(event_id, std::make_shared<listener<>>(listener_id, cb)));

                return listener_id;       
            }

            unsigned int dispatcher::on(unsigned int event_id, std::function<void ()> cb)
            {
                return add_listener(event_id, cb);
            }

            void dispatcher::remove_listener(unsigned int listener_id)
            {
                std::lock_guard<std::mutex> lock(mutex);

                auto i = std::find_if(listeners.begin(), listeners.end(), [&] (std::pair<const unsigned int, std::shared_ptr<listenerbase>> p) {
                    return p.second->id == listener_id;
                });
                if (i != listeners.end())
                {
                    listeners.erase(i);
                }
                else
                {
                    throw std::invalid_argument("dispatcher::remove_listener: Invalid listener id.");
                }
            }
        } // namespace internal
    } // namespace ws
} // namespace disccord
