/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:21 by felperei          #+#    #+#             */
/*   Updated: 2025/01/14 13:18:48 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_exit(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->dt->map2d[i])
		free(mlx->dt->map2d[i++]);
	free(mlx->dt->map2d);
	free(mlx->dt->map_texts->text_no);
	free(mlx->dt->map_texts->text_so);
	free(mlx->dt->map_texts->text_we);
	free(mlx->dt->map_texts->text_ea);
	free(mlx->dt->map_texts->floor);
	free(mlx->dt->map_texts->ceiling);
	free(mlx->dt->map_texts);
	mlx_destroy_image(mlx->mlx_p, mlx->img_ptr);
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	mlx_destroy_display(mlx->mlx_p);
	printf("Game closed\n");
	exit(0);
}
