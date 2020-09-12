#include "timer.h"
#define IDT_TIMER_ID 0x1100

LRESULT Timer::message(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(uMsg == WM_TIMER && wParam == id)
    {
        std::list<TimerEvent*>::iterator ite;
        TimerEvent * timer;

        for(ite = timerEvent.begin(); ite != timerEvent.end(); ite++)
        {
            timer = *ite;
            timer->timer(*this);
        }
        return 0;
    }
    return Control::message(uMsg, wParam, lParam);
}

Timer::Timer()
{
    registerClass("Timer");
    createControl(0, 0, "Timer", "", 0, 0, 1, 1, NULL);
    enabled = false;
    interval = 1000;
    enabled = true;
    id = IDT_TIMER_ID;
    SetTimer(getHandle(), id, interval, NULL);
}

Timer::~Timer()
{
    KillTimer(getHandle(), id);
}

void Timer::setInterval(unsigned int interval)
{
    this->interval = interval;
    if(enabled)
        id = SetTimer(getHandle(), id, interval, NULL);
}

unsigned int Timer::getInterval()
{
    return interval;
}

void Timer::addTimerEvent(TimerEvent* timer)
{
    timerEvent.push_back(timer);
}

bool Timer::isEnabled()
{
    return enabled;
}

void Timer::setEnabled(bool enabled)
{
    if(this->enabled == enabled)
        return;
    this->enabled = enabled;
    if(enabled)
        id = SetTimer(getHandle(), id, interval, NULL);
    else
        KillTimer(getHandle(), id);
}

