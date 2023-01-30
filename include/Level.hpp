#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <numeric>

#include "Block.hpp"
#include "View.hpp"

class Level {
public:
	~Level();

	bool try_move(vec2i from, vec2i to);

	bool check_completion();

	void connect_with(View *view);

	static Level *generate();

	static constexpr uint16_t cConstraintsSize = 3;
	static constexpr uint16_t cConstraints[cConstraintsSize][2] = {{ 0, 1 },
	                                                               { 2, 2 },
	                                                               { 4, 3 }};

private:
	Level();

	static constexpr uint16_t cLevelSize = 5;

	static constexpr uint16_t cLockedSize = 6;
	static constexpr uint16_t cLocked[cLockedSize][2] = {{ 0, 1 },
	                                                     { 0, 3 },
	                                                     { 2, 1 },
	                                                     { 2, 3 },
	                                                     { 4, 1 },
	                                                     { 4, 3 }};

	Block ***_field;

	View *_view;
};

#endif //_LEVEL_HPP_
