#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <lua.hpp>
#include "Player.h"

void check_for_errors();
void init_opengl();
void init_lua();
static int move_to(lua_State *L);
void update_player( Player *player );
void keydown(unsigned char key, int x, int y);
