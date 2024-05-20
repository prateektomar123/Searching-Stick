#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIElement/RectangleShapeView.h"
#include <vector>
#include <thread>

namespace Gameplay
{
    class GameplayView;
    class GameplayModel;
    enum class SearchType;

    class GameplayController
    {
    private:
        GameplayView* gameplay_view;
        GameplayModel* gameplay_model;

        std::vector<UI::UIElement::RectangleShapeView*> elements;
        UI::UIElement::RectangleShapeView* element_to_search;

        SearchType search_type;
        std::thread search_thread;

        int number_of_comparisons;
        int number_of_array_access;
        int current_operation_delay;

        int num_sticks;
        int delay_in_ms;
        sf::String time_complexity;


        void initializeElements();
        float calculateElementWidth();

        void updateElementsPosition();
        void shuffleElements();

        void resetElementsColor();
        void resetVariables();
        void resetSearchElement();

        void processSearchThreadState();
        void processLinearSearch();
        void initializeElementsArray();
        float calculateElementHeight();

        void destroy();

    public:
        GameplayController();
        ~GameplayController();

        void initialize();
        void update();
        void render();

        void reset();
        void searchElement(SearchType search_type);

        SearchType getSearchType();
        int getNumberOfComparisons();
        int getNumberOfArrayAccess();

        int getNumberOfSticks();
        int getDelayMilliseconds();
        sf::String getTimeComplexity();

        void setOperationDelayAndSticks(SearchType search_type);
    };
}



