/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_directions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontes <fmontes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:02:50 by fmontes           #+#    #+#             */
/*   Updated: 2025/01/23 15:14:45 by fmontes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_direction_north(t_mlx *mlx)
{
	mlx->ray->dir_x = -1.0;
	mlx->ray->dir_y = 0.0;
	mlx->ray->plane_x = 0.0;
	mlx->ray->plane_y = 0.66;
	mlx->ply->n_player++;
}

void	set_direction_south(t_mlx *mlx)
{
	mlx->ray->dir_x = 1.0;
	mlx->ray->dir_y = 0.0;
	mlx->ray->plane_x = 0.0;
	mlx->ray->plane_y = -0.66;
	mlx->ply->n_player++;
}

void	set_direction_east(t_mlx *mlx)
{
	mlx->ray->dir_x = 0.0;
	mlx->ray->dir_y = 1.0;
	mlx->ray->plane_x = 0.66;
	mlx->ray->plane_y = 0.0;
	mlx->ply->n_player++;
}

void	set_direction_west(t_mlx *mlx)
{
	mlx->ray->dir_x = 0.0;
	mlx->ray->dir_y = -1.0;
	mlx->ray->plane_x = -0.66;
	mlx->ray->plane_y = 0.0;
	mlx->ply->n_player++;
}

void	handle_player_direction(t_mlx *mlx, int x, int y)
{
	if (mlx->dt->map2d[x][y] == 'N')
		set_direction_north(mlx);
	else if (mlx->dt->map2d[x][y] == 'S')
		set_direction_south(mlx);
	else if (mlx->dt->map2d[x][y] == 'E')
		set_direction_east(mlx);
	else if (mlx->dt->map2d[x][y] == 'W')
		set_direction_west(mlx);
	mlx->dt->map2d[x][y] = '0';
}
