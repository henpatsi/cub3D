/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:46:15 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/10 14:47:16 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	normalize_vector(t_vector	*vector)
{
	if (vector->y == 0 || vector->x == 0)
		return ;
	vector->x *= NORMALIZE_VALUE;
	vector->y *= NORMALIZE_VALUE;
}