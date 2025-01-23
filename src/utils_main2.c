/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:42:40 by vboxuser          #+#    #+#             */
/*   Updated: 2025/01/16 23:12:19 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	validate_path(t_mlx mlx)
{
	if (check_path(mlx.dt->map_texts->text_no) == 1)
	{
		printf("Error na imagem NO\n");
		cleanup(&mlx);
		exit(1);
	}
	else if (check_path(mlx.dt->map_texts->text_so) == 1)
	{
		printf("Error na imagem SO\n");
		cleanup(&mlx);
		exit(1);
	}
	if (check_path(mlx.dt->map_texts->text_we) == 1)
	{
		printf("Error na imagem WE\n");
		cleanup(&mlx);
		exit(1);
	}
	if (check_path(mlx.dt->map_texts->text_ea) == 1)
	{
		printf("Error na imagem EA\n");
		cleanup(&mlx);
		exit(1);
	}
}

void	validate_map(char **map, t_mlx mlx)
{
	int i = 0;
	int j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'F')
			{
				if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1] || map[i
					- 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j
					- 1] == ' ' || map[i][j + 1] == ' ')
				{
					printf("Error: map is not closed\n");
					cleanup(&mlx);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}