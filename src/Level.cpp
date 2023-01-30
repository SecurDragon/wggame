#include "Level.hpp"

#define DIFF(X, Y) ((X) > (Y) ? ((X) - (Y)) : ((Y) - (X)))

Level::Level() {
	_field = new Block **[cLevelSize];
	for (uint16_t i = 0; i < cLevelSize; ++i)
		_field[i] = new Block *[cLevelSize];

	for (uint16_t i = 0; i < cLevelSize; ++i)
		for (uint16_t j = 0; j < cLevelSize; ++j)
			_field[i][j] = nullptr;

	for (uint16_t k = 0; k < cLockedSize; ++k) {
		uint16_t i = cLocked[k][0];
		uint16_t j = cLocked[k][1];
		_field[i][j] = new Block(Block::TypeStatic);
	}
};

Level::~Level() {
	for (uint16_t i = 0; i < cLevelSize; ++i) {
		for (uint16_t j = 0; j < cLevelSize; ++j)
			delete _field[i][j];
	}

	for (uint16_t i = 0; i < cLevelSize; ++i)
		delete[] _field[i];

	delete[] _field;
}

void Level::connect_with(View *view) {
	_view = view;

	for (uint16_t i = 0; i < cLevelSize; ++i) {
		for (uint16_t j = 0; j < cLevelSize; ++j) {
			if (_field[i][j] != nullptr)
				_view->update(*_field[i][j], { j, i });
		}
	}
}

bool Level::try_move(vec2i from, vec2i to) {
	uint16_t dist_x = DIFF(from.x, to.x);
	uint16_t dist_y = DIFF(from.y, to.y);
	if (dist_x + dist_y > 1)
		return false;

	if (_field[from.y][from.x] != nullptr &&
	    _field[from.y][from.x]->type == Block::TypeStatic)
		return false;

	if (_field[to.y][to.x] != nullptr)
		return false;

	std::swap(_field[to.y][to.x], _field[from.y][from.x]);
	if (_field[to.y][to.x] != nullptr)
		_view->update(*_field[to.y][to.x], to);
	return true;
}

bool Level::check_completion() {
	for (uint16_t i = 0; i < cLevelSize; ++i) {
		for (auto cConstraint : cConstraints) {
			if (_field[i][cConstraint[0]] == nullptr || _field[i][cConstraint[0]]->type != cConstraint[1])
				return false;
		}
	}
	return true;
}

#include <algorithm>
#include <random>
#include <chrono>

Level *Level::generate() {
	Level *level = new Level();
	std::vector<Block::Type> quotas;
	for (uint16_t i = 0; i < cLevelSize; ++i) {
		for (uint16_t type = 1; type <= cConstraintsSize; ++type)
			quotas.push_back(type);
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(quotas.begin(), quotas.end(), std::default_random_engine(seed));

	for (uint16_t i = 0; i < cLevelSize; ++i) {
		for (auto cConstraint : cConstraints) {
			level->_field[i][cConstraint[0]] = new Block(quotas.back());
			quotas.pop_back();
		}
	}
	return level;
}
