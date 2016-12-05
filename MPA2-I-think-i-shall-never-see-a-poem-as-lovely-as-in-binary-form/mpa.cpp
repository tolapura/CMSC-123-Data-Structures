/**
* Created by @tolapura (11/2/16)
*/

#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <fstream>
#include <list>

using namespace std;
class packet {
    private:
        string stringBinary;
		string sourceAddress;
		string destinationAddress;
		int sequenceNumber;
		string checksum;
		int lengthOfData;
		string data;
		bool corrupted;
    public:
		packet();
        packet(string);
		void display();
		void setSourceAddress();
		void setDestinationAddress();
		void setSequenceNumber();
		void setCheckSum();
		void setLengthOfData();
		void setCorrupted();
		void setData();
		inline string getSourceAddress() {return sourceAddress;};
		inline string getDestinationAddress() {return destinationAddress;};
		inline int getSequenceNumber() {return sequenceNumber;};
		inline string getData() {return data;};
		inline bool isCorrupted() {return corrupted;};
};
packet::packet() {
	this->sourceAddress = "";
	this->destinationAddress = "";
	this->sequenceNumber = 0;
	this->checksum = "";
	this->lengthOfData = 0;
	this->data = "";
	this->corrupted = false;
}
void packet::setSourceAddress() {
    std::ostringstream ss;
    bitset<8> bitset8;
    int i=0;
    for (int j=0; j<4; j++) {
        for (int k=7; k>=0; k--) {
            bitset8[k] = stringBinary[i]=='0'?false:true;
            i++;
        }
        ss.str("");
        ss.clear();
        ss << bitset8.to_ulong();
        sourceAddress += ss.str();
        if(j != 3) {
            sourceAddress += ".";
		}
    }
}
void packet::setDestinationAddress() {
    std::ostringstream ss;
    bitset<8> bitset8;
    int i=32;
    for (int j=0; j<4; j++) {
        for (int k=7; k>=0; k--) {
            bitset8[k] = stringBinary[i]=='0'?false:true;
            i++;
        }
        ss.str("");
        ss.clear();
        ss << bitset8.to_ulong();
        destinationAddress += ss.str();
        if(j != 3) {
            destinationAddress += ".";
		}
    }
}
void packet::setSequenceNumber() {
    string seq = stringBinary.substr(64, 16);
    if (seq[0] == '1') {
        bitset<16> bitset16(seq);
        bitset16.flip();
        sequenceNumber = (bitset16.to_ulong() + 1) * -1;
    } else {
        bitset<16> bitset16(seq);
         sequenceNumber = bitset16.to_ulong();
    }
}
void packet::setCheckSum() {
    checksum = stringBinary.substr(80, 16);
}
void packet::setLengthOfData() {
    string len = stringBinary.substr(96, 16);
    bitset<16> bitset16(len);
    lengthOfData = bitset16.to_ulong();
}
void packet::setCorrupted() {
    string originalCheckSum = stringBinary.substr(80, 16);
    string strBin = stringBinary;
    strBin.replace(80, 16, "0000000000000000");
    unsigned long sumValue = 0;
    int start = 0;
    int end = stringBinary.length();
    int count = 0;
    while(start < end) {
		count++;
		if(count != 6) {
			bitset<16> temp(strBin.substr(start, 16));
			sumValue += temp.to_ulong();
			if(sumValue >= 65536) {
				sumValue -= 65535;
			}
		}
		start += 16;
	}
	// 1's complement the sum
    bitset<16> temp(sumValue);
	for(int i = 0; i < 16; i++) {
		temp[i] = !temp[i];
	}
    corrupted = (temp.to_string().compare(originalCheckSum) != 0);
}
void packet::setData() {
    int dataLen = lengthOfData;
    if (dataLen == 0) {
        data = "";
    } else {
        string temp = stringBinary.substr(112, dataLen);
        bitset<8> bitset8;
        int times = dataLen / 8;
        int start = 0;
        for (int i=0; i < times; i++) {
            for (int j=7; j>=0; j--) {
                bitset8[j] = temp[start++] == '0'?false:true;
            }
            data += (char) bitset8.to_ulong();
        }
    }
}
packet::packet(string stringBinary) {
    this->stringBinary = stringBinary;
    setSourceAddress();
	setDestinationAddress();
	setSequenceNumber();
	setCheckSum();
	setLengthOfData();
	setCorrupted();
	setData();
}
void packet::display() {
    cout << "Source Address: " << this->sourceAddress << "\n";
	cout << "Destination Address: " << this->destinationAddress << "\n";
	cout << "Sequence Number: " << this->sequenceNumber << "\n";
	cout << "Checksum: " << this->checksum << "\n";
	cout << "Length of Data: " << this->lengthOfData << "\n";
	cout << "Data: " << this->data << "\n";
	cout << "Corrupted: " << this->corrupted << "\n\n";
}

int main(){
    ifstream file("cases_random.in");
    ofstream fileOut("poems.in");
    list< list<packet> > listOfLists;
    list< list<packet> >::iterator it;
	list<packet> packetList;
	if(file.is_open()){
		string line;
		while(getline(file,line)){
			packet a(line);
			// if list of lists is empty, make a list then push the packet then push the list to the list of lists (liboga)
            if(listOfLists.empty()) {
				list<packet> tempList;
				tempList.push_back(a);
				listOfLists.push_back(tempList);
			} else {
			    // else find the list w/ same source address then push it to the list
			    for(it = listOfLists.begin(); it != listOfLists.end(); it++){
                    packet frontPacket = (*it).front();
                    if(frontPacket.getSourceAddress().compare(a.getSourceAddress())==0 && frontPacket.getDestinationAddress().compare(a.getDestinationAddress()) == 0){
                        (*it).push_back(a);
                        break;
                    }
			    }
			    // if there's no existing list of packet with similar address, make a list of packet then push the packet
			    // to the list then push the list to the list of lists (libog part 2)
			    if(it == listOfLists.end()) {
                    list<packet> temp;
                    temp.push_back(a);
                    listOfLists.push_back(temp);
			    }
			}
		}
		file.close();
	}
        for (it = listOfLists.begin(); it != listOfLists.end(); it++) {
            list<packet> temp = *it;
            int max; // this is the absolute value of the last element in a list of packets
            // iterate through every list in the list of lists then set max to the negative sequence number
			for(list<packet>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++) {
                packet packet = *it2;
                if (packet.getSequenceNumber() < 0) {
                    max = packet.getSequenceNumber() * -1;
                    break;
                }
			}
            int ctr = 0;
            bool found = false; // when line isn't found
            while(ctr < max) {
            // iterate through all the packets in the list
            for (list<packet>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++) {
                packet packet = *(it2);
                if (packet.getSequenceNumber() == ctr) {
                    found = true;
                    if (ctr == 0) { // zero sequence number is the title
                        if (packet.isCorrupted()) {
                            fileOut << "[title corrupted]" << endl;
                        } else {
                            fileOut << packet.getData() << endl;
                            fileOut << packet.getSourceAddress() << "/" << packet.getDestinationAddress() << endl;
                        }
                    } else {
                        packet.isCorrupted() ? fileOut << "[line corrupted]" << endl:fileOut << packet.getData() << endl;
                    }
                }
            }   // checking if line isn't found
                if (found == false) {
                    (ctr == 0) ? fileOut << "[title missing]" << endl : fileOut << "[line missing]" << endl;
                }
                found = false;
                ctr++;
            }
            fileOut<<"\n\n--------------------------------------------------------------------------------\n"<<endl<<endl;
    }
    fileOut.close();
    return 0;
}

