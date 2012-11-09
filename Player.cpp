#include "Player.h"

Player::Player() {
    pos_x  = 0.0;
    pos_y  = 0.0;
    pos_z  = 0.0;
    scale_x = 0.05;
    scale_y = 0.05;
    scale_z = 0.05;
}

Player::Player(float x, float y, float z) {
    pos_x = x;
    pos_y = y;
    pos_z = z;
    scale_x = 0.05;
    scale_y = 0.05;
    scale_z = 0.05;
}


void Player::updateScale( float x, float y, float z ) {
    scale_x = x;
    scale_y = y;
    scale_z = z;
}

void Player::setScaleX( float x ) {
    scale_x = x;
}

void Player::setScaleY( float y ) {
    scale_y = y;
}

void Player::setScaleZ( float z ) {
    scale_z = z;
}
