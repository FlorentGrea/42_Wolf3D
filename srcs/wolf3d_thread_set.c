/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_thread_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 07:04:08 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/30 05:43:09 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			wolf3d_setup(t_pxl *p)
{
	int			win_x;
	int			win_y;

	win_x = RESX;
	win_y = RESY / 2;
	p->pos.x = 1.501;
	p->pos.y = 1.501;
	p->dir.x = 1;
	p->dir.y = 0;
	p->rplane.x = 0;
	p->rplane.y = -0.80;
	p->speed = 0.1;
	p->sky.im = mlx_xpm_file_to_image(p->mlx, SKY, &win_x, &win_y);
	p->sky.imc = mlx_get_data_addr(p->sky.im, &p->sky.bpp, &p->sky.imlen, \
			&p->sky.endi);
}

static void		wolf3d_hud(t_pxl p)
{
	int			x;
	int			y;
	int			i;

	x = 20;
	y = 600;
	i = 0x00FF00;
	mlx_string_put(p.mlx, p.win, x, y + 32, i, "Mvt   : wasd / Arrows");
	mlx_string_put(p.mlx, p.win, x, y + 48, i, "Speed :    + / -     ");
	mlx_string_put(p.mlx, p.win, x, y + 64, i, "Reset :      0       ");
	mlx_string_put(p.mlx, p.win, x, y + 80, i, "Quit  :     esc      ");
}

int				wolf3d_launcher(t_pxl *p)
{
	if (p->check == 0)
		return (0);
	wolf3d_move(p);
	wolf3d_ray_study(p);
	wolf3d_put_map(p);
	mlx_clear_window(p->mlx, p->win);
	mlx_put_image_to_window(p->mlx, p->win, p->sky.im, 0, 0);
	mlx_put_image_to_window(p->mlx, p->win, p->img.im, 0, 0);
	wolf3d_hud(*p);
	return (0);
}
