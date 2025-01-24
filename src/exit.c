/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:21 by felperei          #+#    #+#             */
/*   Updated: 2025/01/24 14:45:12 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_p, mlx->img_ptr);
	mlx_destroy_image(mlx->mlx_p, mlx->textures->north->ptr);
	mlx_destroy_image(mlx->mlx_p, mlx->textures->south->ptr);
	mlx_destroy_image(mlx->mlx_p, mlx->textures->west->ptr);
	mlx_destroy_image(mlx->mlx_p, mlx->textures->east->ptr);
}

int	ft_exit(t_mlx *mlx)
{
	free_matrix(mlx->dt->map2d);
	free_matrix(mlx->dt->map_copy);
	free(mlx->dt->map_texts->text_no);
	free(mlx->dt->map_texts->text_so);
	free(mlx->dt->map_texts->text_we);
	free(mlx->dt->map_texts->text_ea);
	free(mlx->dt->map_texts->floor);
	free(mlx->dt->map_texts->ceiling);
	free(mlx->dt->map_texts);
	free(mlx->dt);
	free(mlx->ray);
	free(mlx->rc);
	free(mlx->ply);
	destroy_image(mlx);
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	mlx_destroy_display(mlx->mlx_p);
	free(mlx->textures->north);
	free(mlx->textures->south);
	free(mlx->textures->west);
	free(mlx->textures->east);
	free(mlx->textures);
	free(mlx->mlx_p);
	printf("Game closed\n");
	exit(0);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}