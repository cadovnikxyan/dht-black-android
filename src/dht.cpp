/*
 * dht.cpp
 *
 *  Created on: 31 июля 2015 г.
 *      Author: alexey
 */

#include "dht.h"

dht::dht() {

}

dht::~dht() {

}
static char buf[512];
static unsigned int counter = 0;
static int failcounter = 0;

void dht::dht_request_data()
{

	int fd=open("/sys/kernel/debug/irq-dht", O_WRONLY);
	sprintf(buf, "%d %u", DHT_GPIO, getpid()); // gpio-dht-handler kernel module
	write(fd, buf, strlen(buf) + 1);
	std::cout<<"dht";
	close(fd);
}





 void dht::dht_handler(int n, siginfo_t *info, void *unused)
{
	 dht wer;
	if (info->si_int == 0) // DHT protocol CRC error
	{
		if (++failcounter > 10)
		{
			printf("Error retrieving data from DHT sensor\n");
			failcounter = 0;
			return;
		}
		usleep(3000000); // wait 3 seconds between attempts
		wer.dht_request_data();
		return;
	}
    socket_tcp sock;
    int socket_num=sock.socket_open();
	float humidity = (float)((info->si_int) >> 16)/10.0; // 2xMSB
	float temperature = (float)((info->si_int) & 0xFFFF)/10.0; //2xLSB
	std::cout<< std::endl<<humidity<<std::endl<<temperature<<std::endl;
	string m_str_buf[2];
	char buffer[32],buffer1[32];
	snprintf(buffer, sizeof(buffer), "%g", humidity);
	snprintf(buffer1, sizeof(buffer), "%g", temperature);
	m_str_buf[0]=buffer;
	m_str_buf[1]=buffer1;
	sock.socket_write(socket_num,m_str_buf[0]+"|"+m_str_buf[1]);
	close(socket_num);
	if ((humidity > 100) || (temperature > 80))
	{
		// Obviously incorrect data
		if (++failcounter > 10)
		{
			printf("Incorrect DHT data with correct CRC. Wow!\n");
			failcounter = 0;
			return;
		}
		usleep(3000); // wait 3 seconds between attempts
		wer.dht_request_data();
		return;
	}

	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	char stime[50];
	strftime (stime, 50,"%a %B %e %H:%M", timeinfo);
}

//////////////////////////////////////////////////////////////////////////

void dht::irq_handler(int n, siginfo_t *info, void *unused)
{
	dht wer;
	//every minute
	counter++;
	wer.dht_request_data();

}

////////////////////////////////////////////////////////////////////////////////

bool dht::init_handler(int timer, int tick, unsigned int timeout)
{
	int fd;
	struct sigaction sig;
	sig.sa_sigaction=dht::irq_handler;
	sig.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigaction(SIG_TIMER_IRQ, &sig, NULL);

	fd = open("/sys/kernel/debug/timer-irq", O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		return false;
	}

	sprintf(buf, "+ %d %u\n+ %d %u %u", timer, tick, timer, timeout, getpid());

	if(write(fd, buf, strlen(buf) + 1) < 0)
	{
		perror("write");
		close(fd);
		return false;
	}

	close(fd);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool dht::remove_handler(int timer)
{
	int fd;

	fd = open("/sys/kernel/debug/timer-irq", O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		return false;
	}

	sprintf(buf, "- %d", timer);

	if(write(fd, buf, strlen(buf) + 1) < 0)
	{
		perror("write");
		close(fd);
		return false;
	}

	close(fd);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
