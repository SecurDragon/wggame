#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "View.hpp"
#include "InputController.hpp"

class Game {
private:
	sf::RenderWindow* _window;
	View* _view;
	Level* _level;
	InputController* _controller;
	sf::Font* _font;
	sf::Text _complete_text;
	sf::RectangleShape _complete_background;

	enum State { Play, Completed };
	State _state;

public:
	Game() : _state(Play) {}
	~Game();

	void init();
	void loop();
};
#endif //_GAME_HPP_
