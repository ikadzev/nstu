#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <cassert>
#include "Hash.h"

void benchmark(double loadFactor, int trials = 10000) {
    int tableSize = 32;
    int elementCount = static_cast<int>(tableSize * loadFactor);
    std::vector<double> values;

    std::mt19937 rng(42);
    std::uniform_real_distribution<> dist(10000.0000, 15000.0000);

    for (int i = 0; i < elementCount; ++i) {
        values.push_back(dist(rng));
    }

    HashTable table;

    for (auto v : values) table.insert(v);
    auto insert_time = table.Operations();

    for (int i = 0; i < trials; ++i) assert(table.search(values[i % elementCount]));
    auto search_time = table.Operations();

    for (int i = 0; i < trials; ++i) table.remove(values[i % elementCount]);
    auto delete_time = table.Operations();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Load factor: " << loadFactor
         << " | Insert: " << insert_time / values.size()
         << " | Search: " << (search_time - insert_time) / trials
         << " | Delete: " << (delete_time - search_time) / trials << std::endl;
}

int main() {
    HashTable table;
    int choice;
    double value;

    while (true) {
        std::cout << "\n1. Insert\n2. Search\n3. Delete\n4. Print\n5. Clear\n6. Count\n7. Is Empty\n8. Benchmark\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value to insert: ";
                std::cin >> value;
                table.insert(value);
                break;
            case 2:
                std::cout << "Enter value to search: ";
                std::cin >> value;
                std::cout << (table.search(value) ? "Found" : "Not found") << std::endl;
                break;
            case 3:
                std::cout << "Enter value to delete: ";
                std::cin >> value;
                table.remove(value);
                break;
            case 4:
                table.print();
                break;
            case 5:
                table.clear();
                std::cout << "Table cleared.\n";
                break;
            case 6:
                std::cout << "Count: " << table.Count() << std::endl;
                break;
            case 7:
                std::cout << (table.IsEmpty() ? "Table is empty" : "Table is not empty") << std::endl;
                break;
            case 8:
                benchmark(0.5);
                benchmark(0.7);
                benchmark(0.9);
                break;
            case 0:
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}
