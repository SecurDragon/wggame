#include "InputController.hpp"

extern float scale_factor;

extern sf::Vector2f view_offset;

void InputController::processEvent(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i pos = { event.mouseButton.x, event.mouseButton.y };
		_mouse_down = _window->mapPixelToCoords(pos);
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		sf::Vector2i position = { event.mouseButton.x, event.mouseButton.y };
		_mouse_up = _window->mapPixelToCoords(position);
		_gestures.push({ _mouse_down, _mouse_up });
	}
}

void InputController::update(Level *level) {
	while (_gestures.size() > 0) {
		MouseGesture gesture = _gestures.front();
		_gestures.pop();
		vec2i begin = { static_cast<uint16_t>((gesture.begin.x - view_offset.x) / scale_factor),
		                static_cast<uint16_t>((gesture.begin.y - view_offset.y) / scale_factor) };

		vec2i end = { static_cast<uint16_t>((gesture.end.x - view_offset.x) / scale_factor ),
		              static_cast<uint16_t>((gesture.end.y - view_offset.y) / scale_factor) };
		level->try_move(begin, end);
	}
}

