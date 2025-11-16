// SPDX-License-Identifier: MIT
pragma solidity ^0.8.30; // use Solidity version 0.8.30
//Solidity contract
/**
 * A smart contract that allows any user to submit a text record
 * (e.g., a claim, a product serial number, a certification link)
 * along with a unique ID, creating a timestamped, permanent entry
 * on the blockchain.
 */



contract SimpleRegistry {
    // Define data strucrture for each stored record
    struct Record {
        string id;          // unique string key (serial number, claim ID, etc.)
        address owner;      // Ethereum address that created the record
        string data;        // text record (claim, serial number, link, etc.)
        uint256 timestamp;  // when the record was created (block.timestamp)
    }

    // Mapping from unique ID -> Record (Mapping to Store Records)
    // Efficiency: store permanent (works exactly like a dictionary or hash map)
    // Each unique ID maps to a Record struct

    mapping(string => Record) private records;

    // Track used IDs
    mapping(string => bool) private idUsed;

    // Event declaration: Emits a log entry whenever a record is created.
    event RecordCreated(
        string indexed id,
        address indexed owner,
        string data,
        uint256 timestamp
    );

    /**
     * createRecord:
     * Any user (msg.sender) can call this.
     * _id = non-empty string
     * _data =  text (claim, serial number, certification link, etc.).
     * record stored permanently with a timestamp
     */

// createRecord() — MAIN FUNCTION
    function createRecord(string calldata _id, string calldata _data) external {
        require(bytes(_id).length > 0, "ID cannot be empty"); //check for empty ID
        require(!idUsed[_id], "ID already used"); //Prevents duplicate

// Store Record
        records[_id] = Record({ //Creates a new permanent entry
            id: _id,
            owner: msg.sender,
            data: _data,
            timestamp: block.timestamp
        });
        // Marks ID as used
        idUsed[_id] = true;

        emit RecordCreated(_id, msg.sender, _data, block.timestamp);
    }


    // recordExists() - MAINFUNCTION 
    // Returns true or false depending on whether an ID exists
    // Check if a record with this ID exists
    function recordExists(string calldata _id) external view returns (bool) {
        return idUsed[_id];
    }

//getRecord() - MAIN FUNCTION
//Checks if the record exists
//Loads the Record struct
//Returns all the stored fields
    // Read a record by ID
    function getRecord(string calldata _id)
        external
        view
        returns (string memory id, address owner, string memory data, uint256 timestamp)
    {
        require(idUsed[_id], "Record does not exist");
        Record storage r = records[_id];
        return (r.id, r.owner, r.data, r.timestamp);
    }
}
