//  File cache_sim.cpp

#include <iostream>  //  For normal output: cout, endl
#include <fstream>   //  For file streams
#include <iomanip>   //  For the hex and dec stream manipulators
#include <vector>    //  std::vector
#include <string>
#include <cstddef>   //  std::size_t

using namespace std;

class Block {

	private:    // properties
    bool valid = false;
    bool dirty = false;
    unsigned tag = 0;

    public:     // member functions
    // getters
    bool isValid {return valid;}
    bool isDirty {return dirty;}
    unsigned getTag {return tag;}
    //setters
    void setValid(bool valid) {this.valid = valid;}
    void setDirty(bool dirty) {this.dirty = dirty;}
    void setTag(unsigned tag) {this.tag = tag;}
};

class Cache {
	private:    // properties
    unsigned mMemory;
    unsigned mBlockSize;
    unsigned mWayNum;       // number of ways
    unsigned mIndexNum;     // number of cache indexes
    Block *mBlocks;         // the cache

    public:
    // Constructor
    Cache(unsigned memory, unsigned blockSize, unsigned wayNum) 
        : mMemory(memory), mBlockSize(blockSize), mWayNum(wayNum),
        mIndexNum(mMemory/(mBlockSize * mWayNum)) {
            // initialize the cache size as a multidimensional array
            mBlocks = new Block[mIndexNum][mWayNum];
        }

    // processing commands
    void process(vector<pair<char, unsigned>> traces, unsigned mask) {
        for (size_t i = 0; i < traces.size(); i++) {
            // Get data from each trace
            pair<char, unsigned> trace = traces[i];
            char cmd = trace.first          // the command (read or write)
            unsigned adr = trace.second;    // the address
            adr >>= 8;                      // shift right 8 bits
            unsigned index = adr & mask;    // masking the cache index
            unsigned tag = adr >> mIndexNum;// shift 6 bits to get the tag

            Block* row = mBlocks[mIndexNum];
            cout << hitOrMiss(row, tag, cmd);
            cout << " ";
        }
    }

    // Hit or Miss?
    string hitOrMiss(const Block* row, unsigned tag, char cmd) {
        string result;
        for (size_t i = 0; i < row.size(); i++) {
            Block block = row[i];
            if (block.isValid) {        // valid block
                if(block.getTag() == tag) {     // same tag?
                    result = "hit";
                    // set dirty bit to true if it is a write, otherwise dont do anything
                    if (cmd == 'w') { block.setDirty(true); }
                } else {                // different tag
                    result = "miss with write-back";
                    // write-back a new tag
                    block.setTag(tag);
                    // set dirty bit to true if it is a write
                    if (cmd == 'w') {
                        block.setDirty(true);
                    } else {    // set it to false if it is a read
                        block.setDirty(false);
                    }
                }
            } else {                    // invalid block
                result = "miss";
                block.setTag(tag);
                // set dirty bit to true if it is a write, otherwise dont do anything
                if (cmd == 'w') { block.setDirty(true); }
            }
            // set block valid
            block.setValid(true);
        }
        return result;
    }
}; 

int main(int argc, char** argv)
{
    const unsigned indexMask1 = 0x7F;           // for masking cache 1
    const unsigned indexMask2 = 0x1F;                  // TODO: masks
    const unsigned indexMask3 = 0xF;
    const unsigned indexMask4 = 1; 

    vector<pair<char, unsigned>> memoryTraces;
    if ( argc > 1 )  //  Require a data file
    {
        ifstream fin;
        fin.open(argv[1]);
        if ( fin.good() )
        {   //  File opened successfully
            char command;
            unsigned address;
            //  hex is the hexadecimal stream manipulator
            for ( ;; )  //  Infinite loop
            {
                fin >> command;
                if ( command == 'x' )
                    break;    //  All done
                fin >> hex >> address;  //  Read address as hexadecimal
                // push command and address into the vector
                memoryTraces.push_back(pair(command, address));
                fin >> dec;   //  Reset stream to "normal" input
            }
            fin.close();   //  Close the file
        }
        else   //  Could not open file, so report error
            cout << "Could not open the command file." << endl;
    }
    else  //  User must provide a datafile
        cout << "Usage: " << endl
             << "  cache_sim <filename>" << endl;
	
	// 32KB direct mapped cache with a 256-byte block size
    Cache cache1 = new Cache(32768, 256, 1);
    cache1.process(memoryTraces, indexMask1);
	
	// 32KB 4-way set associative cache with a 256-byte block size
	Cache cache2 = new Cache(32768, 256, 4);
    cache2.process(memoryTraces, indexMask2);

	// 32KB 8-way set associative cache with a 256-byte block size
	Cache cache3 = new Cache(32768, 256, 8);
    cache3.process(memoryTraces, indexMask3);

	// 32KB fully associative cache with a 256-byte block size
	Cache cache4 = new Cache(32768, 256, 128);
    cache4.process(memoryTraces, indexMask4);
	
}