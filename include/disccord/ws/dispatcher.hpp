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

#ifndef _ws_dispatcher_hpp_
#define _ws_dispatcher_hpp_

#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <list>
#include <algorithm>
#include <string>

#include <disccord/ws/event.hpp>

namespace disccord
{
    namespace ws
    {
        namespace internal
        {
            class dispatcher
            {
            public:
                
                dispatcher();

                virtual ~dispatcher();

                unsigned int add_listener(unsigned int event_id, std::function<void ()> cb);
                
                template <typename... Args>
                unsigned int add_listener(unsigned int event_id, std::function<void (Args...)> cb)
                {
                    if (!cb)
                    {
                        throw std::invalid_argument("dispatcher::add_listener: No callbak provided.");
                    }

                    std::lock_guard<std::mutex> lock(mutex);

                    unsigned int listener_id = ++last_listener;
                    listeners.insert(std::make_pair(event_id, std::make_shared<listener<Args...>>(listener_id, cb)));

                    return listener_id;        
                }

                template<typename LambdaType>
                unsigned int add_listener(unsigned int event_id, LambdaType lambda) {
                    return add_listener(event_id, make_function(lambda));
                }

                unsigned int on(unsigned int event_id, std::function<void ()> cb);

                template <typename... Args>
                unsigned int on(unsigned int event_id, std::function<void (Args...)> cb)
                {
                    return add_listener(event_id, cb);
                }

                template<typename LambdaType>
                unsigned int on(unsigned int event_id, LambdaType lambda) {
                    return on(event_id, make_function(lambda));
                }

                void remove_listener(unsigned int listener_id);

                template <typename... Args>
                void emit(disccord::ws::event event_id, Args... args)
                {
                    std::list<std::shared_ptr<listener<Args...>>> handlers;

                    {
                        std::lock_guard<std::mutex> lock(mutex);

                        auto range = listeners.equal_range(static_cast<unsigned int>(event_id));
                        handlers.resize(std::distance(range.first, range.second));
                        std::transform(range.first, range.second, handlers.begin(), [] (std::pair<const unsigned int, std::shared_ptr<listenerbase>> p) {
                            auto l = std::dynamic_pointer_cast<listener<Args...>>(p.second);
                            if (l)
                            {
                                return l;
                            }
                            else
                            {
                                throw std::logic_error("dispatcher::emit: Invalid event signature.");
                            }
                        });
                    }

                    for (auto& h : handlers)
                    {
                        h->cb(args...);
                    }        
                }

                // http://stackoverflow.com/a/21000981
                template <typename T>
                struct function_traits
                   : public function_traits<decltype(&T::operator())>
                {};

                template <typename ClassType, typename ReturnType, typename... Args>
                struct function_traits<ReturnType(ClassType::*)(Args...) const> {
                   typedef std::function<ReturnType (Args...)> f_type;
                };

                template <typename L> 
                typename function_traits<L>::f_type make_function(L l){
                  return (typename function_traits<L>::f_type)(l);
                }

            private:
                struct listenerbase
                {
                    listenerbase() {}

                    listenerbase(unsigned int i)
                    : id(i) {}

                    virtual ~listenerbase() {}

                    unsigned int id;
                };

                template <typename... Args>
                struct listener : public listenerbase
                {
                    listener() {}

                    listener(unsigned int i, std::function<void (Args...)> c)
                    : listenerbase(i), cb(c) {}

                    std::function<void (Args...)> cb;
                };

                std::mutex mutex;
                unsigned int last_listener;
                std::multimap<unsigned int, std::shared_ptr<listenerbase>> listeners;

                dispatcher(const dispatcher&) = delete;  
                const dispatcher& operator = (const dispatcher&) = delete;
            };
        } //namespace internal
    } // namespace ws
} // namespace disccord

#endif /* _ws_dispatcher_hpp_ */
