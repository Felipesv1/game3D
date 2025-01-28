/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:21 by felperei          #+#    #+#             */
/*   Updated: 2025/01/28 13:23:44 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_player_right(t_mlx *mlx)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = mlx->ray->dir_x;
	mlx->ray->dir_x = mlx->ray->dir_x * cos(-ROTATION_SPEED) - mlx->ray->dir_y
		* sin(-ROTATION_SPEED);
	mlx->ray->dir_y = olddir_x * sin(-ROTATION_SPEED) + mlx->ray->dir_y
		* cos(-ROTATION_SPEED);
	oldplane_x = mlx->ray->plane_x;
	mlx->ray->plane_x = mlx->ray->plane_x * cos(-ROTATION_SPEED)
		- mlx->ray->plane_y * sin(-ROTATION_SPEED);
	mlx->ray->plane_y = oldplane_x * sin(-ROTATION_SPEED) + mlx->ray->plane_y
		* cos(-ROTATION_SPEED);
}

void	rotate_player_left(t_mlx *mlx)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = mlx->ray->dir_x;
	mlx->ray->dir_x = mlx->ray->dir_x * cos(ROTATION_SPEED) - mlx->ray->dir_y
		* sin(ROTATION_SPEED);
	mlx->ray->dir_y = olddir_x * sin(ROTATION_SPEED) + mlx->ray->dir_y
		* cos(ROTATION_SPEED);
	oldplane_x = mlx->ray->plane_x;
	mlx->ray->plane_x = mlx->ray->plane_x * cos(ROTATION_SPEED)
		- mlx->ray->plane_y * sin(ROTATION_SPEED);
	mlx->ray->plane_y = oldplane_x * sin(ROTATION_SPEED) + mlx->ray->plane_y
		* cos(ROTATION_SPEED);
}

void	verify_moves(int keycode, t_mlx *game)
{
	if (keycode == KEY_W)
	{
		move_player_forward(game);
		update_map(game);
	}
	else if (keycode == KEY_S)
	{
		move_player_backward(game);
		update_map(game);
	}
	else if (keycode == KEY_RIGHT)
	{
		rotate_player_right(game);
		update_map(game);
	}
	else if (keycode == KEY_LEFT)
	{
		rotate_player_left(game);
		update_map(game);
	}
}

void	game_events(int keycode, t_mlx *game)
{
	verify_moves(keycode, game);
	if (keycode == KEY_A)
	{
		move_player_left(game);
		update_map(game);
	}
	else if (keycode == KEY_D)
	{
		move_player_right(game);
		update_map(game);
	}
}
