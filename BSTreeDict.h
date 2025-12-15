#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    // El árbol almacena objetos TableEntry<V>
    BSTree<TableEntry<V>>* tree;

public:
    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor
    ~BSTreeDict() {
        delete tree;
    }

    // Insertar: lanza excepción si la clave ya existe
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        try {
            // Intentamos buscar la clave
            tree->search(entry);
            // Si no lanza excepción, la clave ya existe
            throw std::runtime_error("Clave '" + key + "' ya existe!");
        } catch (const std::runtime_error&) {
            // No encontrada, insertar
            tree->insert(entry);
        }
    }

    // Buscar: lanza excepción si no existe
    V search(std::string key) override {
        TableEntry<V> query(key);
        try {
            return tree->search(query).value;
        } catch (const std::runtime_error&) {
            throw std::runtime_error("Clave no encontrada");
        }
    }

    // Eliminar: lanza excepción si no existe
    V remove(std::string key) override {
        V val = search(key); // search lanza excepción si no existe
        TableEntry<V> query(key);
        tree->remove(query);
        return val;
    }

    // Número de entradas
    int entries() override {
        return tree->size();
    }

    // Operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Impresión
    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
        out << *(bs.tree); // depende del operator<< de BSTree
        return out;
    }
};

#endif
