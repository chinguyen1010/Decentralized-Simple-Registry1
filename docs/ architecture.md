# Decentralized Simple Registry – Architecture

## Problem

People need a public, tamper-proof record for small claims, certifications, or
asset provenance that is not tied to a centralized database or authority.

## High-Level Solution

We deploy an Ethereum smart contract (`SimpleRegistry`) that lets any user:

- Submit a text record (claim, serial number, certification link, etc.)
- Attach it to a unique string ID
- Store the creator address and creation timestamp

Once written, the record is publicly readable and cannot be overwritten under
the same ID, giving a permanent, verifiable history.

## Data Model

### Struct

```solidity
struct Record {
    string id;
    address owner;
    string data;
    uint256 timestamp;
}

mapping(string => Record) private records; //records holds the full record
mapping(string => bool) private idExists; 
