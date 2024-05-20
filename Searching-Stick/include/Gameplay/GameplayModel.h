#pragma once
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    enum class SearchType
    {
        LINEAR_SEARCH,
        BINARY_SEARCH,
    };

    class GameplayModel
    {
    public:
        const float max_element_height = 820.f;
        const float elements_spacing = 25.f;
        const float element_y_position = 1020.f;

        const sf::Color element_color = sf::Color::White;
        const sf::Color search_element_color = sf::Color::Blue;
        const sf::Color found_element_color = sf::Color::Green;
        const sf::Color processing_element_color = sf::Color::Red;

        int linear_search_delay = 120;
        int linear_search_sticks = 100;

        int number_of_elements = linear_search_sticks;

        GameplayModel();
        ~GameplayModel();

        void initialize();
        void update();
        void render();
    };
}