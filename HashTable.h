#ifndef HASHTABLE_H
#define HASTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../Practica1/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {
	private:
		int n;
		int max;
		ListLinked<TableEntry<V>>* table;

		int h(std::string key){
			int temp = 0;
			for(char c : key){
				temp += int(c);
			}
			return temp % max;
		}
	public:
		HashTable(int size){
			max = size;
			n = 0;
			table = new ListLinked<TableEntry<V>>[max];
		}

		~HashTable(){
			delete[] table;;
		}

		int capacity(){
			return max;
		}

		friend std::ostream&operator<<(std::ostream &out, const HashTable<V> &th){
			for(int i = 0; i < th.max; i++) {
				out << th.table[i] << std::endl;
			}
			return out;
		}

		V operator[](std::string key) {
			int index = h(key);
    			ListLinked<TableEntry<V>>& list = table[index];
    
    			for (auto& entry : list) {
        			if (entry.key == key) {
            				return entry.value;
        			}
    			}
    			throw std::runtime_error("Clave no encontrada");
		}


};

#endif
