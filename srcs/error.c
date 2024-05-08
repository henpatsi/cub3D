/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:35:01 by hpatsi            #+#    #+#             */
/*   Updated: 2024/05/08 11:00:01 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	return_error(char *message)
{
	if (message != 0)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	return (-1);
}

int	exit_error(char *message)
{
	if (message != 0)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(1);
}
