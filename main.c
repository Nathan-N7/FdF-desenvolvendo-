#include "fdf.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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
	free_matriz(ptr);
	free(line);
}