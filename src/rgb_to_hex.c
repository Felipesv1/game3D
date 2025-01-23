/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:54:30 by vboxuser          #+#    #+#             */
/*   Updated: 2025/01/16 23:06:01 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	is_valid_rgb(char *str, t_mlx mlx)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_matrix(rgb);
		printf("Error\nInvalid RGB format\n");
		cleanup(&mlx);
		exit(1);
	}
	if (!verify_digits(rgb))
	{
		free(rgb[0]);
		free(rgb[1]);
		free(rgb[2]);
		free(rgb);
		printf("Error\nInvalid RGB format\n");
		cleanup(&mlx);
		exit(1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free(rgb[0]);
		free(rgb[1]);
		free(rgb[2]);
		free(rgb);
		printf("Error\nInvalid RGB format\n");
		cleanup(&mlx);
		exit(1);
	}
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
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
