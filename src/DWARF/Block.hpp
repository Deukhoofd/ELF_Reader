#ifndef ELF_EXPORTER_BLOCK_HPP
#define ELF_EXPORTER_BLOCK_HPP

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
    uint32_t _atType = 0;
    bool _external = false;
    uint8_t _byteSize = 0;
    std::string _constValue;

    static std::regex _atKindMatcher;
    static std::regex _nameMatcher;

public:
    Block(uint8_t level, TagType type);
    virtual ~Block() = default;

    inline constexpr uint8_t GetLevel() const { return _level; }
    inline constexpr TagType GetType() const { return _type; }
    inline constexpr Block* GetNext() const { return _next; }
    inline constexpr const std::string& GetName() const { return _name; }
    inline constexpr uint32_t GetAtType() const { return _atType; }
    inline constexpr bool IsExternal() const { return _external; }
    inline constexpr uint8_t GetByteSize() const { return _byteSize; }
    inline constexpr const std::string& GetConstValue() const { return _constValue; }

    void SetNext(Block* next) { _next = next; }

    static uint32_t constexpr GetStringHash(char const* input) {
        return *input ? static_cast<uint32_t>(*input) + 33 * GetStringHash(input + 1) : 5381;
    };

    virtual void AddData(const std::string& str) {
        std::smatch match;
        if (std::regex_match(str, match, _atKindMatcher)) {
            auto kind = GetStringHash(match[1].str().c_str());
            auto data = match[2].str();

            switch (kind){
                case GetStringHash("DW_AT_name"):
                    if (std::regex_match(data, match, _nameMatcher)) {
                        _name = match[1].str();
                        return;
                    }
                    break;
                case GetStringHash("DW_AT_type"):
                    _atType = std::stoi(data.substr(3, data.size() - 4), nullptr, 16);
                    break;
                case GetStringHash("DW_AT_byte_size"):
                    _byteSize = std::stoi(data);
                    break;
                case GetStringHash("DW_AT_external"):
                    _external = *data.c_str() == '1';
                    break;
                case GetStringHash("DW_AT_const_value"):
                    _constValue = data;
                    break;
            }
        }
    }
};

#endif // ELF_EXPORTER_BLOCK_HPP
