#include "Registry.h"
#include <stdexcept>

// Create a new record
void SimpleRegistry::createRecord(const std::string& id,
                                  const std::string& data,
                                  const std::string& owner,
                                  std::uint64_t timestamp) {

    if (id.empty()) {
        throw std::runtime_error("ID cannot be empty");
    }
    if (records_.find(id) != records_.end()) {
        throw std::runtime_error("ID already used");
    }

    Record r;
    r.id = id;
    r.owner = owner;
    r.data = data;
    r.timestamp = timestamp;

    records_.emplace(id, std::move(r));
}

// Check existence
bool SimpleRegistry::recordExists(const std::string& id) const {
    return records_.find(id) != records_.end();
}

// Get a record or throw
const Record& SimpleRegistry::getRecord(const std::string& id) const {
    auto it = records_.find(id);
    if (it == records_.end()) {
        throw std::runtime_error("Record does not exist");
    }
    return it->second;
}

// List all IDs
std::vector<std::string> SimpleRegistry::listIds() const {
    std::vector<std::string> ids;
    ids.reserve(records_.size());
    for (const auto& kv : records_) ids.push_back(kv.first);
    return ids;
}