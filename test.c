#include <stdio.h>

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
	char i = 0;

	while (i < 2)
	{
		ft_test[(int)i].function("world");
		i++;
	}
	return (1);
}
