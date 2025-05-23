#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <chrono>
#include <vector>
#include <random>

class Tribios {
private:
    std::string name;
    bool isWord;
    std::map<char, Tribios*> kids;

public:
    Tribios() : name(""), isWord(false) {}
    Tribios(const std::string& name) : name(name), isWord(false) {}

    void insert(const std::string& key, size_t index = 0) {
        if (index > key.length()) return;
        if (key.empty()) return;
        if (key.length() - index == 0) {
            isWord = true;
            return;
        }
        if (kids.find(key[index]) == kids.end()) {
            kids[key[index]] = new Tribios(name + key[index]);
        }
        kids[key[index]]->insert(key, index + 1);
    }

    bool seek(const std::string& key, size_t index = 0) {
        if (index > key.length()) return false;
        if (key.empty()) return true;
        if (key.length() - index == 0) {
            return isWord;
        }
        if (kids.find(key[index]) == kids.end()) {
            return false;
        }
        return kids[key[index]]->seek(key, index + 1);
    }

    void print() {
        if (isWord) std::cout << name << " ";
        for (char c = 'a'; c <= 'z'; c++) {
            if (kids.find(c) != kids.end()) {
                kids[c]->print();
            }
        }
    }
};

std::string generateRandomString(size_t length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<> dist(0, 25);

    std::string s;
    s.reserve(length);
    for (size_t i = 0; i < length; ++i)
        s += charset[dist(rng)];
    return s;
}

void benchmark(const std::string& name, std::vector<std::string>& dataset) {
    Tribios t;

    // Insertion
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& word : dataset)
        t.insert(word);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "[" << name << "] Insertion time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    // Search
    start = std::chrono::high_resolution_clock::now();
    for (const auto& word : dataset)
        assert(t.seek(word));
    end = std::chrono::high_resolution_clock::now();
    std::cout << "[" << name << "] Search time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

int main() {
    Tribios t;
    std::vector<std::string> elems = {"aisubdf", "qnwovtb", "bvksjxhbi", "what", "i", "wow", "ggwp", "kvuzy", "ziuaewtbci"};
    for (std::string i : elems) {
        t.insert(i);
    }
    
    std::cout << "Words in Trie:\n";
    t.print();
    std::cout << std::endl;
    std::cout << std::endl;


    const size_t N = 10000;
    const size_t len = 10;
    std::vector<std::string> randomWords, worstWords;

    for (size_t i = 0; i < N; ++i)
        randomWords.push_back(generateRandomString(len));

    for (size_t i = 1; i <= N; ++i)
        worstWords.push_back(std::string(i, 'a'));

    benchmark("Average Case", randomWords);
    benchmark("Worst Case", worstWords);

    return 0;
}