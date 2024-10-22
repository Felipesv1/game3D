/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:21 by felperei          #+#    #+#             */
/*   Updated: 2024/10/22 16:59:10 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void move_player_forward(t_mlx *mlx)
{

	// if (mlx->dt->map[(int)(mlx->rc->posX + mlx->ray->dirX * PLAYER_SPEED)][(int)(mlx->rc->posY)])
		mlx->ply->plyr_x += mlx->ray->dirX * PLAYER_SPEED;
	// if (mlx->dt->map[(int)mlx->rc->posX][(int)(mlx->rc->posY + mlx->ray->dirY * PLAYER_SPEED)])
		mlx->ply->plyr_y += mlx->ray->dirY * PLAYER_SPEED;
}

void move_player_backward(t_mlx *mlx)
{
	// if (mlx->dt->map[(int)(mlx->rc->posX - mlx->ray->dirX * PLAYER_SPEED)][(int)(mlx->rc->posY)])
mlx->ply->plyr_y -= mlx->ray->dirY * PLAYER_SPEED;
// if (mlx->dt->map[(int)mlx->rc->posX][(int)(mlx->rc->posY - mlx->ray->dirY * PLAYER_SPEED)])
mlx->ply->plyr_x -= mlx->ray->dirX * PLAYER_SPEED;
}

void rotate_player_right(t_mlx *mlx) // rotate the player
{
  double oldDirX = mlx->ray->dirX ;
      mlx->ray->dirX  = mlx->ray->dirX  * cos(-ROTATION_SPEED) - mlx->ray->dirY * sin(-ROTATION_SPEED);
      mlx->ray->dirY = oldDirX * sin(-ROTATION_SPEED) +  mlx->ray->dirY * cos(-ROTATION_SPEED);
      double oldPlaneX = mlx->ray->planeX;
      mlx->ray->planeX = mlx->ray->planeX * cos(-ROTATION_SPEED) - mlx->ray->planeY * sin(-ROTATION_SPEED);
      mlx->ray->planeY = oldPlaneX * sin(-ROTATION_SPEED) + mlx->ray->planeY * cos(-ROTATION_SPEED);
}

void rotate_player_left(t_mlx *mlx) // rotate the player
{
  double oldDirX = mlx->ray->dirX ;
      mlx->ray->dirX  = mlx->ray->dirX  * cos(ROTATION_SPEED) - mlx->ray->dirY * sin(ROTATION_SPEED);
      mlx->ray->dirY = oldDirX * sin(ROTATION_SPEED) +  mlx->ray->dirY * cos(ROTATION_SPEED);
      double oldPlaneX = mlx->ray->planeX;
      mlx->ray->planeX = mlx->ray->planeX * cos(ROTATION_SPEED) - mlx->ray->planeY * sin(ROTATION_SPEED);
      mlx->ray->planeY = oldPlaneX * sin(ROTATION_SPEED) + mlx->ray->planeY * cos(ROTATION_SPEED);
}


int keypress(int keycode, t_mlx *game)
{
	if (keycode == ESC || keycode == KEY_Q)
		ft_exit(game);
	game_events(keycode, game);
	return (0);
}

void game_events(int keycode, t_mlx *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		move_player_forward(game);
		update_map(game);
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		move_player_backward(game);
		update_map(game);

	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		// game->ply->rot = 1;
		rotate_player_left(game);
		update_map(game);

	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		// game->ply->rot = -1;
		rotate_player_right(game);
		update_map(game);
	}
}
