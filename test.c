#define _BSD_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
	struct stat *yo;

	yo = (struct stat *)malloc(sizeof(struct stat));
	printf("%d\n", lstat("test.c", yo));
	printf("Hello %u\n", major(yo->st_rdev));
	printf("World %u\n", minor(yo->st_rdev));	
	printf("! %lld\n", yo->st_size);	
	printf("Device number (st_rdev):  major=%ld; minor=%ld\n",
		   (long) major(yo->st_rdev), (long) minor(yo->st_rdev));
	printf("%s\n", ctime(&yo->st_ctime));
	return (0);
}
