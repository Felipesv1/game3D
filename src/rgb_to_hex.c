/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:54:30 by vboxuser          #+#    #+#             */
/*   Updated: 2025/01/28 11:11:25 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	clean_rgb(t_mlx *mlx)
{
	free(mlx->ply);
	free(mlx->ray);
	free(mlx->rc);
	free(mlx->dt->map_texts->text_no);
	free(mlx->dt->map_texts->text_so);
	free(mlx->dt->map_texts->text_we);
	free(mlx->dt->map_texts->text_ea);
	free(mlx->dt->map_texts->floor);
	free(mlx->dt->map_texts->ceiling);
	free(mlx->dt->map_texts);
	free_matrix(mlx->dt->backup);
	free_matrix(mlx->dt->map2d);
	free_matrix(mlx->dt->map_copy);
	free(mlx->dt);
	destroy_image(mlx);
	mlx_destroy_window(mlx->mlx_p, mlx->win);
	mlx_destroy_display(mlx->mlx_p);
	free(mlx->textures->north);
	free(mlx->textures->south);
	free(mlx->textures->west);
	free(mlx->textures->east);
	free(mlx->textures);
	free(mlx->mlx_p);
}

static int	verify_digits(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	control_error_rgb(char **rgb, t_mlx mlx)
{
	free_matrix(rgb);
	printf("Error\nInvalid RGB format\n");
	clean_rgb(&mlx);
}

void	is_valid_rgb(char *str, t_mlx mlx)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		control_error_rgb(rgb, mlx);
		exit(1);
	}
	if (!verify_digits(rgb))
	{
		control_error_rgb(rgb, mlx);
		exit(1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		control_error_rgb(rgb, mlx);
		exit(1);
	}
	free_matrix(rgb);
}

int	rgb_to_hex(char *texture)
{
	int		r;
	int		g;
	int		b;
	int		color;
	char	**rgb;

	rgb = ft_split(texture, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_matrix(rgb);
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	color = (r << 16) + (g << 8) + b;
	free_matrix(rgb);
	return (color);
}
