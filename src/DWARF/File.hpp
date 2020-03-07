#ifndef ELF_EXPORTER_FILE_HPP
#define ELF_EXPORTER_FILE_HPP

#include <map>
#include "../Config.hpp"
#include "Block.hpp"
class File {
    std::map<uint32_t, Block*> _blocks;

public:
    static File Read(const std::string& file, const std::string& ns);

    ~File() {
        for (auto b : _blocks) {
            delete b.second;
        }
    }

    const std::map<uint32_t, Block*>& GetBlocks() const { return _blocks; }

    Block* GetBlock(uint32_t key) const {
        return _blocks.at(key);
    }
};

#endif // ELF_EXPORTER_FILE_HPP
