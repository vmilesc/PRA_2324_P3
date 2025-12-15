#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../Practica1/PRA_2324_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
        	int n;
		int max;
		ListLinked<TableEntry<V>>* table;

    public:
        int h(std::string key){
	
		int i=0;
		char c = key.at(i);
		int valor=0;
	
		while(i < key.length()){
    
    		valor = valor + int(key.at(i));
    		i++;
		}
	
		return (valor % max);
	}	

	HashTable(int size){

		max = size;
		n = 0;
		table = new TableEntry<V>* [max];
		for(int i=0;i<max;i++){
			table[i]=nullptr;
		}
	};



	~HashTable(){
	
		for(int i=0;i<max;i++){
			if(table[i] != nullptr){

                        delete table[i];
                	
			}
		}
		delete[] table;

	}

	int capacity(){

		return max;

	}
        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){

		for(int i=0;i<th.max;i++){


		out<<th.table[i]<<"\n";
			
		}

		return out;
	}
	V operator[](std::string key){

	if(key!= ""){
		return key;
	}else {
		throw std::runtime_error("La clave no puede estar vacía.");
	}


	}
};

#endif
