//  File cache_sim.cpp

#include <iostream>  //  For normal output: cout, endl
#include <fstream>   //  For file streams
#include <iomanip>   //  For the hex and dec stream manipulators
#include <queue>     //  std::queue

using namespace std;

class Cache {
	private:
		// properties
        unsigned mMemory;
        unsigned mBlockSize;
        unsigned mWayNum;     // number of ways
		Block **blocks;
    public:
		// Constructor
        Cache(unsigned memory, unsigned blockSize, unsigned wayNum) 
			: mMemory(memory), mBlockSize(blockSize), mWayNum(wayNum),
			blocks(mMemory/mBlockSize) {}
		
		Block getBlocks {return blocks;}
};

class Block {
	private:
		// properties
        bool valid = false;
        bool dirty = false;
        unsigned tag = 0;
    public:
		// getters
		bool isValid {return valid;}
		bool isDirty {return dirty;}
		unsigned getTag {return tag;}
		//setters
		void setValid(bool valid) {this.valid = valid;}
		void setDirty(bool dirty) {this.dirty = dirty;}
		void setVTag(bool tag) {this.tag = tag;}
};

//  Augmment this function to properly perform the 
//  cache simulation
// void process(char cmd, unsigned addr)
// {
//     cout << "Command: " << cmd 
//          << ", address: " << dec << addr
//          << " (hex " << hex << addr << ')' << endl;
// }

int main(int argc, char** argv)
{
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
	for (unsigned i = 0; i < memoryTraces.size(); i++ {
		if (memoryTraces)
		if (trace.first = 'w') {
			
		}
		else if (trace.first = 'r')
	}
	// 32KB 4-way set associative cache with a 256-byte block size
	Cache cache2 = new Cache(32768, 256, 4);
	// 32KB 8-way set associative cache with a 256-byte block size
	Cache cache3 = new Cache(32768, 256, 8);
	// 32KB fully associative cache with a 256-byte block size
	Cache cache4 = new Cache(32768, 256, 128);
	
}