/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:54:42 by hpatsi            #+#    #+#             */
/*   Updated: 2024/04/22 13:04:41 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		ft_putstr_fd("Use: ./cub3D path_to_map\n", 2);
		return (1);
	}

	map.mlx = mlx_init(10, 10, "cub3D", false);
	if (map.mlx == 0)
	{
		ft_putstr_fd("Failed to init mlx\n", 2);
		return (1);
	}

	if (load_map(&map, argv[1]) == -1)
		return (1);

	ft_printf("map f color = %d, %d, %d\n", (map.floor_color >> 24) & 0xFF, (map.floor_color >> 16) & 0xFF, (map.floor_color >> 8) & 0xFF);
	ft_printf("map c color = %d, %d, %d\n", (map.ceiling_color >> 24) & 0xFF, (map.ceiling_color >> 16) & 0xFF, (map.ceiling_color >> 8) & 0xFF);

	

	mlx_terminate(map.mlx);

	return (0);
}
