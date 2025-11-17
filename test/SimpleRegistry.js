import { expect } from "chai";
import { ethers } from "hardhat";

describe("SimpleRegistry", function () {
  let Registry, registry, owner, addr1;

  beforeEach(async function () {
    [owner, addr1] = await ethers.getSigners();
    Registry = await ethers.getContractFactory("SimpleRegistry");
    registry = await Registry.deploy();
    await registry.waitForDeployment();
  });

  it("creates a record with correct fields and emits event", async function () {
    const tx = await registry.createRecord("id-123", "my first claim");
    const receipt = await tx.wait();

    const [id, recOwner, data, timestamp] = await registry.getRecord("id-123");

    expect(id).to.equal("id-123");
    expect(recOwner).to.equal(owner.address);
    expect(data).to.equal("my first claim");
    expect(timestamp).to.be.gt(0);

    const parsedEvents = receipt.logs.map((log) =>
      registry.interface.parseLog(log)
    );
    const createdEvent = parsedEvents.find(
      (e) => e.name === "RecordCreated"
    );

    expect(createdEvent.args.id).to.equal("id-123");
    expect(createdEvent.args.owner).to.equal(owner.address);
    expect(createdEvent.args.data).to.equal("my first claim");
    expect(createdEvent.args.timestamp).to.equal(timestamp);
  });

  it("prevents duplicate IDs", async function () {
    await registry.createRecord("dup-id", "first");
    await expect(
      registry.createRecord("dup-id", "second")
    ).to.be.revertedWith("ID already used");
  });

  it("rejects empty id", async function () {
    await expect(
      registry.createRecord("", "data")
    ).to.be.revertedWith("ID required");
  });

  it("rejects empty data", async function () {
    await expect(
      registry.createRecord("id-1", "")
    ).to.be.revertedWith("Data required");
  });

  it("tracks existence correctly", async function () {
    expect(await registry.recordExists("x")).to.equal(false);
    await registry.createRecord("x", "data");
    expect(await registry.recordExists("x")).to.equal(true);
  });

  it("allows multiple users to create different records", async function () {
    await registry.connect(owner).createRecord("owner-id", "owner-data");
    await registry.connect(addr1).createRecord("user-id", "user-data");

    const [, ownerOfOwnerId] = await registry.getRecord("owner-id");
    const [, ownerOfUserId] = await registry.getRecord("user-id");

    expect(ownerOfOwnerId).to.equal(owner.address);
    expect(ownerOfUserId).to.equal(addr1.address);
  });

  it("reverts when fetching non-existent record", async function () {
    await expect(
      registry.getRecord("nope")
    ).to.be.revertedWith("Record does not exist");
  });
});
