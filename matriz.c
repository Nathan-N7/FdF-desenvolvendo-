#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_matriz
{
	int	x;
	int	y;
	int	**mapa;
}	t_matriz;

int	count_x(char	*str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			count++;
		while (str[i] != ' ' && str[i] != '\0')
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
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

int	*mapa_line(char	*line, int x)
{
	char	**num;
	int	*linem;
	int	i;
	
	i = 0;
	linem = malloc(sizeof(int) * x);
	num = ft_split(line, ' ');
	if (num == NULL || linem == NULL)
		return (NULL);
	while  (num[i] != NULL)
	{
		linem[i] = ft_atoi(num[i]);
		free(num[i]);
		i++;
	}
	free(num[i]);
	return (linem);
}

void	creat_matriz(t_matriz *ptr, int fd)
{
	char	*line;
	int	i;
	
	line = get_next_line(fd);
	ptr->mapa = (int **)malloc(sizeof(int *) * ptr->y);
	if (ptr->mapa == NULL)
		return ;	
	i = 0;
	while (line != NULL)
	{
		ptr->mapa[i] = mapa_line(line, ptr->x);
		if (ptr->mapa[i] == NULL)
		{
			free(line);
			return ;
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

int	main()
{
	int	fd;
	char	*line;
	int	i;
	int	k;
	t_matriz	*ptr;

	i = 0;
	k = 0;
	ptr  = malloc(sizeof(t_matriz));
	fd = open("42.fdf", O_RDONLY);
	if (fd < 0 || ptr == NULL)
		return (-1);

	line = get_next_line(fd);
	ptr->x = count_x(line);
	ptr->y = count_y(fd);
	fd = open("42.fdf", O_RDONLY);
	creat_matriz(ptr, fd);
	
	while (i < ptr->y)
	{
		while (k < ptr->x)
		{
			printf("%d ", ptr->mapa[i][k]);
			k++;
		}
		printf("\n");
		k = 0;
		i++;
	}
}
