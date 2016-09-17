#ifndef EVENT_H_
#define EVENT_H_

#include <boost/signals2.hpp>

template <class T>
using Signal = boost::signals2::signal<void (const T&)>;

template <class T>
using SignalSlotType = typename Signal<T>::slot_type;

typedef boost::signals2::connection Connection;

template <class T>
class Event
{
  public:
    
    static void fire( const T& d ) { Event<T>::sig_(d); }

    static Connection connect( const SignalSlotType<T>& slot )
    {
      return sig_.connect(slot);
    }

  private:
    static Signal<T> sig_;

};

template <class T>
Signal<T> Event<T>::sig_;

#endif
