#include <Expo/Room.h>


Room::Room(const glm::vec3& pos, const glm::vec2& dimensions, float wallHeight, const std::string& floorTexture, const std::string& wallTexture)
    : m_Floor(dimensions.x, 0.2f, dimensions.y, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}),
    m_WallNorth(dimensions.x, wallHeight, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}),
    m_WallSouth(dimensions.x, wallHeight, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}),
    m_WallEast(0.2f, wallHeight, dimensions.y, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}),
    m_WallWest(0.2f, wallHeight, dimensions.y, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {})
{
    // --- Set Positions ---
    // Floor
    m_Floor.setPosition(pos);

    // Walls (Y is centered on wall height)
    float wallY = pos.y + (wallHeight / 2.0f);
    float halfWidth = dimensions.x / 2.0f;
    float halfDepth = dimensions.y / 2.0f;

    m_WallNorth.setPosition({ pos.x, wallY, pos.z - halfDepth });
    m_WallSouth.setPosition({ pos.x, wallY, pos.z + halfDepth });
    m_WallWest.setPosition({ pos.x - halfWidth, wallY, pos.z });
    m_WallEast.setPosition({ pos.x + halfWidth, wallY, pos.z });

    // --- Set Textures ---
    m_Floor.setAllFacesTexture(floorTexture);
    m_WallNorth.setAllFacesTexture(wallTexture);
    m_WallSouth.setAllFacesTexture(wallTexture);
    m_WallEast.setAllFacesTexture(wallTexture);
    m_WallWest.setAllFacesTexture(wallTexture);
}

void Room::drawOpaque()
{
    m_Floor.drawOpaque();
    m_WallNorth.drawOpaque();
    m_WallSouth.drawOpaque();
    m_WallEast.drawOpaque();
    m_WallWest.drawOpaque();
}
