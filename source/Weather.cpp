//
// Created by bgd on 13.04.2024.
//

#include "../header/Weather.h"
#include "../header/ResourcesManager.h"

#include "../header/DataAPI.h"
#include "../header/API.h"
#include "../header/MockAPI.h"

// https://tilecache.rainviewer.com/v2/radar/1713089400/256/6/55.776575/-5.624999/2/1_0.png
// https://tilecache.rainviewer.com/v2/radar/1713041400/512/5/55.776575/-11.249998/1/1_0.png
Weather::Weather() : m_tiles{ResourcesManager::Instance().getWeatherTiles()}
{}

void Weather::render(sf::RenderWindow *window) {
    for(const sf::Sprite &sprite: m_sprites) {
        window->draw(sprite);
    }
}

int Weather::getPixelColor(sf::Sprite& sprite, sf::Vector2i position) {
    sf::Vector2i spritePosition(static_cast<int>(sprite.getPosition().x) - 128,
                                static_cast<int>(sprite.getPosition().y) - 128);

    sf::Color pixelColor = sprite.getTexture()->copyToImage().getPixel(position.x - spritePosition.x, position.y - spritePosition.y);

    struct Color {
        int r, g, b;
    };

    const std::vector<Color> colors = {
            {255, 191, 0},   // yellow
            {0, 118, 170},   // blue
            {189, 0, 0},     // red
            {255, 157, 255}, // pink
            {0, 0, 0}        // nothing
    };

    int minDistance = std::numeric_limits<int>::max();
    int colorIndex = -1;

    for (int i = 0; i < (int) colors.size(); ++i) {
        int dr = pixelColor.r - colors[i].r;
        int dg = pixelColor.g - colors[i].g;
        int db = pixelColor.b - colors[i].b;

        int distance = dr * dr + dg * dg + db * db;

        if (distance < minDistance) {
            minDistance = distance;
            colorIndex = i;
        }
    }

    return colorIndex;
}

void Weather::fetchWeatherImages(sf::RenderWindow *window) {
    m_sprites = std::vector<sf::Sprite> {};

    m_textures = (ResourcesManager::Instance().isMockingEnabled() ? DataAPI<MockAPI>::getWeatherTextures(window) :
                                                                    DataAPI<LiveAPI>::getWeatherTextures(window));

    for(int i = 0; i < (int) m_textures.size(); i++) {
        sf::Sprite temp_sprite;
        temp_sprite.setTexture(m_textures[i]);

        sf::Color color = temp_sprite.getColor();
        temp_sprite.setColor(sf::Color(color.r, color.g, color.b, 140));

        sf::FloatRect bounds = temp_sprite.getLocalBounds();
        temp_sprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

        sf::Vector2f projection = Math::MercatorProjection(m_tiles[i].first, m_tiles[i].second,
                                                           ResourcesManager::Instance().getRegionBox());
        temp_sprite.setPosition(projection);
        m_sprites.push_back(temp_sprite);
    }
}