# Decentralized-Simple-Registry  (BUBlockchain Hackathon)


1. Problem Statement: People need a public, tamper-proof record for small
claims, certifications, or asset provenance that is not tied to a centralized
database.

2. Proposed Solution: A contract that allows any user to submit a text record
(e.g., a claim, a product serial number, a certification link) along with a
unique ID, creating a timestamped, permanent entry.

● Core Smart Contract Logic:
○ A Struct to define the record (e.g., id, owner_address, data_string,
timestamp)

○ A Mapping to store the records (e.g., mapping of unique id to the
Record struct)

○ A function createRecord(string memory_id, string memory_data) that checks if the ID is already used and then saves the new record.



3. System Architecture
<img width="1377" height="588" alt="Screenshot 2025-11-17 at 1 41 00 PM" src="https://github.com/user-attachments/assets/69176a57-8804-4f85-8b7d-8af779a087f7" />



5. Smart Contract Design
   
Record Struct

struct Record {

  string id;
  
  address owner;
  
  string data;
  
  uint256 timestamp;
  
}

Key Functions:

Function	Description

createRecord(id, data)	Creates a new record, enforces unique IDs

getRecord(id)	          Returns stored record fields

recordExists(id)	      Checks if ID has been used

Event RecordCreated	    Logs record creation for off-chain use




5. Features Using Blockchain Technology

Immutable storage via EVM mapping(string => Record)

Trustless identity using msg.sender

Auditable creation time using block.timestamp

Event logs enabling scalable off-chain indexing & verification

Permissionless usage — any address can store records



6. How the Project Works (Technical Overview) SDKs / Tools Used

- Solidity 0.8.20

- Hardhat development environment

- Ethers.js for contract interaction

- Chai for contract testing

- Node.js for scripting

- C++17 for off-chain demo mirror

Why blockchain makes this possible:

- Data cannot be modified after creation

- No central party required to trust

- Wallets inherently create identity bindings

- Event logs enable efficient record tracking outside the chain



7. Project Structure
Decentralized-Simple-Registry/

contracts/

    SimpleRegistry.sol
cpp/

    main.cpp

    Registry.cpp

    Registry.h

    
scripts/

    deploy.js

test/

    SimpleRegistry.js

docs/

    architecture.md

    lifecycle.md

LICENSE

README.md

hardhat.config.js

package.json

package-lock.json


