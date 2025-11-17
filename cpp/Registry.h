#ifndef SIMPLE_REGISTRY_H
#define SIMPLE_REGISTRY_H

#include <string>
#include <unordered_map>
#include <cstdint>
#include <vector>

// Record struct: mirrors Solidity struct
struct Record {
    std::string id;
    std::string owner;
    std::string data;
    std::uint64_t timestamp;
};

// SimpleRegistry: local C++ mirror of Solidity contract
class SimpleRegistry {
public:
    void createRecord(const std::string& id,
                      const std::string& data,
                      const std::string& owner,
                      std::uint64_t timestamp);

    bool recordExists(const std::string& id) const;

    const Record& getRecord(const std::string& id) const;

    std::vector<std::string> listIds() const;

private:
    std::unordered_map<std::string, Record> records_; // id → Record
};

#endif
