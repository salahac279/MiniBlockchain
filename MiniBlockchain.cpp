#include "picosha2.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Transaction {
    string sender;
    string receiver;
    int amount;

public:
    Transaction(string Sender, string Receiver, int Amount) : sender(Sender), receiver(Receiver), amount(Amount) {
        cout << "A transaction has been created" << endl;
    }

    string getSender() { return sender; }
    string getReceiver() { return receiver; }
    int getAmount() { return amount; }
};

class Block {
    string previous_hash;
    Transaction transaction;
    int nonce;
    string Timestamp;
    string hash;

public:
    Block(string previousHx, Transaction trx, int Nonce = 0)
        : previous_hash(previousHx), transaction(trx), nonce(Nonce) {
        
        time_t timestamp = time(NULL);
        struct tm datetime = *localtime(&timestamp);
        Timestamp = asctime(&datetime);

        // Generate initial hash
        hash = generate_hash(getInput());
    }

    void printBlock() {
        cout << "Block Timestamp: " << Timestamp;
        cout << "Block Hash: " << hash << endl;
        cout << "Previous Hash: " << previous_hash << endl;
        cout << "Transaction -> " << transaction.getSender() << " sent " << transaction.getAmount() 
             << " coins to " << transaction.getReceiver() << endl;
    }

    string generate_hash(string Content) {
        return picosha2::hash256_hex_string(Content);
    }

    string getHash() { return hash; }
    string getPreviousHash() { return previous_hash; }

    void set_BlockData(string Hash, int Nonce) {
        hash = Hash;
        nonce = Nonce;
    }

    string getInput() {
        return previous_hash + Timestamp + transaction.getSender() + transaction.getReceiver() 
               + to_string(transaction.getAmount()) + to_string(nonce);
    }
};

class Blockchain {
    vector<Block> chain;
    vector<Transaction> all_transactions;

public:
    Blockchain() {
        cout << "Blockchain Created!" << endl;

        // Create the Genesis Block
        Transaction GenesisTrx("Satoshi", "Saladeen", 1);
        Block GenesisBlock("0", GenesisTrx, 1);
        chain.push_back(GenesisBlock);
        all_transactions.push_back(GenesisTrx);

        cout << "The Genesis Block has been created!" << endl;
    }

    Block PoW(Block block, int difficulty = 2) {
        int Nonce = 0;
        string Hx;
        string diff(difficulty, '0');

        do {
            block.set_BlockData(block.generate_hash(block.getInput()), Nonce);
            Hx = block.getHash();
            Nonce++;
        } while (Hx.substr(0, difficulty) != diff);

        cout << "Block mined: " << Hx << endl;
        return block;
    }

    void add_Block(Transaction trx) {
        Block NewBlock = Block(chain.back().getHash(), trx);
        NewBlock = PoW(NewBlock, 2);  // Adjust difficulty for better mining
        chain.push_back(NewBlock);
        all_transactions.push_back(trx);
        cout << "Block has been added to the chain!" << endl;
    }

    bool validateChain() {
        for (size_t i = 1; i < chain.size(); i++) {
            Block current = chain[i];
            Block previous = chain[i - 1];

            if (current.getHash() != current.generate_hash(current.getInput())) {
                cout << "The chain is NOT valid! (Tampered block found)" << endl;
                return false;
            }

            if (previous.getHash() != current.getPreviousHash()) {
                cout << "The chain is NOT valid! (Invalid hash linkage)" << endl;
                return false;
            }
        }

        cout << "The blockchain is valid!" << endl;
        return true;
    }

    void printBlockchain() {
        cout << "\n==== Blockchain Data ====" << endl;
        for (Block block : chain) {
            block.printBlock();
            cout << "------------------------" << endl;
        }
    }
};

int main() {
    // Creating Transactions
    Transaction Trx1("Bob", "John", 10);
    Transaction Trx2("Alice", "Mark", 5);
    Transaction Trx3("Charlie", "David", 20);
    Transaction Trx4("Eve", "Frank", 15);

    cout << "------------------------" << endl;
    
    // Creating Blockchain
    Blockchain BNB;
    
    // Adding Blocks
    BNB.add_Block(Trx1);
    BNB.add_Block(Trx2);
    BNB.add_Block(Trx3);
    BNB.add_Block(Trx4);

    // Validate Blockchain
    BNB.validateChain();

    // Print Blockchain
    BNB.printBlockchain();

    return 0;
}

