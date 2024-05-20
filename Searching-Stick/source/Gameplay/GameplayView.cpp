#include "Gameplay/GameplayView.h"
#include "Gameplay/GameplayController.h"
#include "Global/ServiceLocator.h"
#include "Global/Config.h"

namespace Gameplay
{
	using namespace UI::UIElement;
	using namespace Global;

	GameplayView::GameplayView() { background_image = new ImageView(); }

	GameplayView::~GameplayView() { delete (background_image); }

	void GameplayView::initialize(GameplayController* gameplay_controller)
	{
		this->gameplay_controller = gameplay_controller;
		initializeBackgroundImage();
		initializeTextElements();
	}

	void GameplayView::initializeBackgroundImage()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

		background_image->initialize(Config::background_texture_path,
			game_window->getSize().x,
			game_window->getSize().y,
			sf::Vector2f(0, 0));

		background_image->setImageAlpha(background_alpha);
	}

	void GameplayView::initializeTextElements()
	{
		font.loadFromFile(Global::Config::bubble_bobble_font_path);

		num_sticks_text.setFont(font);
		num_sticks_text.setCharacterSize(24);
		num_sticks_text.setFillColor(sf::Color::White);
		num_sticks_text.setPosition(10.f, 10.f);

		delay_text.setFont(font);
		delay_text.setCharacterSize(24);
		delay_text.setFillColor(sf::Color::White);
		delay_text.setPosition(10.f, 40.f);

		time_complexity_text.setFont(font);
		time_complexity_text.setCharacterSize(24);
		time_complexity_text.setFillColor(sf::Color::White);
		time_complexity_text.setPosition(10.f, 70.f);
	}

	void GameplayView::updateTextElements()
	{
		num_sticks_text.setString("Number of Sticks: " + std::to_string(gameplay_controller->getNumberOfSticks()));
		delay_text.setString("Delay in milliseconds: " + std::to_string(gameplay_controller->getDelayInMs()));
		time_complexity_text.setString("Time Complexity: " + gameplay_controller->getTimeComplexity());
	}

	void GameplayView::update() { updateTextElements(); background_image->update(); }

	void GameplayView::render() { 
		background_image->render();

		if (gameplay_controller)
		{
			sf::RenderWindow* game_window = Global::ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
			game_window->draw(num_sticks_text);
			game_window->draw(delay_text);
			game_window->draw(time_complexity_text);
		}
	}
}