#ifndef CONSTANTS_H
#define CONSTANTS_H

// TODO: constants::window_width/window_height are actually hardcoded from the map size (loaded in main)
// We should add objects like vegetation to prevent the player going anywhere near the limit
// of the map, and its black zone.
// auto mapSize = gameMap.getBounds();
// std::cout << mapSize.height << '\n'
//           << mapSize.width;

static constexpr int WINDOW_WIDTH{60 * 16};  // = 960
static constexpr int WINDOW_HEIGHT{40 * 16}; // = 640
static constexpr int TILE_SIZE{16};
static constexpr float PLAYER_SPEED{1.0f};
static constexpr int PLAYER_HEIGHT{20};

#endif // CONSTANTS_H
