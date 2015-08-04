/*
 * dht.h
 *
 *  Created on: 31 июля 2015 г.
 *      Author: alexey
 */

#ifndef DHT_H_
#define DHT_H_
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "socket_tcp.h"
#include <string>
#include "rwfile.h"

#define SIG_TIMER_IRQ	43
#define SIG_DHT_IRQ		44
#define TIMER_TIMER 1
#define DHT_TIMER 2
#define DHT_GPIO 23


class dht {
public:
	dht();
	~dht();

void dht_request_data();
bool remove_handler(int timer);
bool init_handler(int timer, int tick, unsigned int timeout);
static void irq_handler(int n, siginfo_t *info, void *unused);
static void dht_handler(int n, siginfo_t *info, void *unused);

};

#endif /* DHT_H_ */
