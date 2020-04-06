#ifndef ELF_EXPORTER_ENUM_HPP
#define ELF_EXPORTER_ENUM_HPP
#include <map>
#include <string>
#include "DWARF/Block.hpp"
#include "DWARF/File.hpp"

class Enum {
    std::string _name;
    std::string _fileName;
    uint8_t _byteSize;
    std::map<std::string, std::string> _values;

public:
    Enum(const File& file, Block* block);

    const std::string& GetName() const { return _name; }
    const std::string& GetFileName() const { return _fileName; }
    uint8_t GetByteSize() const { return _byteSize; }
    const std::map<std::string, std::string>& GetValues() const { return _values; }

};

#endif // ELF_EXPORTER_ENUM_HPP
