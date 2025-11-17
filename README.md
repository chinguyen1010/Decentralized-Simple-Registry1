# Decentralized-Simple-Registry1
BU BlockChain hackathon Nov 16, 2025

1. Problem Overview

People often need a public, tamper-proof place to store important information such as:

small claims

certification proofs

product serial numbers

asset provenance

Today, these records usually rely on centralized databases with trust, transparency, and durability limitations.

On public blockchains, users are anonymous, and no standard registry exists that allows anyone to verify claims or certificates in a trustless way.


2. Proposed Solution

A smart contract that allows any user to submit a unique ID + text data, automatically storing:

ID

creator’s blockchain address

arbitrary text (claim, certification link, serial number, etc.)

timestamp

All entries are:

immutable

publicly verifiable

permanently on-chain

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


