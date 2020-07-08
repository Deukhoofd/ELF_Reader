#ifndef ELF_EXPORTER_TYPE_HPP
#define ELF_EXPORTER_TYPE_HPP

#include <string>
#include "DWARF/Block.hpp"
#include "DWARF/File.hpp"
#include "../extern/json.hpp"

using json = nlohmann::json;

class Type {
    bool _pointer = false;
    bool _reference = false;
    bool _const = false;
    Type *_underlying = nullptr;
    std::string _name = "";

public:
    Type() { _name = "void"; }

    Type(const File &file, Block *block) {
        if (block->GetType() == TagType::DW_TAG_restrict_type) {
            block = file.GetBlock(block->GetAtType());
        }

        if (block->GetType() == TagType::DW_TAG_pointer_type) {
            _pointer = true;
            if (block->GetAtType() != 0) {
                auto underlyingBlock = file.GetBlock(block->GetAtType());
                if (underlyingBlock->GetType() == TagType::DW_TAG_const_type) {
                    _const = true;
                    if (underlyingBlock->GetAtType() != 0)
                        underlyingBlock = file.GetBlock(underlyingBlock->GetAtType());
                }
                _underlying = new Type(file, underlyingBlock);
            }
            return;
        }
        if (block->GetType() == TagType::DW_TAG_reference_type) {
            _reference = true;
            if (block->GetAtType() != 0) {
                auto underlyingBlock = file.GetBlock(block->GetAtType());
                if (underlyingBlock->GetType() == TagType::DW_TAG_const_type) {
                    _const = true;
                    if (underlyingBlock->GetAtType() != 0)
                        underlyingBlock = file.GetBlock(underlyingBlock->GetAtType());
                }
                _underlying = new Type(file, underlyingBlock);
            }
            return;
        }
        if (block->GetType() == TagType::DW_TAG_const_type) {
            if (block->GetAtType() != 0)
                block = file.GetBlock(block->GetAtType());
            _const = true;
        }
        while (block->GetType() == TagType::DW_TAG_typedef) {
            if (block->GetAtType() != 0)
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
        if (_name == "") {
            throw std::logic_error("Didn't set type name.");
        }
    }

    bool IsPointer() const { return _pointer; }

    bool IsReference() const { return _reference; }

    bool IsConst() const { return _const; }

    const std::string &GetName() const { return _name; }

    const Type *GetUnderlying() const { return _underlying; }

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
        if (_reference)
            ss << "&";
        return ss.str();
    }

    std::string ToShortString() const {
        std::stringstream ss;
        if (_const) ss << "const ";
        if (!_name.empty()) ss << _name;
        else if (_underlying != nullptr) ss << _underlying->ToShortString();
        else ss << "void";
        if (_pointer) ss << " *";
        if (_reference) ss << " &";
        return ss.str();
    }
};


#endif // ELF_EXPORTER_TYPE_HPP
