
#include "dht.h"

int main(int argc, char* argv[])

{

	dht weather;
	string str;

	std::cout<< "start"<<std::endl;

	int timer = TIMER_TIMER;
	int tick = 1000*1000; // 1 sec
	unsigned int timeout = 1000*1000*2; // 2 sec
	sigset_t sigset;
	siginfo_t siginfo;

	struct sigaction sig;
	sig.sa_sigaction =dht::dht_handler;
	sig.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigaction(SIG_DHT_IRQ, &sig, NULL);

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);	//	Ctrl+C
	sigprocmask(SIG_BLOCK, &sigset, NULL);

	weather.dht_request_data();

	if (!weather.init_handler(timer,tick,timeout))
		{
			std::cout<<"Error initializing timer"<<std::endl;
			return -1;
		}

	while (1)
	{
		sigwaitinfo(&sigset, &siginfo);

		if(siginfo.si_signo == SIGINT)
		{
			break;
		}
	}

	weather.remove_handler(timer);

	return 0;
}
