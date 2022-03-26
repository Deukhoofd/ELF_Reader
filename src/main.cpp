#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "../extern/json.hpp"
#include "Config.hpp"
#include "DWARF/File.hpp"
#include "Enum.hpp"
#include "Function.hpp"
using json = nlohmann::json;

Config ParseArgs(int argc, char* argv[]) {
    std::string ns = "";
    std::string of;
    std::vector<std::string> files;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            ns = std::string(argv[i + 1]);
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            i++;
            while (i < argc) {
                if (*argv[i] == '-') {
                    i--;
                    break;
                }
                files.emplace_back(argv[i]);
                i++;
            }
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            of = std::string(argv[i + 1]);
        }
    }
    return Config(files, ns, of);
}

void to_json(json& j, const Type& value) { j = value.ToShortString(); }

void to_json(json& j, const FunctionParameter& value) {
    j = json{{"name", value.GetName()}, {"type", value.GetType()}};
}

void to_json(json& j, const Function& value) {
    j = json{{"name", value.GetName()},
             {"filename", value.GetFileName()},
             {"returns", value.GetReturnType()},
             {"parameters", value.GetParameters()}};
}

void to_json(json& j, const Enum& value) {
    j = json{{"name", value.GetName()},
             {"filename", value.GetFileName()},
             {"byteSize", value.GetByteSize()},
             {"values", value.GetValues()}};
}

int main(int argc, char* argv[]) {
    auto cfg = ParseArgs(argc, argv);
    std::cout << "Namespace: " << cfg.GetNamespace() << std::endl;
    std::cout << "Output File: " << cfg.GetOutputFile() << std::endl;
    std::cout << "Files: " << std::endl;
    for (const auto& v : cfg.GetFiles()) {
        std::cout << "\t- " << v << std::endl;
    }

    std::vector<Function> functions;
    std::vector<Enum> enums;
    for (const auto& v : cfg.GetFiles()) {
        auto file = File::Read(v, cfg.GetNamespace());
        std::cout << "Found " << file.GetBlocks().size() << " blocks in file " << v << std::endl;

        std::unordered_set<std::string> foundEnums;

        for (auto kv : file.GetBlocks()) {
            auto block = kv.second;
            if (!block->GetName().empty() && block->GetType() == TagType::DW_TAG_subprogram &&
                block->IsExternal() &&
                strncmp(block->GetName().c_str(), cfg.GetNamespace().c_str(), cfg.GetNamespace().size()) == 0) {
                auto function = Function(file, block);
                functions.push_back(function);
            } else if (block->GetType() == TagType::DW_TAG_enumeration_type && !block->GetName().empty()) {
                if (block->GetName()[0] == '_') {
                    continue;
                }
                if (foundEnums.find(block->GetName()) == foundEnums.end()) {
                    auto enum_ = Enum(file, block);
                    enums.push_back(enum_);
                    foundEnums.insert(block->GetName());
                }
            }
        }
    }

    std::cout << "Found " << functions.size() << " functions in " << cfg.GetFiles().size() << " file(s)" << std::endl;
    std::cout << "Found " << enums.size() << " enums in " << cfg.GetFiles().size() << " file(s)" << std::endl;

    json o;
    o["functions"] = functions;
    o["enums"] = enums;

    auto outFile = cfg.GetOutputFile();
    if (outFile.empty()) {
        outFile = "exported_data.json";
    }
    std::ofstream outfile(outFile);
    outfile << o << std::endl;
    outfile.close();
    std::cout << "Wrote exported data to file " << outFile << std::endl;
}
