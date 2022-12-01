#include "raycaster.h"

/**
* initial_calc - project ray
* @rc: struct for raycast
* @x: position
*/
void initial_calc(t_raycaster *rc, int x)
{
	double camera_x;

	camera_x = 2 * x / (double)(WIN_X) - 1;
	rc->ray_dir_x = rc->player_dir_x + rc->player_plane_x * camera_x;
	rc->ray_dir_y = rc->player_dir_y + rc->player_plane_y * camera_x;
	rc->map_x = (int)(rc->player_pos_x);
	rc->map_y = (int)(rc->player_pos_y);
	rc->delta_dist_x = sqrt(1 + pow(rc->ray_dir_y, 2) / pow(rc->ray_dir_x, 2));
	rc->delta_dist_y = sqrt(1 + pow(rc->ray_dir_x, 2) / pow(rc->ray_dir_y, 2));
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->player_pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->player_pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->player_pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->player_pos_y) * rc->delta_dist_y;
	}
}

/**
* perform_dda - detect if the ray hit wall
* @rc: struct for raycast
*/
void perform_dda(t_raycaster *rc)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (worldMap[rc->map_x][rc->map_y] > 0)
			hit = 1;
	}
}


/**
* calc_wall_height - calc th height of the wall
* @rc: struct for raycast
*/
void calc_wall_height(t_raycaster *rc)
{
	int line_height;

	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - rc->player_pos_x + (1 - rc->step_x) /
										2) / rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - rc->player_pos_y + (1 - rc->step_y) /
										2) / rc->ray_dir_y;
	line_height = (int)(WIN_Y / rc->perp_wall_dist);
	rc->draw_start = -line_height / 2 + WIN_Y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = line_height / 2 + WIN_Y / 2;
	if (rc->draw_end >= WIN_Y)
		rc->draw_end = WIN_Y - 1;
}

/**
* draw_vert_line - draw wall
* @sdl: sruct for handle sdl
* @rc: struct for raycast
* @x: position
*/
void draw_vert_line(t_sdl *sdl, t_raycaster *rc, int x)
{
	SDL_Color color;

	color = apply_night_effect(select_wall_color(rc->map_x, rc->map_y),
										rc->perp_wall_dist);

	if (rc->side == 1)
	{
		color.r /= 2;
		color.g /= 2;
		color.b /= 2;
	}
	SDL_SetRenderDrawColor(sdl->renderer, color.r, color.g, color.b,
									SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(sdl->renderer, x, rc->draw_start, x, rc->draw_end);
}

/**
* raycaster - assemble all function for raycasting
* @sdl: struct for handle sdl
* @rc: struct for raycast
*/
void raycaster(t_sdl *sdl, t_raycaster *rc)
{
	SDL_bool done;
	int x;

	done = SDL_FALSE;
	while (!done)
	{
		for (x = 0; x < WIN_X; x++)
		{
			initial_calc(rc, x);
			perform_dda(rc);
			calc_wall_height(rc);
			draw_vert_line(sdl, rc, x);
		}
		render_frame(sdl);
		if (handle_events(rc) != 0)
			done = SDL_TRUE;
	}
}
