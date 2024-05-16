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

    struct Element
    {
        int data;
        UI::UIElement::RectangleShapeView* element_view;

        Element() { }

        Element(int data)
        {
            this->data = data;
            element_view = new UI::UIElement::RectangleShapeView();
        }

        ~Element() { delete(element_view); }
    };

    class GameplayController
    {
    private:
        GameplayView* gameplay_view;
        GameplayModel* gameplay_model;

        std::vector<Element*> elements;
        Element* element_to_search;

        SearchType search_type;
        std::thread search_thread;

        int number_of_comparisons;
        int number_of_array_access;
        int current_operation_delay;

        void initializeElements();
        float calculateElementWidth();

        void updateElementsPosition();
        void shuffleElements();
        void sortElements();
        bool compareElementsByData(const Element* a, const Element* b) const;

        void resetElementsColor();
        void resetVariables();
        void resetSearchElement();

        void processSearchThreadState();
        void processLinearSearch();
        void processBinarySearch();

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
    };
}



