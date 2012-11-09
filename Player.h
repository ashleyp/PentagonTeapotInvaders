#include <iostream>

class Player {
  public:
    Player();                         // constructor; initialize the list to be empty
    Player(float x, float y, float z);
    void updateScale( float x, float y, float z );
    void setScaleX( float x );
    void setScaleY( float y );
    void setScaleZ( float z );
    float pos_x;
    float pos_y;
    float pos_z;
    float scale_x;
    float scale_y;
    float scale_z;
};

