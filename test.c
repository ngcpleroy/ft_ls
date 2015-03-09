#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>

struct test
{
	char	i;
	void	(*function)(char*);
};

void	foo(char *str);
void	bar(char *str);

const struct test ft_test[2] =
{
	{0, foo},
	{1, bar}
};

void	foo(char *str)
{
	printf("HELLO %s\n", str);
}

void	bar(char *str)
{
	printf("hello %s\n", str);
}

int		main(void)
{
	time_t now;
	time_t test;
	struct stat sb;
	char i = 0;

	now = time(NULL);
	lstat("./test.c", &sb);
	while (i < 2)
	{
		ft_test[(int)i].function("world");
		i++;
	}
	printf("%ld\n", now);
	printf("%ld\n", sb.st_mtime);
	printf("%ld\n", now - sb.st_mtime);
	printf("%s\n",ctime(&now));
	return (1);
}
