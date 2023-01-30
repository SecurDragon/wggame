#ifndef _VIEW_HPP_
#define _VIEW_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

#include "Block.hpp"

class View {
public:
	View(sf::RenderWindow *window, uint16_t block_count = 0);

	~View();

	void update(Block const& block, vec2i moved_to);

	void draw();

private:
	static const sf::Vector2f cBlockSize;

	std::vector<sf::RectangleShape *> _blocks;
	std::vector<sf::RectangleShape *> _objectives;
	sf::RenderWindow *_window;
};

#endif //_VIEW_HPP_
