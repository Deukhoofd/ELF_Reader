#ifndef ELF_EXPORTER_CONFIG_HPP
#define ELF_EXPORTER_CONFIG_HPP

#include <utility>
#include <vector>
#include <string>

class Config{
private:
    std::vector<std::string> _files;
    std::string _namespace;
    std::string _outputFile;
public:
    Config(std::vector<std::string>  files, std::string  ns, std::string outputFile)
        : _files(std::move(files)), _namespace(std::move(ns)), _outputFile(std::move(outputFile)) {}

    inline const std::vector<std::string>& GetFiles() const{
        return _files;
    }

    inline const std::string GetNamespace() const{
        return _namespace;
    }

    inline const std::string GetOutputFile() const{
        return _outputFile;
    }
};

#endif // ELF_EXPORTER_CONFIG_HPP
