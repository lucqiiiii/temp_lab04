//
//  table.h
//  W19 - Lab04
//
#ifndef table_h
#define table_h
#include "entry.h"
#include <vector>

class Table{
public:
	//constructor for number of entries
	Table(unsigned int max_entries = 100);
	//constructor for data 
	Table(unsigned int max_entries, std::istream& input);
	//overload memebers 
	void put(unsigned int key, std::string data);
	void put(Entry e);
	//get the string 
	std::string get(unsigned int key)const;
	bool remove(unsigned int key);
	friend std::ostream& operator << (std::ostream& out, Table &t);
private:
	unsigned int max_entries; 
	std::vector<Entry>* entries;
};

#endif /* table_h */
