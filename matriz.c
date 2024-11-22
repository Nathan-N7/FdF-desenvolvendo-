#include "gnl/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

typedef struct s_matriz
{
	void	*x;
	void	*y;
	void	**z;
}	t_matriz;

int	count_x(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			count++;
		while (str[i] != ' ')
			i++;
		i++;
	}
	return (count);
}
int	count_y(int	fd)
{
	char	*line;
	int	i;
	
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{	
		line = get_next_line(fd);
		i++;
	}
	return (i - 1);
}

t_matriz	**matriz(int fd)
{
	int	x;
	int	y;

	x = count_x(fd);
	y = count_y(fd);

	
}

int	main()
{
	int	fd = open("test.txt", O_RDONLY);
	printf("%d", count_y(fd));
}
