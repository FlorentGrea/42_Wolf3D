/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 01:52:29 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/30 05:41:59 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define RESX 1280
# define RESY 720

# define MAP1 "maps/map01"
# define MAP2 "maps/map02"
# define MAP3 "maps/map03"
# define SKY "textures/sky.xpm"

# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

typedef struct		s_ixy
{
	int				x;
	int				y;
}					t_ixy;

typedef struct		s_dxy
{
	double			x;
	double			y;
}					t_dxy;

typedef struct		s_map
{
	int				x;
	int				y;
	int				**map;
}					t_map;

typedef struct		s_img
{
	void			*im;
	char			*imc;
	int				imlen;
	int				bpp;
	int				endi;
}					t_img;

typedef struct		s_ray
{
	double			cam;
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			dist;
	t_dxy			disd;
}					t_ray;

typedef struct		s_pxl
{
	char			*choice;
	int				fd;
	char			**line;
	t_ixy			cmap;
	int				**map;
	int				check;

	void			*mlx;
	void			*win;
	int				color;

	t_img			img;
	t_img			sky;

	t_ray			r;
	int				wall;
	int				hit;
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			rplane;
	t_ixy			rmap;
	t_ixy			step;

	int				wstart;
	int				wend;
	int				rh;

	double			speed;
	int				up;
	int				down;
	int				left;
	int				right;
}					t_pxl;

void				wolf3d_parsing(t_pxl *p, char *line);
int					wolf3d_key_press(int keycode, t_pxl *p);
int					wolf3d_key_release(int keycode, t_pxl *p);
int					wolf3d_launcher(t_pxl *p);
void				wolf3d_fill_columns(t_pxl *p, int x);
void				wolf3d_ray_study(t_pxl *p);
void				wolf3d_move(t_pxl *p);
void				wolf3d_setup(t_pxl *p);
void				wolf3d_put_map(t_pxl *p);
void				wolf3d_error(char *c);

#endif
