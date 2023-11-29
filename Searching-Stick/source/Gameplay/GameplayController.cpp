#include "Gameplay/GameplayController.h"
#include "Gameplay/GameplayView.h"
#include "Gameplay/GameplayModel.h"
#include "Gameplay/GameplayService.h"
#include "Global/ServiceLocator.h"
#include <random>

namespace Gameplay
{
	using namespace UI::UIElement;
	using namespace Global;
	using namespace Graphics;

	GameplayController::GameplayController() 
	{
		gameplay_view = new GameplayView();
		gameplay_model = new GameplayModel();

		for (int i = 0; i < gameplay_model->number_of_elements; i++) elements.push_back(new Element(i));
	}

	GameplayController::~GameplayController() 
	{
		destroy();
	}

	void GameplayController::initialize() 
	{
		gameplay_view->initialize(this);
		gameplay_model->initialize();
		initializeElements();
		reset();
	}

	void GameplayController::initializeElements()
	{
		float rectangle_width = calculateElementWidth();

		for (int i = 0; i < gameplay_model->number_of_elements; i++)
		{
			sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, 
				(static_cast<float>(i+1) / gameplay_model->number_of_elements) * gameplay_model->max_element_height);

			elements[i]->element_view->initialize(rectangle_size, sf::Vector2f(0,0), 0, gameplay_model->element_color);
		}
	}

	void GameplayController::update() 
	{
		processSearchThreadState();
		gameplay_view->update();
		for (int i = 0; i < elements.size(); i++) elements[i]->element_view->update();
	}

	void GameplayController::render() 
	{
		gameplay_view->render(); 
		for (int i = 0; i < elements.size(); i++) elements[i]->element_view->render();
	}

	float GameplayController::calculateElementWidth()
	{
		float total_spacing = gameplay_model->elements_spacing * (gameplay_model->number_of_elements + 1);
		float total_width = ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x;

		return (total_width - total_spacing) / gameplay_model->number_of_elements;
	}

	void GameplayController::updateElementsPosition()
	{
		for (int i = 0; i < elements.size(); i++)
		{
			float x_position = (i * elements[i]->element_view->getSize().x)  + ((i + 1) * gameplay_model->elements_spacing);
			float y_position = gameplay_model->element_y_position - elements[i]->element_view->getSize().y;

			elements[i]->element_view->setPosition(sf::Vector2f(x_position, y_position));
		}
	}

	void GameplayController::shuffleElements()
	{
		std::random_device device;
		std::mt19937 random_engine(device());

		std::shuffle(elements.begin(), elements.end(), random_engine);
		updateElementsPosition();
	}

	void GameplayController::sortElements()
	{
		std::sort(elements.begin(), elements.end(), [this](const Element* a, const Element* b) { return compareElementsByData(a, b); });
		updateElementsPosition();
	}

	bool GameplayController::compareElementsByData(const Element* a, const Element* b) const
	{
		return a->data < b->data;
	}

	void GameplayController::processSearchThreadState()
	{
		if (search_thread.joinable() && element_to_search == nullptr) search_thread.join();
	}

	void GameplayController::processLinearSearch()
	{
		for (int i = 0; i < elements.size(); i++)
		{
			number_of_array_access += 2;
			number_of_comparisons++;

			if (elements[i] == element_to_search)
			{
				elements[i]->element_view->setFillColor(gameplay_model->found_element_color);
				element_to_search = nullptr;
				return;
			}
			else
			{
				elements[i]->element_view->setFillColor(gameplay_model->processing_element_color);
				std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));
				elements[i]->element_view->setFillColor(gameplay_model->element_color);
			}
		}
	}

	void GameplayController::processBinarySearch()
	{
		int left = 0;
		int right = elements.size();

		while (left < right)
		{
			int mid = left + (right - left) / 2;
			number_of_array_access += 2;
			number_of_comparisons++;

			if (elements[mid] == element_to_search)
			{
				elements[mid]->element_view->setFillColor(gameplay_model->found_element_color);
				element_to_search = nullptr;
				return;
			}

			elements[mid]->element_view->setFillColor(gameplay_model->processing_element_color);
			std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));
			elements[mid]->element_view->setFillColor(gameplay_model->element_color);

			number_of_array_access++;
			if (elements[mid]->data <= element_to_search->data) left = mid;
			else right = mid;
		}
	}

	void GameplayController::searchElement(SearchType search_type)
	{
		current_operation_delay = gameplay_model->operation_delay;
		this->search_type = search_type;

		switch (search_type)
		{
		case Gameplay::SearchType::LINEAR_SERACH:
			search_thread = std::thread(&GameplayController::processLinearSearch, this);
			break;

		case Gameplay::SearchType::BINARY_SEARCH:
			sortElements();
			search_thread = std::thread(&GameplayController::processBinarySearch, this);
			break;
		}
	}

	void GameplayController::resetElementsColor()
	{
		for (int i = 0; i < elements.size(); i++) elements[i]->element_view->setFillColor(gameplay_model->element_color);
	}

	void GameplayController::resetVariables()
	{
		number_of_comparisons = 0;
		number_of_array_access = 0;
	}

	void GameplayController::resetSearchElement()
	{
		element_to_search = elements[std::rand() % elements.size()];
		element_to_search->element_view->setFillColor(gameplay_model->search_element_color);
	}

	void GameplayController::reset() 
	{
		current_operation_delay = 0;
		if (search_thread.joinable()) search_thread.join();
		
		shuffleElements();
		resetElementsColor();
		resetSearchElement();
		resetVariables();
	}

	void GameplayController::destroy()
	{
		if (search_thread.joinable()) search_thread.join();
		for (int i = 0; i < elements.size(); i++) delete(elements[i]);
		elements.clear();

		delete (gameplay_view);
		delete (gameplay_model);
	}

	SearchType GameplayController::getSearchType() { return search_type; }

	int GameplayController::getNumberOfComparisons() { return number_of_comparisons; }

	int GameplayController::getNumberOfArrayAccess() { return number_of_array_access; }
}