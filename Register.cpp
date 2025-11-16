#include "Registry.h"
#include <stdexcept> //Gives error messages when something is wrong (like duplicate IDs)

//Registry.cpp: The logic that manipulates the private mapping records_

//implement all methods define in Registry.h
//void createRecord(...);
//bool recordExists(...);
//const Record& getRecord(...);
//std::vector<std::string> listIds() const;

// * createRecord()
//Validates the ID
//Checks if record already exists
//Stores a new Record into the mapping (unordered_map)
void SimpleRegistry::createRecord(const std::string& id,
                                  const std::string& data,
                                  const std::string& owner,
                                  std::uint64_t timestamp) {
   // Check that ID is not empty 
    if (id.empty()) {
        throw std::runtime_error("ID cannot be empty");
    }

    // Check if ID already used 
    if (records_.find(id) != records_.end()) {
        throw std::runtime_error("ID already used");
    }
    // Build the new record
    Record r;
    r.id = id;
    r.owner = owner;
    r.data = data;
    r.timestamp = timestamp;
    
    // Insert into the mapping
    records_.emplace(id, std::move(r)); 
}

// * recordExists()
// Returns true if the ID exists in the mapping (checking if mapping contains key)
bool SimpleRegistry::recordExists(const std::string& id) const {
    return records_.find(id) != records_.end();
}

// * getRecord()
//Retrieves the stored Record associated with an ID
// Return 'Error' if the ID does not exist.
const Record& SimpleRegistry::getRecord(const std::string& id) const {
    auto it = records_.find(id);
  // Reject if no record found
    if (it == records_.end()) {
        throw std::runtime_error("Record does not exist");
    }
    return it->second;
}

// * listIds()
// Returns a vector containing all keys (IDs) in the mapping.
std::vector<std::string> SimpleRegistry::listIds() const {
    std::vector<std::string> ids;
    ids.reserve(records_.size());
   // Extract each mapping key (id)
    for (const auto& kv : records_) {
        ids.push_back(kv.first);
    }
    return ids;
}
