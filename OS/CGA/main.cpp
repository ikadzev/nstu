#include <iostream>
#include <pthread.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <math.h>
#include <SDL2/SDL.h>


const int WIDTH = 500;
const int HEIGHT = 500;
const int COUNT = 50;
const int SIZE = 10;
std::mutex lock1;
std::mutex lock2;

int numTime = 0;
int count = 50;
double numA = 100;
double numB = 100;
double numN = 0.1;
double numM = 0.1;
double numD = 0;
double threadX = 0;
double threadY = 0;
bool running = true;

pthread_t createThread(void* func(void* arg)) {
    pthread_t thread;
    int result = pthread_create(&thread, nullptr, func, nullptr);
    if (result != 0) {
        std::cerr << "Error creating thread!" << std::endl;
        exit(1);
    }
    return thread;
}

void drawDot(SDL_Renderer* ren, std::pair<double, double> dot) {
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_Rect rect = {
        (int)(dot.first + WIDTH / 2),
        (int)(-dot.second + HEIGHT / 2),
        SIZE, SIZE
    };
    SDL_RenderFillRect(ren, &rect);
}

void* threadDraw(void* arg) {
    if (SDL_Init(SDL_INIT_VIDEO)) exit(101);
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_PING,"0");
    
	SDL_Window* win;
	SDL_Renderer* ren;
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &win, &ren)) exit(102);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderClear(ren);

    std::vector<std::pair<double, double>> dots;
    while (running) {
        if (dots.size() >= count) {
            dots.erase(dots.begin(), dots.begin() + (dots.size() - count));
        }
        lock1.lock();
        lock2.lock();
        dots.push_back({threadX, threadY});
        lock1.unlock();
        lock2.unlock();
        numTime++;
        for (auto dot : dots) drawDot(ren, dot);
        SDL_RenderPresent(ren);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderClear(ren);
    }
    SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
    return nullptr;
}

void* thread1(void* arg) {
    int tempT;
    while (running) {
        tempT = numTime;
        lock1.lock();
        threadX = numA * sin(numN * numTime + numD);
        lock1.unlock();
        while (tempT == numTime);
    }
    return nullptr;
}

void* thread2(void* arg) {
    int tempT;
    while (running) {
        tempT = numTime;
        lock2.lock();
        threadY = numB * cos(numM * numTime);
        lock2.unlock();
        while (tempT == numTime);
    }
    return nullptr;
}

void waitThreads(int count, ...) {
    va_list threads;
    va_start(threads, count);
    void* status;
    for (size_t i = 0; i < count; i++) {
        pthread_t thread = va_arg(threads, pthread_t);
        int result = pthread_tryjoin_np(thread, &status);
        while (result) result = pthread_tryjoin_np(thread, &status);
    }
}

int main() {
    pthread_t tDraw = createThread(threadDraw);
    pthread_t t1 = createThread(thread1);
    pthread_t t2 = createThread(thread2);

    while (running) {
        int ch;
        std::cout << "Set:\n1. A\n2. B\n3. N\n4. M\n5. D\n6. COUNT\n0. Stop\n" << std::endl;
        std::cin >> ch;
        switch (ch) {
            case 1:
                std::cout << "A = ";
                std::cin >> numA;
                break;
            case 2:
                std::cout << "B = ";
                std::cin >> numB;
                break;
            case 3:
                std::cout << "N = ";
                std::cin >> numN;
                break;
            case 4:
                std::cout << "M = ";
                std::cin >> numM;
                break;
            case 5:
                std::cout << "D = ";
                std::cin >> numD;
                break;
            case 6:
                std::cout << "COUNT = ";
                std::cin >> count;
                break;
            case 0:
                running = false;
                break;
        }
    }
    waitThreads(3, t1, t2, tDraw);
}