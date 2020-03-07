
#include "Function.hpp"

Function::Function(const File& file, Block* block) {
    _name = block->GetName();
    _returnType = ((block->GetAtType() == 0) ? Type() : Type(file, file.GetBlock(block->GetAtType())));

    auto c= block->GetNext();
    while (c != nullptr){
        if (c->GetLevel() == block->GetLevel())
            break;
        if (c->GetType() == TagType::DW_TAG_formal_parameter &&  c->GetLevel() == block->GetLevel() + 1){
            _parameters.emplace_back(file, c);
        }
        c = c->GetNext();
    }
}
FunctionParameter::FunctionParameter(const File& file, Block* block) {
    _name = block->GetName();
    _type = ((block->GetAtType() == 0) ? Type() : Type(file, file.GetBlock(block->GetAtType())));
}
