#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIElement/ImageView.h"

namespace Gameplay
{
    class GameplayController;

    class GameplayView
    {
    private:
        const float background_alpha = 55.f;

        GameplayController* gameplay_controller;
        UI::UIElement::ImageView* background_image;

        sf::Font font;
        sf::Text num_sticks_text;
        sf::Text delay_text;
        sf::Text time_complexity_text;

        void initializeBackgroundImage();
        void initializeTextElements();
        void updateTextElements();

    public:
        GameplayView();
        ~GameplayView();

        void initialize(GameplayController* gameplay_controller);
        void update();
        void render();
    };
}