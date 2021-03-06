/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:06 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/25 19:39:16 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		double_modulo(double num)
{
	num = (int)num % 360 + num - (int)num;
	return (num);
}

double		angle_adaptater(double angle)
{
	if (angle < 0.0)
		angle += 360.0;
	else if (angle > 360.0)
		angle = double_modulo(angle);
	return (angle);
}
