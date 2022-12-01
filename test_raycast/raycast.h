#ifndef __RAYCAST_H__
#define __RAYCAST_H__

/* structures */
typedef struct walls {
	int a[2];
	int b[2];
} wall;

typedef struct player_point {
	int a;
	int b;

} player;

/* functions */
bool endpoint_check(player p, wall w);

#endif
