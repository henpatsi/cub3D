/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:46:15 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/12 17:42:53 by ixu              ###   ########.fr       */
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
