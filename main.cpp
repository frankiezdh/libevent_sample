#include <iostream>
#include <event.h>
#include <event2/event.h>
#include <cstring>
#include <iomanip>

using namespace std;

void onTime(evutil_socket_t fd, short event, void *data) {
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    cout << "定时事件: " << put_time(&tm, "%Y-%m-%d %H:%M:%S")<< endl;

    struct timeval tv;
    memset(&tv, 0, sizeof(tv));
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    evtimer_add((struct event *)data, &tv);
}

int main() {
    event_init();

    struct event evTime;
    memset(&evTime, 0, sizeof(evTime));
    evtimer_set(&evTime, onTime, (void *)&evTime);

    struct timeval tv;
    memset(&tv, 0, sizeof(tv));
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    evtimer_add(&evTime, &tv);

    event_dispatch();

    return 0;
}