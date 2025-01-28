/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:38:17 by felperei          #+#    #+#             */
/*   Updated: 2025/01/28 10:37:57 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* char	**read_map(char *path)
{
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;
	char	*holder_map;
	char	*temp;
	char	**map;
	char	buffer[1024];
	ssize_t	bytes_read;
	char	*holder_map;
	char	*temp;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
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
		temp = holder_map;
		holder_map = ft_strjoin(holder_map, buffer);
		free(temp);
		if (!holder_map)
			return (NULL);
	}
	close(fd);
	map = ft_split(holder_map, '\n');
	free(holder_map);
	return (map);
} */

/* char	**get_map(char **data)
{
	int		i;
	int		j;
	int		rows;
	char	**map;
	int		start_line;
	int		rows;

	start_line = 6;
	rows = 0;
	while (data[start_line + rows])
		rows++;
	map = malloc(sizeof(char *) * (rows + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		map[i] = malloc(sizeof(char) * (ft_strlen(data[start_line + i]) + 1));
		if (!map[i])
			return (NULL);
		j = 0;
		while (data[start_line + i][j])
		{
			map[i][j] = data[start_line + i][j];
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[rows] = NULL;
	return (map);
} */
static int	count_rows(char **data, int start_line)
{
	int	rows;

	rows = 0;
	while (data[start_line + rows])
		rows++;
	return (rows);
}

static char	**allocate_map(char **data, int start_line, int rows)
{
	char	**map;
	int		i;
	int		j;

	map = malloc(sizeof(char *) * (rows + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		map[i] = malloc(sizeof(char) * (ft_strlen(data[start_line + i]) + 1));
		if (!map[i])
			return (NULL);
		j = 0;
		while (data[start_line + i][j])
		{
			map[i][j] = data[start_line + i][j];
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[rows] = NULL;
	return (map);
}

char	**get_map(char **data)
{
	int	start_line;
	int	rows;

	start_line = 6;
	rows = count_rows(data, start_line);
	return (allocate_map(data, start_line, rows));
}

// int	**copy_char_to_int(char **char_matrix, t_data *dt)
// {
// 	int	**int_matrix;
// 	int	i;
// 	int	j;

// 	i = 0;
// 	int_matrix = (int **)malloc(dt->rows * sizeof(int *));
// 	if (!int_matrix)
// 		return (NULL);
// 	while (i < dt->rows)
// 	{
// 		int_matrix[i] = (int *)malloc(dt->cols * sizeof(int));
// 		if (!int_matrix[i])
// 			return (NULL);
// 		j = 0;
// 		while (j < dt->cols)
// 		{
// 			if (ft_isdigit(char_matrix[i][j]))
// 				int_matrix[i][j] = char_matrix[i][j] - '0';
// 			else
// 				int_matrix[i][j] = 1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (int_matrix);
// }

void	size_map(t_data *dt)
{
	int	rows;
	int	cols;
	int	current_col;

	rows = 0;
	cols = 0;
	while (dt->map2d[rows])
	{
		current_col = 0;
		while (dt->map2d[rows][current_col])
		{
			current_col++;
		}
		if (current_col > cols)
		{
			cols = current_col;
		}
		rows++;
	}
	dt->rows = rows;
	dt->cols = cols;
}

void	update_map(t_mlx *mlx)
{
	raycasting(mlx);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, mlx->img_ptr, 0, 0);
}
// int	size_map(t_data *dt)
// {
// 	int	i;

// 	dt->w_map = ft_strlen(dt->map2d[0]);
// 	i = 0;
// 	while (dt->map2d[i])
// 		i++;
// 	dt->h_map = i;
// 	if (dt->w_map != dt->h_map)
// 		return (1);
// 	return (0);
// }