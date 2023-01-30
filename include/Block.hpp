#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include <cstdint>

struct vec2i {
	uint16_t x;
	uint16_t y;
};

struct Block {
	using Type = uint16_t;
	static constexpr Type TypeStatic = UINT16_MAX;

	Type type;
	uint16_t const id;

	explicit Block(Type type)
			: type(type), id(_id_counter++) {}

	Block() : Block(0) {}

private:
	static uint16_t _id_counter;
};

#endif //_BLOCK_HPP_
