/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   color_utils.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: vdurand <vdurand@student.42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2025/01/10 02:24:10 by val   #+##+# */
/*   Updated: 2025/01/13 15:27:38 by vdurand  ###   ########.fr   */
/**/
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
    t_argb rgb;
    unsigned char region, remainder, p, q, t;
    
    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }
    
    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 
    
    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;
    
    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }
    
    return rgb;
}

