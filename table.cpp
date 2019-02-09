#include "table.h"
#include <vector>
#include <iostream>
using namespace std;

Table::Table(unsigned int max_entries){
	this->max_entries = max_entries;
	this->entries = new vector<Entry>[max_entries];
}

Table::Table(unsigned int entries, std::istream& input){
	this->max_entries = entries;
	this->entries = new vector<Entry>[max_entries];
	Entry e;
	while(max_entries != 0){
		input >> e;
		put(e);
		max_entries --;
	}
}

void Table::put(unsigned int key, std::string data){
	put(Entry(key, data));
}

void Table::put(Entry e){
	int hashValue = e.get_key();
	int key = hashValue % max_entries;

	for(int i = 0; i < entries[key].size(); ++i) {
		if(entries[key][i].get_key() == e.get_key()) {
			entries[key][i] = e;
			return;
		}
	}

	entries[key].push_back(e);
}
std::string Table::get(unsigned int key) const {
	string string_value;
	for(int i = 0; i < entries[key].size(); ++i){
		if(entries[key][i] == key){
			string_value = entries[key][i];
		}
	}
	return string_value;
}

bool Table::remove(unsigned int key){
	int index = key % max_entries;
	std::vector<Entry>::iterator i; 
	for(i = entries[key].begin(); i < entries[key].end(); i++){
		if(i->get_key()==key){
			entries[key].erase(i);
			return true;
		}
	}
	return false;
}
void merge(vector <Entry>& data, int n1, int n2) 
{ 
    Entry *temp;
    int copied = 0;//total number copied from data to temp
    int copied1 = 0;//number copied from the first half of the data
    int copied2 = 0;//number copied from the second half of the data
    int i ;// array index to copy from temp back to data

    temp = new Entry[n1 + n2];
    vector<Entry>::iterator first = data.begin()+n1; 
    vector<Entry>::iterator last = data.end();
    vector<Entry> subvec(first,last);
 
    while ((copied1 < n1) && (copied2 < n2)){
        if(data[copied1] < subvec[copied2])
            temp[copied++] = data[copied1++];
        else
	    temp[copied++] = subvec[copied2++];
    }
    
    while(copied1 < n1)
        temp[copied++] = data[copied1++];
    while(copied2 < n2)
        temp[copied++] = subvec[copied2++];

    for(i = 0; i < n1 + n2; i++){
        data[i] = temp[i];
    }
    delete [] temp;

/*    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    // create temp arrays 
    Entry L[n1], R[n2]; 
  
    // Copy data to temp arrays L[] and R[] 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    // Copy the remaining elements of L[], if there 
       are any 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    // Copy the remaining elements of R[], if there 
       are any 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } */
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(vector <Entry>& data, int n) 
{ 
    int n1;
    int n2;

    if(n >1){

        n1 = n/2;
        n2 = n - n1;
        vector<Entry>::iterator first = data.begin()+n1;
        vector<Entry>::iterator last = data.end();
        vector<Entry> subvec(first,last);
 
        mergeSort(data, n1);
        mergeSort(subvec, n2);

	merge(data, n1, n2);
    }

/*    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        Entry m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } */
}
ostream& operator<<(std::ostream& out, Table &t){
	vector<Entry>entries2; 

	for(unsigned int i = 0; i < t.max_entries; i++){
		for(int j = 0; j < t.entries[i].size(); j++){
			entries2.push_back(t.entries[i][j]);
		}
	}
	mergeSort(entries2, entries2.size()); 

	for(unsigned int i = 0; i < entries2.size(); i++){
		out << entries2[i] << "\n";
	}
	return out;
}
