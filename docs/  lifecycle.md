Core Functions
createRecord(string _id, string _data)
Validates: 
    _id is non-empty
    _data is non-empty
    idExists[_id] == false

Creates a new Record with:
    id = _id
    owner = msg.sender
    data = _data
    timestamp = block.timestamp

Stores it in records[_id]
Marks idExists[_id] = true
Emits RecordCreated(id, owner, data, timestamp)

getRecord(string _id)
    Reverts if idExists[_id] is false.
    Returns all fields of the record.

recordExists(string _id)
    Returns idExists[_id]

Blockchain Features Used

Immutability: Once deployed, the contract code cannot change. Record
history is preserved across the chain.

Public verifiability: Anyone can query getRecord or inspect
RecordCreated events to independently confirm claims.

Decentralized identity: Ownership is based on Ethereum addresses. The
owner field is derived from msg.sender without a central identity
provider.

Timestamps: block.timestamp records when a claim was created on chain.

Event logs: RecordCreated provides an append-only audit log.



Tooling / SDKs
    Solidity for the smart contract.
    Hardhat as the development environment (compilation, testing, deployment).
    @nomicfoundation/hardhat-toolbox and ethers.js for:
        Contract interactions in tests 
        Deployment scripts
    Mocha/Chai via Hardhat for the JS test runner and assertions.

Security / Design Considerations
    IDs are user-chosen; collisions are prevented by idExists.