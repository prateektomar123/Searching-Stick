#include "Gameplay/GameplayModel.h"
#include "Global/ServiceLocator.h"
#include "Global/Config.h"

namespace Gameplay
{
	using namespace Global;

	GameplayModel::GameplayModel() { }

	GameplayModel::~GameplayModel() { }

	void GameplayModel::initialize() {

		const int number_of_elements = 300;
		const float max_element_height = 820.f;
		const float elements_spacing = 25.f;
		const float element_y_position = 1020.f;

		const sf::Color element_color = sf::Color::White;
		const sf::Color search_element_color = sf::Color::Blue;
		const sf::Color found_element_color = sf::Color::Green;
		const sf::Color processing_element_color = sf::Color::Red;
	
		linear_search_delay = 120;
		binary_search_delay = 60;

		linear_search_sticks = 100; 
		binary_search_sticks = 50;
	}

	void GameplayModel::update() { }

	void GameplayModel::render() { }
}