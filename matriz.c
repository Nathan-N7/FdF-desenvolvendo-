#include "fdf.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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

void	free_matriz(t_matriz	*ptr)
{
	int	i;

	i = 0;
	while (ptr->mapa[i])
	{
		free(ptr->mapa[i]);
		i++;
	}
	free(ptr->mapa);
	free(ptr);
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
	free(num);
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
			free_matriz(ptr);
			return ;
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
}