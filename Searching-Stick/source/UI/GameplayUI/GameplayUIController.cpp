#include "UI/GameplayUI/GameplayUIController.h"
#include "Global/Config.h"
#include "Global/ServiceLocator.h"
#include "Gameplay/GameplayService.h"
#include "Sound/SoundService.h"
#include "Main/GameService.h"
#include "Gameplay/GameplayModel.h"

namespace UI
{
    namespace GameplayUI
    {
        using namespace Main;
        using namespace Sound;
        using namespace UIElement;
        using namespace Global;
        using namespace Gameplay;

        GameplayUIController::GameplayUIController()
        {
            createButton();
            createTexts();
        }

        GameplayUIController::~GameplayUIController()
        {
            destroy();
        }

        void GameplayUIController::initialize()
        {
            initializeButton();
            initializeTexts();
        }

        void GameplayUIController::createButton()
        {
            menu_button = new ButtonView();
        }

        void GameplayUIController::createTexts()
        {
            search_type_text = new TextView();
            number_of_comparisons_text = new TextView();
            number_of_array_access_text = new TextView();
        }

        void GameplayUIController::initializeButton()
        {
            menu_button->initialize("Menu Button",
                Config::menu_button_large_texture_path,
                menu_button_width, menu_button_height,
                sf::Vector2f(menu_button_x_position, menu_button_y_position));

            registerButtonCallback();
        }

        void GameplayUIController::initializeTexts()
        {
            search_type_text->initialize("Search Type  :  Linear Search", sf::Vector2f(search_type_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
            number_of_comparisons_text->initialize("Comparisons  :  0", sf::Vector2f(comparisons_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
            number_of_array_access_text->initialize("Array Access  :  0", sf::Vector2f(array_access_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
        }

        void GameplayUIController::update()
        {
            menu_button->update();
            updateSearchTypeText();
            updateComparisonsText();
            updateArrayAccessText();
        }

        void GameplayUIController::render()
        {
            menu_button->render();
            search_type_text->render();
            number_of_comparisons_text->render();
            number_of_array_access_text->render();
        }

        void GameplayUIController::show()
        {
            menu_button->show();
            search_type_text->show();
            number_of_comparisons_text->show();
            number_of_array_access_text->show();
        }

        void GameplayUIController::updateSearchTypeText()
        {
            SearchType search_type = ServiceLocator::getInstance()->getGameplayService()->getSearchType();
            
            switch (search_type)
            {
            case::Gameplay::SearchType::LINEAR_SERACH:
                search_type_text->setText("Linear Search");
                break;

            case::Gameplay::SearchType::BINARY_SEARCH:
                search_type_text->setText("Binary Search");
                break;
            }
            search_type_text->update();
        }

        void GameplayUIController::updateComparisonsText()
        {
            int number_of_comparisons = ServiceLocator::getInstance()->getGameplayService()->getNumberOfComparisons();;
            sf::String comparisons_string = "Comparisons  :  " + std::to_string(number_of_comparisons);

            number_of_comparisons_text->setText(comparisons_string);
            number_of_comparisons_text->update();
        }

        void GameplayUIController::updateArrayAccessText()
        {
            int number_of_array_access = ServiceLocator::getInstance()->getGameplayService()->getNumberOfArrayAccess();;
            sf::String array_access_string = "Array Access  :  " + std::to_string(number_of_array_access);

            number_of_array_access_text->setText(array_access_string);
            number_of_array_access_text->update();
        }

        void GameplayUIController::menuButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            ServiceLocator::getInstance()->getGameplayService()->reset();
            GameService::setGameState(GameState::MAIN_MENU);
        }

        void GameplayUIController::registerButtonCallback()
        {
            menu_button->registerCallbackFuntion(std::bind(&GameplayUIController::menuButtonCallback, this));
        }

        void GameplayUIController::destroy()
        {
            delete (menu_button);
            delete (search_type_text);
            delete (number_of_comparisons_text);
            delete (number_of_array_access_text);
        }
    }
}