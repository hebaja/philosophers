#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

int main()
{
	sem_t	*sem;

	sem_unlink("/my_semaphore");
	sem = sem_open("/my_semaphore", O_CREAT, 0644, 1);
	if (sem == SEM_FAILED)
	{
		perror("sem_error");
		exit(EXIT_FAILURE);
	}
	sem_wait(sem);
	printf("semaphore acquired\n");
	usleep(9000000);
	sem_post(sem);

	sem_close(sem);
	sem_unlink("/my_semaphore");

	return (0);
}
