/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:09:33 by fmontes           #+#    #+#             */
/*   Updated: 2025/01/28 10:58:19 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_line_height(t_mlx *mlx, double perp_wall_dist)
{
	mlx->dt->line_height = (int)(S_H / perp_wall_dist);
	mlx->dt->draw_start = -(mlx->dt->line_height) / 2 + S_H / 2;
	if (mlx->dt->draw_start < 0)
		mlx->dt->draw_start = 0;
	mlx->dt->draw_end = (mlx->dt->line_height) / 2 + S_H / 2;
	if (mlx->dt->draw_end >= S_H)
		mlx->dt->draw_end = S_H - 1;
}

double	calculate_delta_dist(double value)
{
	if (value == 0)
	{
		return (1e30);
	}
	else
	{
		return (fabs(1 / value));
	}
}

int	calculate_tex_x(t_mlx *mlx)
{
	double	wall_x;

	if (mlx->rc->side == 0)
	{
		wall_x = mlx->rc->pos_y + mlx->rc->perp_wall_dist * mlx->rc->raydir_y;
	}
	else
	{
		wall_x = mlx->rc->pos_x + mlx->rc->perp_wall_dist * mlx->rc->raydir_x;
	}
	return ((int)((int)(wall_x * TEX_WIDTH) % TEX_WIDTH));
}

static void	get_ray_dir(t_mlx *mlx, int x)
{
	mlx->rc->raydir_x = mlx->ray->dir_x + mlx->ray->plane_x * (2 * x
			/ (double)S_W - 1);
	mlx->rc->raydir_y = mlx->ray->dir_y + mlx->ray->plane_y * (2 * x
			/ (double)S_W - 1);
}

void	raycasting(t_mlx *mlx)
{
	int	map_x;
	int	map_y;
	int	x;

	map_x = 0;
	map_y = 0;
	x = 0;
	mlx->rc->pos_x = mlx->ply->plyr_x;
	mlx->rc->pos_y = mlx->ply->plyr_y;
	while (x++ < S_W)
	{
		get_ray_dir(mlx, x);
		mlx->rc->hit = 0;
		map_x = (int)mlx->rc->pos_x;
		map_y = (int)mlx->rc->pos_y;
		mlx->rc->delta_dist_x = calculate_delta_dist(mlx->rc->raydir_x);
		mlx->rc->delta_dist_y = calculate_delta_dist(mlx->rc->raydir_y);
		calculate_step_and_side_dist(mlx->rc, map_x, map_y);
		perform_dda(&map_x, &map_y, mlx->rc, mlx);
		mlx->rc->perp_wall_dist = calculate_perp_wall_dist(map_x, map_y,
				mlx->rc);
		calculate_line_height(mlx, mlx->rc->perp_wall_dist);
		mlx->dt->tex_x = calculate_tex_x(mlx);
		draw_buffer(mlx, x);
	}
}
