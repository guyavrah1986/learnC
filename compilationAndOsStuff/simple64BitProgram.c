#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>


void* sampleThreadFunc(void* arg)
{
	const char* funcName = "sampleThreadFunc -";
	printf("%s start\n", funcName);
	unsigned long iterationNum = 0;
	//const char* threadName = (const char*)arg;

	
	while (iterationNum < 100000)
	{
		++iterationNum;
		printf("%s iteration:%lu", funcName, iterationNum);
		unsigned int secondsToSleep = 60;
		printf("%s sleeping for %d seconds\n", funcName, secondsToSleep);
		int res = sleep(secondsToSleep);
		if (res != 0)
		{
			printf("%s had issue sleeping in between iterations, aborting thread", funcName);
			return NULL;
		}
	}
	
	
	printf("%s got to final iteration ,terminating thread gracefully\n", funcName);
	return NULL;
}

int main(int argc, char** argv)
{
	const char* funcName = "main -";
	printf("%s start\n", funcName);
	pthread_t threadId;
	const char* threadName = "backgroundThread";
	printf("%s before creating background thread\n", funcName);
	int retCode = pthread_create(&threadId, NULL, &sampleThreadFunc, (void *)threadName);
	printf("%s created background thread\n", funcName);
	int err = pthread_join(threadId, NULL);
	// check if joining is sucessful
	if (err)
	{
		printf("Failed to join Thread:%s", threadName);
		return err;
	}
	
	printf("%s end\n", funcName);
	return 0;
}
