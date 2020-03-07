#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../extern/json.hpp"
#include "Config.hpp"
#include "DWARF/File.hpp"
#include "Function.hpp"
using json = nlohmann::json;

Config ParseArgs(int argc, char* argv[]) {
    std::string ns;
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


void to_json(json& j, const Type& value) {
    j = value.ToShortString();
}

void to_json(json& j, const FunctionParameter& value) {
    j = json{{"name", value.GetName()}, {"type", value.GetType()}};
}

void to_json(json& j, const Function& value) {
    j = json{{"name", value.GetName()}, {"returns", value.GetReturnType()}, {"parameters", value.GetParameters()}};
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
    for (const auto& v : cfg.GetFiles()) {
        auto file = File::Read(v, cfg.GetNamespace());
        std::cout << "Found " << file.GetBlocks().size() << " blocks" << std::endl;
        for (auto kv : file.GetBlocks()) {
            auto block = kv.second;
            if (!(block->GetLevel() == 1 && !block->GetName().empty() &&
                  block->GetType() == TagType::DW_TAG_subprogram && block->IsExternal() &&
                  strncmp(block->GetName().c_str(), cfg.GetNamespace().c_str(), cfg.GetNamespace().size()) == 0))
                continue;

            auto function = Function(file, block);
            std::cout << "Got function by name of " << function.GetName() << " with return type "
                      << function.GetReturnType().ToPrettyString() << std::endl;
            for (const auto& par : function.GetParameters()) {
                std::cout << "\t - " << par.GetName() << " " << par.GetType().ToPrettyString() << std::endl;
            }
            functions.push_back(function);
        }
    }
    json o;
    o["functions"] = functions;

    auto outFile = cfg.GetOutputFile();
    if (outFile.empty()){
        outFile = "exported_functions.json";
    }

    std::ofstream outfile (outFile);
    outfile << o << std::endl;
    outfile.close();
}
