#pragma once
#include <SFML/System/String.hpp>

namespace Gameplay
{
	class GameplayController;
	enum class SearchType;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;

		void initializeRandomSeed();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		void reset();
		void searchElement(SearchType search_type);

		SearchType getCurrentSearchType();
		int getNumberOfComparisons();
		int getNumberOfArrayAccess();

		int getNumberOfSticks();
		int getDelayMilliseconds();
		sf::String getTimeComplexity();

	};
}