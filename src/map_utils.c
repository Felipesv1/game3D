/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontes <fmontes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:56:51 by felperei          #+#    #+#             */
/*   Updated: 2025/01/23 15:11:20 by fmontes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void verify_one_player(t_mlx *mlx)
{
		if (mlx->ply->n_player != 1)
	{
		printf("Error: player not find\n");
		cleanup(mlx);
		exit(1);
	}
}
void	find_player(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (mlx->dt->map2d[x])
	{
		y = 0;
		while (mlx->dt->map2d[x][y])
		{
			if (mlx->dt->map2d[x][y] == 'N' || mlx->dt->map2d[x][y] == 'S'
				|| mlx->dt->map2d[x][y] == 'W' || mlx->dt->map2d[x][y] == 'E')
			{
				mlx->ply->plyr_x = x + 0.5;
				mlx->ply->plyr_y = y + 0.5;
				handle_player_direction(mlx, x, y);
			}
			y++;
		}
		x++;
	}
	verify_one_player(mlx);
}



void	is_format_valid(char *av, t_mlx mlx)
{
	int	i;

	if (!av)
		return ;
	i = 0;
	while (av[i])
		i++;
	i -= 1;
	if (av[i] == 'b' && av[i - 1] == 'u' && av[i - 2] == 'c' && av[i
			- 3] == '.')
		return ;
	else
	{
		printf("Error: invalid file format\n");
		cleanup(&mlx);
		exit(1);
	}
}


static char	*read_file_to_str(int fd)
{
	char	buffer[1024];
	ssize_t	bytes_read;
	char	*holder_map;
	char	*temp;

	holder_map = malloc(1);
	if (!holder_map)
		return (NULL);
	holder_map[0] = '\0';
	while (1)
	{
		bytes_read = read(fd, buffer, 1023);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(holder_map, buffer);
		if (!temp)
		{
			free(holder_map);
			return (NULL);
		}
		free(holder_map);
		holder_map = temp;
	}
	return (holder_map);
}

char	**read_map(char *path)
{
	int		fd;
	char	*holder_map;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	holder_map = read_file_to_str(fd);
	close(fd);
	if (!holder_map)
		return (NULL);
	map = ft_split(holder_map, '\n');
	free(holder_map);
	return (map);
}