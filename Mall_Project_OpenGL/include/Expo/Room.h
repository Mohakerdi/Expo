#pragma once

#include "Box.h"

// Defines a simple room with a floor and four walls.
class Room
{
public:
    // Constructor takes position, dimensions, and wall textures.
    Room(
        const glm::vec3& pos,
        const glm::vec2& dimensions, // x = width, y = depth
        float wallHeight,
        const std::string& floorTexture,
        const std::string& wallTexture
    );

    // Draws all parts of the room.
    void drawOpaque();

private:
    Box m_Floor;
    Box m_WallNorth, m_WallSouth, m_WallEast, m_WallWest;
};
