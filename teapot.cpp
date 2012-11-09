#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "teapot.h"

using namespace std;

/* Globals */

int timeSinceStart;
int deltaTime;
int oldTimeSinceStart = 0;

lua_State* L;

vector<Player*> enemies;
Player *playerOne;


void
display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    /* Transforms */

    if ( (timeSinceStart%500) == 0 ) {
        for ( Player *player : enemies ) {
            update_player( player );
        }
    }

    for ( Player *player : enemies ) {
        glPushMatrix();
        glTranslatef( player->pos_x, player->pos_y, player->pos_z );
        glScalef( player->scale_x, player->scale_y, player->scale_z );
        /* Draw object(s) */
        glutWireSphere(1.0f, 5, 5);
        glPopMatrix();
    }


    glPushMatrix();
    glTranslatef( playerOne->pos_x, playerOne->pos_y, playerOne->pos_z );
    glScalef( playerOne->scale_x, playerOne->scale_y, playerOne->scale_z );

    /* Draw object(s) */
    glutWireTeapot(1.0f);
    glPopMatrix();

    /* Error checking */
    check_for_errors();

    /* Redraw */
    glutSwapBuffers();
    glutPostRedisplay();
}

void
idle()
{
    timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;
}

void
update_player( Player *player )
{
    /* the function name */
    lua_getglobal(L, "updatePlayer");

    /* Pass current player pointer */
    lua_pushlightuserdata(L, (void*)player);

    /* Pass current position */
    lua_pushnumber(L, player->pos_x);
    lua_pushnumber(L, player->pos_y);
    lua_pushnumber(L, player->pos_z);

    /* call function with 4 arguments, return 0 result */
    lua_call(L, 4, 0);
}

void
check_for_errors()
{
    GLenum errCode;
    const GLubyte *errString;
    errCode = glGetError();
    if (errCode) {
        errString = gluErrorString(errCode);
        std::cout << errString;
    }
}

void
initEnemies()
{
    float x = -0.8;
    for ( float y = 0.8; y > 0.4; y -= 0.15 ) {
        while ( x < 0.8 ) {
            enemies.push_back( new Player(x, y, 0.0) );
            x += 0.15;
        }
        x = -0.8;
    }
}

void
init_opengl(int argc, char **argv)
{
    /* default basic window init */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Teapot!");
    glutKeyboardFunc(keydown);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    initEnemies();
    playerOne = new Player(0.0, -0.8, 0.0);
    playerOne->updateScale(0.1, 0.1, 0.1);

}

void
init_lua()
{
    /* initialize Lua */
    L = lua_open();

    /* load Lua base libraries */
    luaL_openlibs(L);

    /* register our function */
    lua_register(L, "move_to", move_to);

    /* run the script */
    luaL_dofile(L, "update_player.lua");
}


static int
move_to(lua_State *L)
{
    /* Fetch player pointer */
    Player *updatePlayer = (Player*)lua_touserdata(L, 1);

    /* iterate through table */
    updatePlayer->pos_z = lua_tonumber(L, -1);
    lua_pop(L, 1);
    updatePlayer->pos_y = lua_tonumber(L, -1);
    lua_pop(L, 1);
    updatePlayer->pos_x = lua_tonumber(L, -1);
    lua_pop(L, 1);

    /* return the number of results */
    return 0;
}

void
keydown(unsigned char key, int x, int y)
{
    if (key == 'r')
    {
        luaL_dofile(L, "update_player.lua");
    }
    else if ( key == 'a' )
    {
        playerOne->pos_x -= 0.1;
    }
    else if ( key == 'd' )
    {
        playerOne->pos_x += 0.1;
    }
}

int
main(int argc, char **argv)
{
    init_opengl(argc, argv);
    init_lua();
    glutMainLoop();
}
