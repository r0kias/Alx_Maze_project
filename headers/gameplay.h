#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

typedef struct villains
{
	int hp;
	int pos_x;
	int pos_y;
	int pos_dir;
	bool alert_state;
}villain_t;

/*typedef struct inventory
{
	size_t *size;
	char **objects;
}inventory_t*/

typedef struct weapons
{
	int weapPos_x;
	int weapPos_y;
	int weapPos_dir;
	int shootRange;
	int attack;
}weapon_t;

// Fonctions

weapon_t weapGenerator();
int shoot(weapon_t weapon);
void DrawBullets(SDL_Renderer * ren, weapon_t weapon);

// Fonctions villain
villain_t MoveEnnemy(villain_t ennemy);
int attack_player(weapon);

#endif
