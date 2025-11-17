// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

/// @title Decentralized Simple Registry
/// @notice Tamper-proof registry for small claims, certifications, and asset provenance
contract SimpleRegistry {
    /// @notice A single registry record
    /// @param id User-supplied unique string identifier
    /// @param owner Address that created the record
    /// @param data Arbitrary text payload (claim, serial number, URL, etc.)
    /// @param timestamp Block timestamp when the record was created
    struct Record {
        string id;
        address owner;
        string data;
        uint256 timestamp;
    }

    /// @notice Mapping from id string to the stored Record
    mapping(string => Record) private records;

    /// @notice Tracks whether an id has already been used
    mapping(string => bool) private idExists;

    /// @notice Emitted whenever a new record is created
    /// @param id Unique record identifier
    /// @param owner Address that created the record
    /// @param data Text payload associated with the record
    /// @param timestamp Block timestamp at creation
    event RecordCreated(
        string indexed id,
        address indexed owner,
        string data,
        uint256 timestamp
    );

    /// @notice Create a new record
    /// @dev Reverts if id is empty, data is empty, or id is already used
    /// @param _id Unique id string chosen by the user
    /// @param _data Arbitrary text payload
    function createRecord(string memory _id, string memory _data) external {
        require(bytes(_id).length > 0, "ID required");
        require(bytes(_data).length > 0, "Data required");
        require(!idExists[_id], "ID already used");

        Record memory rec = Record({
            id: _id,
            owner: msg.sender,
            data: _data,
            timestamp: block.timestamp
        });

        records[_id] = rec;
        idExists[_id] = true;

        emit RecordCreated(_id, msg.sender, _data, block.timestamp);
    }

    /// @notice Read a record by id
    /// @dev Reverts if the id does not exist
    /// @param _id Unique id string
    /// @return id The id stored
    /// @return owner The creator of the record
    /// @return data The associated text payload
    /// @return timestamp When the record was created
    function getRecord(string memory _id)
        external
        view
        returns (string memory id, address owner, string memory data, uint256 timestamp)
    {
        require(idExists[_id], "Record does not exist");

        Record memory rec = records[_id];
        return (rec.id, rec.owner, rec.data, rec.timestamp);
    }

    /// @notice Check whether a record id exists
    /// @param _id Unique id string
    /// @return exists True if the record exists
    function recordExists(string memory _id) external view returns (bool exists) {
        return idExists[_id];
    }
}
