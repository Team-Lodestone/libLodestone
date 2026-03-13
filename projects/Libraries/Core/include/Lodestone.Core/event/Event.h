/** @file Event.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_EVENT_H
#define LODESTONE_EVENT_H
#include <functional>
#include <cstdint>
#include <limits>
#include <format>
#include <stdexcept>

#include "Lodestone.Core/event/Cancellable.h"
#include "Lodestone.Common/registry/Identifier.h"

namespace lodestone::core::event {
  using FunctionHandle = unsigned int;

  template <typename... Args>
  class Event {
  public:
    using Handler = std::function<void(Args...)>;

    static constexpr FunctionHandle MAX_SUBSCRIBERS = std::numeric_limits<FunctionHandle>::max();

    struct Subscriber {
      FunctionHandle id;
      Handler handler;
    };

    template <std::invocable<Args...> Func>
    FunctionHandle subscribe(Func &&handler) {
      if (this->m_nextId == MAX_SUBSCRIBERS) // how the fuck do you manage this
        throw std::length_error(std::format("The maximum number of subscribers to this event has been reached ({}/{})", this->m_listeners.size(), MAX_SUBSCRIBERS));

      this->m_listeners.push_back(Subscriber {
        this->m_nextId,
        std::forward<Func>(handler)
      });

      return this->m_nextId++;
    }

    bool unsubscribe(FunctionHandle id) {
      return std::erase_if(this->m_listeners, [&id](const Subscriber &subscriber) {
        return subscriber.id == id;
      }) > 0;
    }

    void notify(Args... args) {
      for (Subscriber listener : this->m_listeners) {
        std::invoke(listener.handler, std::forward<Args>(args)...);
      }
    }

    // I wanted it to be like C#'s events
    template <std::invocable<Args...> Func>
    FunctionHandle operator+=(Func &&handler) {
      return this->subscribe(std::forward<Func>(handler));
    }

    bool operator-=(const FunctionHandle id) {
      return this->unsubscribe(id);
    }

  protected:
    std::vector<Subscriber> m_listeners;

    FunctionHandle m_nextId = 0;
  };

  template <typename... Args>
  using CancellableEvent = Event<Cancellable &, Args...>;
}

#endif // LODESTONE_EVENT_H