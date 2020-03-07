#include "File.hpp"
#include <iostream>
#include <regex>
#include "../../extern/pstream.h"
#include "Block.hpp"

static std::regex lineMatcher("\\s*<(\\d+)><(\\w+)>:.*\\((.*)\\)");

static Block* CreateBlock(uint8_t level, TagType type){
    switch (type){
        default: return new Block(level, type);
    }
}

File File::Read(const std::string& file, const std::string& ns) {
    std::stringstream command;
    command << "readelf -wi " << file;
    redi::ipstream exec(command.str(), redi::pstreams::pstdout);
    std::string line;
    Block* currentBlock = nullptr;
    size_t lineNr = 0;

    File f;
    while (std::getline(exec.out(), line)) {
        lineNr++;
        std::smatch match;
        if (std::regex_match(line, match, lineMatcher)) {
            auto level = std::stoi(match[1].str());
            auto index = std::stoi(match[2].str(), nullptr, 16);
            TagType type;
            if (!TagTypeHelper::TryParse(match[3].str().c_str(), type)) {
                throw std::logic_error("invalid tagtype " + match[3].str() + " at line " + std::to_string(lineNr) + "\n" + line);
            }
            auto block = CreateBlock(level, type);
            if (currentBlock != nullptr)
                currentBlock->SetNext(block);
            currentBlock = block;
            f._blocks.insert({index, block});
        }
        else if (currentBlock != nullptr){
            currentBlock->AddData(line);
        }
    }
    return f;
}
