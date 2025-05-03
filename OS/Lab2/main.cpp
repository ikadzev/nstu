#include <iostream>
#include <pthread.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

int gVar = 100;
int sync = 0;
const int CONSTANT = 10;
const int ITERS = 100;
const int DELAY = 100;
std::vector<int> gData1, gData2;
std::mutex mtx;

//unique_lock<mutex> lock(mtx);

void* thread1(void* arg) {
    for (int i = 0; i < ITERS; ++i) {
        if (sync == 2) {
            // std::unique_lock<std::mutex> lock(mtx);
            mtx.lock();
            gVar -= CONSTANT;
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
            gVar += CONSTANT;
            gData1.push_back(gVar);
            mtx.unlock();
        } else if (sync == 1) {
            std::unique_lock<std::mutex> lock(mtx);
            // mtx.lock();
            gVar -= CONSTANT;
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
            gVar += CONSTANT;
            gData1.push_back(gVar);
            // mtx.unlock();
        } else if (sync == 0) {
            // std::unique_lock<std::mutex> lock(mtx);
            // mtx.lock();
            gVar -= CONSTANT;
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
            gVar += CONSTANT;
            gData1.push_back(gVar);
            // mtx.unlock();
        }
    }
    return nullptr;
}

void* thread2(void* arg) {
    for (int i = 0; i < ITERS; ++i) {
        if (sync == 2) {
            // std::unique_lock<std::mutex> lock(mtx);
            mtx.lock();
            gVar += CONSTANT;
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
            gVar -= CONSTANT;
            gData2.push_back(gVar);
            mtx.unlock();
        } else if (sync == 1) {
            std::unique_lock<std::mutex> lock(mtx);
            // mtx.lock();
            gVar += CONSTANT;
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
            gVar -= CONSTANT;
            gData2.push_back(gVar);
            // mtx.unlock();
        } else if (sync == 0) {
            // std::unique_lock<std::mutex> lock(mtx);
            // mtx.lock();
            gVar += CONSTANT;
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
            gVar -= CONSTANT;
            gData2.push_back(gVar);
            // mtx.unlock();
        }
    }
    return nullptr;
}

int main() {
    // std::thread t1(thread1);
    // std::thread t2(thread2);

    std::cout << "0 - no sync; 1 - crit; 2 - mutex;" << std::endl;
    std::cin >> sync;

    pthread_t t1;
    int res1 = pthread_create(&t1, nullptr, thread1, nullptr);
    if (res1 != 0)
    {
        std::cerr << "Error creating thread!" << std::endl;
        return 1;
    }
    pthread_t t2;
    int res2 = pthread_create(&t2, nullptr, thread2, nullptr);
    if (res2 != 0)
    {
        std::cerr << "Error creating thread!" << std::endl;
        return 1;
    }

    for(float i = 0;; i += 0.5) {
        void* status;
        res1 = pthread_tryjoin_np(t1, &status);
        res2 = pthread_tryjoin_np(t2, &status);
        if (res1 != 0 && res2 != 0) {
            std::cout << "working..." << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } else { break; }
    }

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    std::cout << "\n gData1:" << std::endl;
    for (int val : gData1) {
        std::cout << val << " ";
    }
    std::cout << "\n gData2:" << std::endl;
    for (int val : gData2) {
        std::cout << val << " ";
    }
    return 0;
}