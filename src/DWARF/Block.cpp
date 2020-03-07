#include "Block.hpp"
Block::Block(uint8_t level, TagType type) : _level(level), _type(type) {}

std::regex Block::_atKindMatcher("^\\s*<\\w+>\\s*(\\w+)\\s+: (.*)\\r*\\n*$");
std::regex Block::_nameMatcher("^\\(.*\\): (.*)$");
