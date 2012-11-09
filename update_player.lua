-- call a C++ function

function updatePlayer(player, x, y, z)
    if ( x > 0.7 ) then
        x = -0.8
        y = y - 0.15
    else
        x = x + 0.1
    end
    move_to( player, x, y, z );
end

