//  File cache_sim.cpp

#include <iostream>  //  For normal output: cout, endl
#include <fstream>   //  For file streams
#include <iomanip>   //  For the hex and dec stream manipulators
#include <vector>    //  std::vector
#include <string>
#include <cstddef>   //  std::size_t
#include <math.h>    //  log2

using namespace std;

class Block {

	private:    // properties
    bool valid = false;
    bool dirty = false;
    unsigned tag = 0;

    public:     // member functions
    // empty constructor
    Block() {
    }
    // getters
    bool isValid() {return this->valid;}
    bool isDirty() {return this->dirty;}
    unsigned getTag() {return this->tag;}
    //setters
    void setValid(bool valid) {this->valid = valid;}
    void setDirty(bool dirty) {this->dirty = dirty;}
    void setTag(unsigned tag) {this->tag = tag;}
};

class Cache {
public:                     // properties
    unsigned mMemory;
    unsigned mBlockSize;
    unsigned mWayNum;       // number of ways
    unsigned mRowNum;     // number of cache indexes
    unsigned mIndex;
    unsigned mOffset;
    unsigned mHitTally = 0;     // number of hits
    unsigned mMissWBTally = 0;  // number of miss with write back
    unsigned mMissTally = 0;    // number of miss
    vector<vector<Block>> mBlocks;  // the cache

    // Constructor
    Cache(unsigned memory, unsigned blockSize, unsigned wayNum)
        {   
            mMemory = memory;
            mBlockSize = blockSize;
            mWayNum = wayNum;
            mRowNum = (memory / (blockSize * wayNum));
            // initialize the cache as a multidimensional array
            mBlocks = vector<vector<Block>>(mRowNum, vector<Block>(wayNum));
            // TODO: check me
            mIndex = log2 (mRowNum / wayNum);  // index = log2(number of rows)
            mOffset = log2 (memory / mRowNum); // offset = log2(row size)
        }

    // processing commands
    void process(vector<pair<char, unsigned>> traces, unsigned mask) {
        for (size_t i = 0; i < traces.size(); i++) {
            // Get data from each trace
            pair<char, unsigned> trace = traces[i];
            char cmd = trace.first;         // the command (read or write)
            unsigned adr = trace.second;    // the address
            // TODO: check me
            adr >>= mOffset;                // shift right 8 bits (block offset)
            unsigned index = adr & mask;    // masking the cache index
            unsigned tag = adr >> mIndex;   // shift 'offset; bits to get the tag 

            vector<Block>& row = mBlocks[index];
            hitOrMiss(row, tag, cmd);
        }
    }

    // Hit or Miss?
    void hitOrMiss(vector<Block>& row, unsigned tag, char cmd) {
        unsigned mValidTally = 0;
        unsigned random = (mWayNum > 1) ? (rand() % (mWayNum)) : 0;    // generating a random number from 0 to mWayNum - 1
        for (size_t i = 0; i < row.size(); i++) {
            Block& block = row[i];
            if (block.isValid()) {          // valid block
                mValidTally++;
                if(block.getTag() == tag) { // same tag
                    mHitTally++;
                    // set dirty bit to true if it is a write, otherwise dont do anything
                    if (cmd == 'w') { block.setDirty(true); }
                    return;
                }
            }
        }
        
        unsigned chosenIndex;
        if (mValidTally == mWayNum) {       // the row is full
            // choose a block at random
            chosenIndex = random;
            if (row[chosenIndex].isDirty()) {
                mMissWBTally++;
            } else {
                mMissTally++;
            }
        } else {            // the row is not full
            mMissTally++;
            // choose the next unvalid block
            chosenIndex = mValidTally;
        }
        Block& chosen = row[chosenIndex];
        chosen.setTag(tag);
        chosen.setValid(true);
        // set dirty bit to true if it is a write
        if (cmd == 'w') {
            chosen.setDirty(true);
        } else {    // set it to false if it is a read
            chosen.setDirty(false);
        }
        return;
    }
}; 

int main(int argc, char** argv)
{
    const unsigned indexMask1 = 0x7F;           // for masking cache 1
    const unsigned indexMask2 = 0x1F;           // TODO: masks
    const unsigned indexMask3 = 0xF;
    const unsigned indexMask4 = 0; 

    // 32KB direct mapped cache with a 256-byte block size
    Cache cache1 = Cache(32768, 256, 1);
    // 32KB 4-way set associative cache with a 256-byte block size
    Cache cache2 = Cache(32768, 256, 4);
    // 32KB 8-way set associative cache with a 256-byte block size
    Cache cache3 = Cache(32768, 256, 8);
    // 32KB fully associative cache with a 256-byte block size
    Cache cache4 = Cache(32768, 256, 128); 

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
                memoryTraces.push_back(make_pair(command, address));
                // fin >> dec;   //  Reset stream to "normal" input
            }
            
            cout << "Total: " << memoryTraces.size() << '\n';
            cache1.process(memoryTraces, indexMask1);
            cout << "hits: " << cache1.mHitTally << ' ' << "misses: " << cache1.mMissTally 
                << ' ' << "missWB: " << cache1.mMissWBTally << '\n';
            
            cache2.process(memoryTraces, indexMask2);
            cout << "hits: " << cache2.mHitTally << ' ' << "misses: " << cache2.mMissTally 
                << ' ' << "missWB: " << cache2.mMissWBTally << '\n';

            cache3.process(memoryTraces, indexMask3);
            cout << "hits: " << cache3.mHitTally << ' ' << "misses: " << cache3.mMissTally 
                << ' ' << "missWB: " << cache3.mMissWBTally << '\n';

            cache4.process(memoryTraces, indexMask4);
            cout << "hits: " << cache4.mHitTally << ' ' << "misses: " << cache4.mMissTally 
                << ' ' << "missWB: " << cache4.mMissWBTally << '\n';
            fin.close();   //  Close the file
        }
        else   //  Could not open file, so report error
            cout << "Could not open the command file." << endl;
    }
    else  //  User must provide a datafile
        cout << "Usage: " << endl
             << "  cache_sim <filename>" << endl;
	

}


// wayness x-axis % y-axis