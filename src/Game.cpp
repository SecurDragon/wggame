#include "Game.hpp"

extern float scale_factor;

extern sf::Vector2f view_offset;

Game::~Game() {
	delete _window;
	delete _view;
	delete _level;
	delete _controller;
}

void Game::init() {
	_window = new sf::RenderWindow(sf::VideoMode(800, 800), "", sf::Style::Close);
	_font = new sf::Font();
	_font->loadFromFile("resources/Roboto.ttf");

	_complete_text = sf::Text("Puzzle solved!\nPress any key to close", *_font, 24);
	sf::Vector2f complete_position = { 250.f, 250.f };

	sf::Color yellow = sf::Color(0xFFFF00FF);
	sf::FloatRect text_rect = _complete_text.getLocalBounds();
	_complete_text.setOrigin(text_rect.width / 2, text_rect.height / 2);
	_complete_text.setPosition(complete_position + view_offset);
	_complete_text.setFillColor(yellow);

	_complete_background = sf::RectangleShape({ text_rect.width + scale_factor, text_rect.height + scale_factor });
	sf::FloatRect bg_rect = _complete_background.getLocalBounds();
	_complete_background.setOrigin(bg_rect.width / 2, bg_rect.height / 2);
	_complete_background.setPosition(complete_position + view_offset);
	_complete_background.setFillColor(sf::Color::Black);
	_complete_background.setOutlineThickness(2.f);
	_complete_background.setOutlineColor(yellow);

	_level = Level::generate();

	_view = new View(_window);
	_level->connect_with(_view);
	_controller = new InputController(_window);

	_window->setFramerateLimit(60);
}

void Game::loop() {
	while (_window->isOpen()) {
		sf::Event event = sf::Event();
		while (_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				_window->close();
			if (_state == State::Completed) {
				if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
					_window->close();
			} else
				_controller->processEvent(event);

		}

		_window->clear();

		_controller->update(_level);
		if (_level->check_completion()) {
			_state = State::Completed;
		}
		_view->draw();
		if (_state == State::Completed) {
			_window->draw(_complete_background);
			_window->draw(_complete_text);
		}

		_window->display();
	}
}

