#include <iostream>
#include <cstring>
#include <event.h>
#include <event2/thread.h>


using namespace std;

void on_time(evutil_socket_t fd, short event, void *data) {
    (void) fd;
    (void) event;
    (void) data;

    time_t raw_time = time(NULL);
    cout << "[" << pthread_self() << "]"
         << "定时事件: " << ctime(&raw_time);
}

void *time_thread(void *arg) {
    (void) arg;

    struct event_base *base = event_base_new();
    if (base == NULL) {
        cout << "event base new FAILED" << endl;
        return NULL;
    }

    struct event time_event;
    memset(&time_event, 0, sizeof(time_event));
    event_set(&time_event, -1, EV_PERSIST, on_time, NULL);
    event_base_set(base, &time_event);

    struct timeval tv;
    memset(&tv, 0, sizeof(tv));
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    evtimer_add(&time_event, &tv);

    event_base_dispatch(base);

    event_base_free(base);

    return NULL;
}

#define THREAD_MAX_NUM 2

int main() {
    evthread_use_pthreads();

    pthread_t threads[THREAD_MAX_NUM];
    memset(threads, 0, sizeof(threads));

    for (int i = 0; i < THREAD_MAX_NUM; ++i) {
        (void) pthread_create(&threads[i], NULL, time_thread, NULL);
    }

    for (int i = 0; i < THREAD_MAX_NUM; ++i) {
        (void) pthread_join(threads[i], NULL);
    }

    return 0;
}