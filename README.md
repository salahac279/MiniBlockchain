# MiniBlockchain
# A Simple Blockchain in C++

This is a basic blockchain implementation in C++ using SHA-256 hashing for security and a Proof-of-Work (PoW) mechanism for mining. Each block contains a transaction, a timestamp, and a reference to the previous block's hash, ensuring an immutable chain.

## Features

- Implements SHA-256 hashing for block security
- Proof-of-Work (PoW) system to validate new blocks
- Transaction structure to store sender, receiver, and amount
- Blockchain validation to check integrity after adding blocks
- Genesis block (first block in the chain)

## Installation and Compilation

### Install a C++ Compiler

Make sure you have a C++ compiler installed.

For Ubuntu/Linux:
```sh
sudo apt update && sudo apt install g++
```

For Windows:  
- Download and install MinGW or use WSL.

### Clone the Repository

```sh
git clone https://github.com/YOUR_USERNAME/SimpleBlockchain.git
cd SimpleBlockchain
```

### Add the SHA-256 Library

This project uses picosha2, a lightweight SHA-256 implementation. Since it is not included in the repository, you need to download it manually.

#### Option 1: Download picosha2 Manually
- Go to [PicoSHA2 Repository](https://github.com/okdshin/PicoSHA2).
- Download the `picosha2.h` file.
- Place it inside your project folder.

#### Option 2: Use wget to Download It (Linux/macOS)
```sh
wget https://raw.githubusercontent.com/okdshin/PicoSHA2/master/picosha2.h -P .
```

### Compile the Code
```sh
g++ -o blockchain main.cpp -std=c++11
```

### Run the Program
```sh
./blockchain
```

## How the Code Works

### Creating the Blockchain

When you run the program, it initializes the blockchain with a Genesis Block.

### Transactions

Each transaction consists of:
- Sender: The person sending the coins
- Receiver: The person receiving the coins
- Amount: The number of coins transferred

Example:
```cpp
Transaction Trx1("Alice", "Bob", 10);
Transaction Trx2("Bob", "Charlie", 5);
```

### Adding a Block to the Blockchain

Blocks are added to the chain using Proof-of-Work (PoW):
```cpp
BNB.add_Block(Trx1);
BNB.add_Block(Trx2);
```

The blockchain mines the block and ensures it meets the difficulty level before adding it.

## Example Output

```
Blockchain Created!
The Genesis Block has been created!
A transaction has been created
A transaction has been created
Hash is: 00a1b2c3d4...
The block has been mined successfully!
Block has been added!
Hash is: 00e5f6g7h8...
The block has been mined successfully!
Block has been added!
The blockchain is valid!
```

## Customization

### Adjust the Mining Difficulty

The Proof-of-Work (PoW) difficulty determines how hard it is to mine a block. You can increase the difficulty in `PoW()`:

```cpp
Block PoW(Block block, int difficulty = 4);
```

Increasing difficulty will make mining take longer but improve security.

### Modify Transaction Rules

You can update how transactions are created by modifying the `Transaction` class.

## Future Improvements

- Implement multiple transactions per block
- Add wallet balances for users
- Implement a peer-to-peer network for distributed blockchain
- Optimize Proof-of-Work difficulty adjustment

## License

This project is open-source under the MIT License. See the LICENSE file for details.

## Contributing

Feel free to fork this repository, submit pull requests, or open issues to improve this blockchain.



