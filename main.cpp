#include <iostream>
#include <cstring>
#include <iomanip>
#include <event.h>
#include <event2/thread.h>


using namespace std;

void onTime(evutil_socket_t fd, short event, void *data) {
    (void)fd;
    (void)event;

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
    evthread_use_pthreads();

    struct event_base *base = event_base_new();
    if (base == NULL) {
        cout << "event base new FAILED" << endl;
        return -1;
    }

    struct event time_event;
    memset(&time_event, 0, sizeof(time_event));
    evtimer_set(&time_event, onTime, (void *)&time_event);
    event_base_set(base, &time_event);

    struct timeval tv;
    memset(&tv, 0, sizeof(tv));
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    evtimer_add(&time_event, &tv);

    event_base_dispatch(base);

    event_base_free(base);

    return 0;
}