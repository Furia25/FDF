/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 02:24:10 by val               #+#    #+#             */
/*   Updated: 2025/01/10 12:57:06 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	argb_to_int(t_argb argb)
{
	return (argb.a << 24 | argb.r << 16 | argb.g << 8 | argb.b);
}

/* t_hsv argb_to_hsv(t_argb argb)
{
	t_vect3	rgb_ratio;
	t_hsv hsv;
	float max;
	
    rgb_ratio.x = argb.r / 255.0;
    rgb_ratio.y = argb.g / 255.0;
    rgb_ratio.z = argb.b / 255.0;
	max = fmaxf(r, fmaxf(g, b));
    if (max - fminf(r, fminf(g, b)) == 0)
        hsv.h = 0;
    else if (max == r)
        hsv.h = 60 * ((rgb_ratio.y - rgb_ratio.z) / delta);
    else if (max == g)
        hsv.h = 60 * ((rgb_ratio.z - rgb_ratio.x) / delta + 2);
    else
        hsv.h = 60 * ((rgb_ratio.x - rgb_ratio.y) / delta + 4);
    if (max == 0)
        hsv.s = 0;
    else
        hsv.s = max - fminf(r, fminf(g, b)) / max;
    hsv.v = max;
    if (hsv.h < 0)
        hsv.h += 360;
    return (hsv);
} */

t_argb hsv_to_argb(t_hsv hsv)
{
	t_argb	rgb;
	t_vect3 cxm;

    cxm.x = hsv.v * hsv.s; 
    cxm.y = cxm.x * (1 - fabsf(fmodf(hsv.h / 60.0, 2) - 1));
    cxm.z = hsv.v - cxm.x ;
    if (hsv.s == 0)
    	return ((t_argb){255, (char)hsv.v * 255, (char)hsv.v * 255, (char)hsv.v * 255});
    if (hsv.h >= 0 && hsv.h < 60)
		rgb = (t_argb) {255, cxm.x, cxm.y, 0};
    else if (hsv.h >= 60 && hsv.h < 120)
		rgb = (t_argb) {255, cxm.y, cxm.x, 0};
    else if (hsv.h >= 120 && hsv.h < 180)
		rgb = (t_argb) {255, 0, cxm.x, cxm.y};
    else if (hsv.h >= 180 && hsv.h < 240)
		rgb = (t_argb) {255, 0, cxm.y, cxm.x};
    else if (hsv.h >= 240 && hsv.h < 300)
		rgb = (t_argb) {255, cxm.y, 0, cxm.x};
    else
		rgb = (t_argb) {255, cxm.x, 0, cxm.y};
    rgb.r = rgb.r + cxm.z;
    rgb.g = rgb.g + cxm.z;
    rgb.b = rgb.b + cxm.z;
    return (rgb);
}
