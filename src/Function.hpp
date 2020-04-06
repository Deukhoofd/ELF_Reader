#ifndef ELF_EXPORTER_FUNCTION_HPP
#define ELF_EXPORTER_FUNCTION_HPP
#include <string>
#include <vector>
#include "DWARF/File.hpp"
#include "Type.hpp"

class FunctionParameter {
    std::string _name;
    Type _type;

public:
    FunctionParameter(const File& file, Block* block);

    const std::string& GetName() const { return _name; }
    const Type& GetType() const { return _type; }
};

class Function {
    std::string _name;
    std::string _fileName;

    Type _returnType;
    std::vector<FunctionParameter> _parameters;

public:
    Function(const File& file, Block* block);

    const std::string& GetName() const { return _name; }
    const std::string& GetFileName() const { return _fileName; }
    const Type& GetReturnType() const { return _returnType; }
    const std::vector<FunctionParameter>& GetParameters() const { return _parameters; }

};



#endif // ELF_EXPORTER_FUNCTION_HPP
