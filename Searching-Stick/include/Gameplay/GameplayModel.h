#pragma once
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    enum class SearchType
    {
        LINEAR_SERACH,
        BINARY_SEARCH,
    };

    class GameplayModel
    {
    public:
        const int number_of_elements = 300;
        const float max_element_height = 820.f;
        const float elements_spacing = 25.f;
        const float element_y_position = 1020.f;

        const sf::Color element_color = sf::Color::White;
        const sf::Color search_element_color = sf::Color::Blue;
        const sf::Color found_element_color = sf::Color::Green;
        const sf::Color processing_element_color = sf::Color::Red;

        const long operation_delay = 20;

        GameplayModel();
        ~GameplayModel();

        void initialize();
        void update();
        void render();
    };
}