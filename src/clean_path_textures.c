/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_path_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:51:02 by felperei          #+#    #+#             */
/*   Updated: 2025/01/30 10:01:36 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_path_no(t_mlx mlx)
{
	printf("Error\n");
	mlx_destroy_image(mlx.mlx_p, mlx.textures->south->ptr);
	mlx_destroy_image(mlx.mlx_p, mlx.textures->west->ptr);
	mlx_destroy_image(mlx.mlx_p, mlx.textures->east->ptr);
	clean_path(&mlx);
}

void	clean_path_so(t_mlx mlx)
{
	printf("Error\n");
	mlx_destroy_image(mlx.mlx_p, mlx.textures->north->ptr);
	mlx_destroy_image(mlx.mlx_p, mlx.textures->west->ptr);
	mlx_destroy_image(mlx.mlx_p, mlx.textures->east->ptr);
	clean_path(&mlx);
}

void	clean_path_we(t_mlx mlx)
{
	printf("Error\n");
	mlx_destroy_image(mlx.mlx_p, mlx.textures->south->ptr);
	mlx_destroy_image(mlx.mlx_p, mlx.textures->east->ptr);
	mlx_destroy_image(mlx.mlx_p, mlx.textures->north->ptr);
	clean_path(&mlx);
}

void	clean_path_ea(t_mlx mlx)
{
	printf("Error\n");
	mlx_destroy_image(mlx.mlx_p, mlx.textures->north->ptr);
	mlx_destroy_image(mlx.mlx_p, mlx.textures->west->ptr);
	mlx_destroy_image(mlx.mlx_p, mlx.textures->south->ptr);
	clean_path(&mlx);
}
