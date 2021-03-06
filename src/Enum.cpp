#include "Enum.hpp"

Enum::Enum(const File &file, Block *block) {
    _name = block->GetName();
    _fileName = file.GetFileName();
    _byteSize = block->GetByteSize();
    if (_byteSize == 0) {
        throw std::logic_error("Invalid size for enum: " + std::to_string(_byteSize));
    }

    auto c = block->GetNext();
    while (c != nullptr) {
        if (c->GetLevel() <= block->GetLevel())
            break;
        if (c->GetType() == TagType::DW_TAG_enumerator && c->GetLevel() == block->GetLevel() + 1) {
            auto name = c->GetName();
            _values.insert({c->GetConstValue(), name});
        }
        c = c->GetNext();
    }
}
