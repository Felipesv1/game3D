/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:38:17 by felperei          #+#    #+#             */
/*   Updated: 2025/01/28 15:58:20 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	int		start_line;
	int		rows;
	char	**ret;

	start_line = 6;
	rows = count_rows(data, start_line);
	ret = allocate_map(data, start_line, rows);
	return (ret);
}

void	size_map(t_data *dt)
{
	int	rows;
	int	cols;
	int	current_col;
	int	max_row_index;

	rows = 0;
	cols = 0;
	max_row_index = 0;
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
			max_row_index = rows;
		}
		rows++;
	}
	dt->max_row = max_row_index;
	dt->rows = rows;
	dt->cols = cols;
}

void	update_map(t_mlx *mlx)
{
	raycasting(mlx);
	mlx_put_image_to_window(mlx->mlx_p, mlx->win, mlx->img_ptr, 0, 0);
}
