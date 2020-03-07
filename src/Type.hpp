#ifndef ELF_EXPORTER_TYPE_HPP
#define ELF_EXPORTER_TYPE_HPP

#include <string>
#include "DWARF/Block.hpp"
#include "DWARF/File.hpp"
#include "../extern/json.hpp"

using json = nlohmann::json;

class Type{
    bool _pointer = false;
    bool _const = false;
    Type* _underlying = nullptr;
    std::string _name = "";

public:
    Type() { _name = "void"; }

    Type(const File& file, Block* block) {
        if (block->GetType() == TagType::DW_TAG_pointer_type) {
            _pointer = true;
            auto underlyingBlock = file.GetBlock(block->GetAtType());
            if (underlyingBlock->GetType() == TagType::DW_TAG_const_type) {
                _const = true;
                underlyingBlock = file.GetBlock(underlyingBlock->GetAtType());
            }
            _underlying = new Type(file, underlyingBlock);
            return;
        }
        if (block->GetType() == TagType::DW_TAG_const_type) {
            block = file.GetBlock(block->GetAtType());
            _const = true;
        }
        while (block->GetType() == TagType::DW_TAG_typedef) {
            block = file.GetBlock(block->GetAtType());
        }
        if (block->GetType() == TagType::DW_TAG_class_type) {
            _name = block->GetName();
        }
        if (block->GetType() == TagType::DW_TAG_base_type) {
            _name = block->GetName();
        }
        if (block->GetType() == TagType::DW_TAG_enumeration_type) {
            _name = block->GetName();
        }
        if (block->GetType() == TagType::DW_TAG_subroutine_type) {
            _name = "Function";
        }
    }

    bool IsPointer() const { return _pointer; }

    bool IsConst() const { return _const; }

    const std::string& GetName() const { return _name; }
    const Type* GetUnderlying() const { return _underlying; }

    std::string ToPrettyString() const {
        std::stringstream ss;
        if (_const)
            ss << "const ";
        if (!_name.empty())
            ss << _name;
        else if (_underlying != nullptr) {
            ss << "(" << _underlying->ToPrettyString() << ")";
        }
        if (_pointer)
            ss << "*";
        return ss.str();
    }

    std::string ToShortString() const{
        std::stringstream ss;
        if (_const) ss << "const ";
        if (!_name.empty()) ss << _name;
        else if (_underlying != nullptr) ss << _underlying->ToShortString();
        if (_pointer) ss << " *";
        return ss.str();
    }
};


#endif // ELF_EXPORTER_TYPE_HPP
