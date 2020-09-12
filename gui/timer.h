#ifndef _TIMER_H_
#define _TIMER_H_
#include <list>
#include "control.h"

class TimerEvent
{
public:
    virtual void timer(Object& sender) = 0;
};

class Timer: protected Control
{
private:
    unsigned int interval;
    unsigned int id;
    bool enabled;
    std::list<TimerEvent*> timerEvent;
protected:
    LRESULT message(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
    Timer();
    ~Timer();
    void setInterval(unsigned int interval);
    unsigned int getInterval();
    void addTimerEvent(TimerEvent* timer);
    bool isEnabled();
    void setEnabled(bool enabled);
};

#endif

