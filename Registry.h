//Registry.h (header file): Define Record struct and the Registry class
//Struct: Record
//Mapping: std::unordered_map<std::string, Record>
//Function: createRecord(...)


//Struct: Record
#ifndef SIMPLE_REGISTRY_H
#define SIMPLE_REGISTRY_H

#include <string>
#include <unordered_map>
#include <cstdint>
#include <vector>

//Record Struct: A Struct to define the record (e.g., id, owner _ address, data _ string, timestamp)

struct Record {
    std::string id;          // unique ID
    std::string owner;       // owner address (string)
    std::string data;        // text record: claim, serial number, etc.
    std::uint64_t timestamp; // unix timestamp
};

//Mapping to store the records (e.g., mapping of unique id to the Record struct)
//Dedlared methods for Register.cpp to implement
//void createRecord(...);
//bool recordExists(...);
//const Record& getRecord(...);
//std::vector<std::string> listIds() const;

class SimpleRegistry {
public:
    // Function createRecord(...) = Create a new record (rejct if id already exists or invalid)
    void createRecord(const std::string& id,
                      const std::string& data,
                      const std::string& owner,
                      std::uint64_t timestamp);

    // Check if a record exists
    bool recordExists(const std::string& id) const;

    // Get a record by id (reject if not found)
    const Record& getRecord(const std::string& id) const;

    // Return all record IDs
    std::vector<std::string> listIds() const;

private:
    //Mapping: std::unordered_map<std::string, Record>
    // Mapping: id -> Record
    std::unordered_map<std::string, Record> records_;
};

#endif // SIMPLE_REGISTRY_H
