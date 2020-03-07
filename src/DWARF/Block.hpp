#ifndef ELF_EXPORTER_BLOCK_HPP
#define ELF_EXPORTER_BLOCK_HPP

#include <Arbutils/ConstString.hpp>
#include <cstdint>
#include <iostream>
#include <regex>
#include "TagType.hpp"

class Block {
private:
    uint8_t _level;
    TagType _type;
    Block* _next = nullptr;
    std::string _name = "";
    int _atType = 0;
    bool _external = false;

    static std::regex _atKindMatcher;
    static std::regex _nameMatcher;
    static std::regex _typeMatcher;
    static std::regex _externalMatcher;

public:
    Block(uint8_t level, TagType type);
    virtual ~Block() = default;

    inline constexpr uint8_t GetLevel() const { return _level; }
    inline constexpr TagType GetType() const { return _type; }
    inline constexpr Block* GetNext() const { return _next; }
    inline constexpr const std::string& GetName() const { return _name; }
    inline constexpr int GetAtType() const { return _atType; }
    inline constexpr bool IsExternal() const { return _external; }

    void SetNext(Block* next) { _next = next; }

    virtual void AddData(const std::string& str) {
        std::smatch match;
        if (std::regex_match(str, match, _atKindMatcher)) {
            auto kind = Arbutils::CaseInsensitiveConstString::GetHash(match[1].str());
            auto data = match[2].str();
            if (kind == "DW_AT_name"_cnc) {
                if (std::regex_match(data, match, _nameMatcher)) {
                    _name = match[1].str();
                    return;
                }
            } else if (kind == "DW_AT_type"_cnc) {
                _atType = std::stoi(data.substr(3, data.size() - 4), nullptr, 16);
            } else if (kind == "DW_AT_external"_cnc) {
                _external = *data.c_str() == '1';
            }
        }
    }
};

#endif // ELF_EXPORTER_BLOCK_HPP
