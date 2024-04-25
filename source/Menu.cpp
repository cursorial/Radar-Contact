//
// Created by bgd on 09.04.2024.
//

#include "../header/Menu.h"
#include "../header/ResourcesManager.h"

Menu::Menu() :
        Window({500, 400}, "Radar Contact - Menu")
{
    m_background.setTexture(ResourcesManager::Instance().getTexture("menu.png"));

    sf::RectangleShape button{sf::Vector2f(50,30)};
    button.setOutlineThickness(2.3f);
    button.setOutlineColor(sf::Color::Transparent);
    button.setFillColor(sf::Color::Transparent);

    button.setPosition(51,115);
    m_regionsButtons.emplace_back(button, "Poland");

    button.setPosition(145,117);
    m_regionsButtons.emplace_back(button, "Iceland");

    button.setPosition(231,116);
    m_regionsButtons.emplace_back(button, "Cyprus");

    button.setPosition(318,115);
    m_regionsButtons.emplace_back(button, "Austria");

    button.setPosition(410,115);
    m_regionsButtons.emplace_back(button, "Turkey");

    button.setPosition(50,197);
    m_regionsButtons.emplace_back(button, "UK");
}

void Menu::render()
{
    m_window.clear();

    m_window.draw(m_background);

    for(auto &regionsButton: m_regionsButtons) {
        m_window.draw(regionsButton.first);
    }

    m_window.display();
}

void Menu::update()
{
    checkHovers();
}

void Menu::checkHovers()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};

    for(auto &regionsButton: m_regionsButtons) {
        if(regionsButton.first.getGlobalBounds().contains(float_mouse_position)) {
            regionsButton.first.setOutlineColor(sf::Color::White);
        }
        else {
            regionsButton.first.setOutlineColor(sf::Color::Transparent);
        }
    }
}

void Menu::handleEvent()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    sf::Vector2f float_mouse_position{(float) mouse_position.x, (float) mouse_position.y};
    sf::Event menu_event{};

    while(m_window.pollEvent(menu_event))
    {
        switch(menu_event.type)
        {
            case sf::Event::Closed: {
                m_window.close();

                break;
            }
            case sf::Event::KeyPressed:
            {
                const sf::Keyboard::Key key_code = menu_event.key.code;

                if(key_code == sf::Keyboard::Escape)
                {
                    m_window.close();
                }

                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                for(const auto &regionButtons: m_regionsButtons) {
                    if(regionButtons.first.getGlobalBounds().contains(float_mouse_position)) {
                        ResourcesManager::Instance().loadRegion(regionButtons.second);
                        m_window.close();
                    }
                }

                break;
            }

            default:
                break;
        }
    }
}