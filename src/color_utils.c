/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   color_utils.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: vdurand <vdurand@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2025/01/14 03:57:34 by val   #+##+# */
/*   Updated: 2025/01/14 17:43:15 by vdurand  ###   ########.fr   */
/**/
/* ************************************************************************** */

#include "fdf.h"

int	argb_to_int(t_argb argb)
{
	return (argb.a << 24 | argb.r << 16 | argb.g << 8 | argb.b);
}

void	argb_set(t_argb *argb, float r, float g, float b)
{
	argb->a = 0;
	argb->r = r * 255;
	argb->g = g * 255;
	argb->b = b * 255;
}

t_argb	hsv_to_argb(t_hsv hsv)
{
	float	c;
	float	x;
	float	m;
	t_argb	rgb;

	c = hsv.v * hsv.s;
	x = c * (1 - fabsf(fmodf(hsv.h / 60.0f, 2) - 1));
	m = hsv.v - c;
	if (hsv.h >= 0 && hsv.h < 60)
		argb_set(&rgb, c + m, x + m, m);
	else if (hsv.h >= 60 && hsv.h < 120)
		argb_set(&rgb, x + m, c + m, m);
	else if (hsv.h >= 120 && hsv.h < 180)
		argb_set(&rgb, m, c + m, x + m);
	else if (hsv.h >= 180 && hsv.h < 240)
		argb_set(&rgb, m, x + m, c + m);
	else if (hsv.h >= 240 && hsv.h < 300)
		argb_set(&rgb, x + m, m, c + m);
	else
		argb_set(&rgb, c + m, m, x + m);
	return (rgb);
}
