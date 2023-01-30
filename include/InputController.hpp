#ifndef _INPUTCONTROLLER_HPP_
#define _INPUTCONTROLLER_HPP_

#include <SFML/Graphics.hpp>
#include <queue>

#include "Level.hpp"

struct MouseGesture {
	sf::Vector2f begin;
	sf::Vector2f end;
};

class InputController {
private:
	sf::RenderWindow *_window;

	sf::Vector2f _mouse_down;
	sf::Vector2f _mouse_up;
	std::queue<MouseGesture> _gestures;

public:
	InputController(sf::RenderWindow *window) : _window(window) {};

	~InputController() = default;

	void processEvent(sf::Event& event);

	void update(Level *level);
};

#endif //_INPUTCONTROLLER_HPP_
