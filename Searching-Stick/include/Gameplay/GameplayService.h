#pragma once

namespace Gameplay
{
	class GameplayController;
	enum class SearchType;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;

	public:
		GameplayService();
		~GameplayService();

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