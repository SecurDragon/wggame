#include "View.hpp"

#include <unordered_map>
#include "Level.hpp"

float scale_factor = 100.f;
sf::Vector2f view_offset(0.5f * scale_factor, 1.f * scale_factor);

sf::Vector2f const  View::cBlockSize = { 1.f * scale_factor, 1.f * scale_factor };

std::unordered_map<Block::Type, sf::Color> block_colors = {
		{0,					sf::Color(0xFC0FC0FF)},		//Pink (not found)
		{1,					sf::Color(0xFF0000FF)},		//Red
		{2,					sf::Color(0x00FF00FF)},		//Green
		{3,					sf::Color(0x0000FFFF)},		//Blue
		{Block::TypeStatic,	sf::Color(0x48494BFF)},		//Gray
};

View::View(sf::RenderWindow* window, uint16_t block_count)
		: _window(window), _blocks(block_count)
{
	sf::View view(sf::FloatRect(0.0f, 0.0f, 6.f * scale_factor, 6.f * scale_factor));
	view.setViewport(sf::FloatRect(0.1, 0.1f, 0.8f, 0.8f));
	window->setView(view);

	for (uint16_t i = 0; i < Level::cConstraintsSize; ++i) {
		sf::RectangleShape* objective_icon = new sf::RectangleShape();
		objective_icon->setFillColor(block_colors[Level::cConstraints[i][1]]);
		objective_icon->setSize(cBlockSize * 0.75f);

		auto bbox = objective_icon->getLocalBounds();
		objective_icon->setOrigin(bbox.width / 2, bbox.height / 2);
		sf::Vector2f position({ view_offset.x + cBlockSize.x * Level::cConstraints[i][0], 0});
		position += cBlockSize * 0.5f;
		objective_icon->setPosition(position);
		_objectives.push_back(objective_icon);
	}
}

View::~View() {
	for (auto bl : _blocks)
		delete bl;
	for (auto bl : _objectives)
		delete bl;
}

void View::update(Block const& block, vec2i moved_to) {
	if (_blocks.size() < block.id + 1)
		_blocks.resize(block.id + 1);

	if (_blocks[block.id] == nullptr) {
		_blocks[block.id] = new sf::RectangleShape(cBlockSize);
		_blocks[block.id]->setFillColor(block_colors[block.type]);
	}
	sf::Vector2f new_position = { static_cast<float>(moved_to.x) * scale_factor, static_cast<float>(moved_to.y) * scale_factor };
	_blocks[block.id]->setPosition(new_position + view_offset);
}

void View::draw() {
	for (auto& obj : _objectives)
		_window->draw(*obj);
	for (auto& bl : _blocks) {
		if (bl != nullptr)
			_window->draw(*bl);
	}
}
