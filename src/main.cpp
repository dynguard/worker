#include <iostream>
#include <fstream>
#include <test.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define MAX_THREAD_LIMIT 200

using namespace std;

struct thread_args
{
	int thread_id;
	std::string message;
};

void *start_vm_life(void *threadarg)
{
	struct thread_args *my_data;

	my_data = (struct thread_args *) threadarg;
	ostringstream machine_name;
	machine_name << "malanize-windows-xp-" << my_data->thread_id;

	pid_t tid = syscall(SYS_gettid);

	cout << "I am TID: " << tid << " and thread id: " << my_data->thread_id << "\n";

	sleep(rand()%50);
	cout << "Thread: " << tid <<  " with thread_id: " << my_data->thread_id << " is exiting\n";
	pthread_exit(NULL);


//	cout << "Going to grab information for machine: malanize-windows-xp-" << my_data->thread_id << "\n";

//	test machine;
//	machine.get_vm_status(machine_name.str());
//	machine.print_machine_details();
	sleep(10000);
}

int main()
{
	//Grab the number of machines that each test should be running from MySQL

	int rc;
	int no_machines = 2;


	pthread_t * threads = (pthread_t*)malloc(sizeof(pthread_t)*MAX_THREAD_LIMIT);
	cout << "Size of threads: " << sizeof(threads) << endl;

	while (1)
	{
		cout << "Size of no_machines: " << no_machines << endl;

		struct thread_args td[no_machines];

		for (int i = 0; i < no_machines; i++)
		{

			//Here we want to check that thread[i] != 0 which will indicate a closed thread
			//I also need to ensure that we keep track of threads[i] in a different array somehow

			if (threads[i])
			{
				int ret = pthread_kill(threads[i], 0);

				//if ret == 3 that is because the thread died
				if (ret == 3)
				{
					cout << "Thread_id: " << i << " has exited!" << endl;
					//Mark that thread_id as exited
					pthread_detach(threads[i]);
					threads[i] = 0;
					//continue;
				}
				else
				{
					cout << "Thread_id: " << i << " is still running\n";
					continue;
				}
			}

			cout << "Spawning new thread with id: " << i << endl;

			td[i].thread_id = i;
			td[i].message = "Hello";

			rc = pthread_create(&threads[i], NULL, start_vm_life, (void *)&td[i]);

			if (rc)
			{
				cout << "Error creating thread, " << rc << "\n";
				exit(-1);
			}


			sleep(1);
		}

//		for (int i = 0; i < int((sizeof(threads)/sizeof(*threads))); i++)
//		{
//			//cout << "Thread at position: " << i << " contains: " << threads[i] << "\n";
//		}

		if (no_machines == MAX_THREAD_LIMIT)
		{
			sleep(10);
		}


		no_machines+=2;
	}

	return 0;
}



