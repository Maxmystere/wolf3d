/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/04/27 12:58:22 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <fcntl.h>
# include <dirent.h>

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.1415926535897932
# define PI180 0.01745329251
# define TOANGLE 57.2957795131
# define BLUE_SKY 0x4559a8ff
# define RED_WALL 0xb30000ff
# define PINK_FLOOR 0xdcc8c8ff
# define INT_MAX 2147483647
# define TTFWOLF "ressources/font/wolfenstein.ttf"
# define TTFIMPACT "ressources/font/impact.ttf"
# define WALLBLUE "ressources/textures/wall_blue.xpm"
# define WALL "ressources/textures/wall.xpm"
# define GOLD "ressources/textures/plaqueor.xpm"
# define TEST "ressources/textures/test.xpm"

typedef struct			s_vct2
{
	int					x;
	int					y;
}						t_vct2;

typedef struct			s_fvct2
{
	float				x;
	float				y;
}						t_fvct2;

/*
** Snap var behaviour
** 0 = center of object is its left;
** 1 = center of object is its center;
** 2 = center of object is its right;
** 3 = under the object before + (pos) px
*/

typedef struct			s_sloc
{
	SDL_Rect			area;
	int					snapx;
	int					snapy;
	t_fvct2				pos;
}						t_sloc;

typedef struct			s_btn
{
	t_sloc				loc;
	SDL_Texture			*txture;
	SDL_Color			fgcolor;
	SDL_Color			bgcolor;
	char				*data;
	SDL_PixelFormat		*format;
}						t_btn;

typedef struct			s_slid
{
	t_sloc				loc;
	SDL_Texture			*txture;
	int					*val;
	int					min;
	int					max;
	SDL_Rect			grip;
	SDL_Color			fgcolor;
	SDL_Color			bgcolor;
}						t_slid;

typedef struct			s_font
{
	TTF_Font			*s32;
	TTF_Font			*s64;
	TTF_Font			*s128;
}						t_font;

/*
** m_status behaviour
** 0 = gamemode
** 1 = Show main menu
** 2 = show map menu
*/

typedef struct			s_ui
{
	t_font				fonts;
	t_btn				btnarr[10];
	t_btn				btnmap[11];
	t_btn				btnopt[11];
	t_slid				slidopt[5];
	t_slid				*currslid;
	int					m_status;
}						t_ui;

typedef struct			s_ray
{
	t_fvct2				inter_v;
	t_fvct2				inter_h;
	t_fvct2				ratio;
	float				angle;
	float				hor;
	float				ver;
	int					polar;
}						t_ray;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	t_vct2				size;
	t_vct2				m_pos;
	SDL_Texture			*txture;
	uint32_t			*screen;
	t_tab				keys;
	SDL_PixelFormat		*format;
}						t_sdl;

typedef struct			s_wall
{
	SDL_Surface			*surf;
	uint32_t			*txture;
	int					w;
	int					h;
}						t_wall;

typedef	struct			s_wolf
{
	t_sdl				sdl;
	t_ui				ui;
	char				**map;
	t_vct2				map_size;
	t_fvct2				pos;
	double				rot;
	int					fov;
	t_wall				wall[4];
	unsigned long		timestamp;
	float				d_scrn;
}						t_wolf;

t_wolf					*wolf_init();
void					*sdldata_quit(t_sdl **data);
int						sdl_start(t_wolf *wolf, const char *title);
void					sdl_showscreen(t_sdl *sdl);
int						wolf_parseur(t_wolf *wolf, char *filename);
int						prog_quit(t_wolf *wolf);
void					btn_click(t_wolf *wolf, int x, int y);
t_btn					add_start_button(t_wolf *wolf);
t_btn					add_mapmenu_button(t_wolf *wolf);
t_btn					add_map_button(t_wolf *wolf, const char *str);
t_btn					add_wolf_button(t_wolf *wolf);
t_btn					add_opt_button(t_wolf *wolf);
t_btn					add_quit_button(t_wolf *wolf, const char *str);
void					draw_menu(t_wolf *wolf);
int						load_map_btns(t_wolf *wolf);
void					update_slider_txt(t_wolf *wolf, t_slid *slid);
t_slid					add_fov_slider(t_wolf *wolf);
void					draw_slid(t_wolf *wolf, t_slid *tmp);
int						event_handler(t_wolf *wolf);
int						loop_hook(t_wolf *wolf);
int						key_press(int key, t_wolf *wolf);
int						key_release(int key, t_wolf *wolf);
int						mouse_press(int button, int x, int y, t_wolf *wolf);
int						mouse_release(int button, int x, int y, t_wolf *wolf);
int						mouse_move(int x, int y, t_wolf *wolf);
void					raycasting(t_wolf *wolf);
float					float_modulo(float num);
double					angle_adaptater(double angle);
void					print_image(SDL_Surface *png);
float					ver_detection(t_wolf *wolf, t_ray *ray);
float					hor_detection(t_wolf *wolf, t_ray *ray);
double					iswall(t_wolf *wolf, t_fvct2 inter);
void					draw_column(t_wolf *wolf, t_ray ray, int num);
unsigned int			color_rgb(uint8_t r, uint8_t g, uint8_t b);
void					wolf_clear_map(t_wolf *wolf);
int						map_check(t_wolf *wolf, char *filename);
int						row_verif(t_wolf *wolf, char *row);
void					*listdel(t_list **list);
t_vct2					*vct2_value(t_vct2 *vct2, int x, int y);
char					**tab_new(int y);
void					lst_del_node(t_list **node);
#endif
