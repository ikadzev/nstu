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

int numTime = 0;
double numA = 100;
double numW = 0.1;
double numD = 0;
double threadX = 0;
double threadY = 0;
bool running = true;

void* threadDraw(void* arg) {
    if (SDL_Init(SDL_INIT_VIDEO)) exit(101);
	SDL_Window* win = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (!win) {
		SDL_Quit();
		exit(11);
	}
	
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (!ren) {
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(12);
	}
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

    std::vector<std::pair<double, double>> dots;
    while (running) {
        if (dots.size() >= COUNT) {
            dots.erase(dots.begin(), dots.begin() + 1);
        }
        dots.push_back({threadX, threadY});
        numTime++;
        for (auto dot : dots) {
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            SDL_Rect rect = {
                static_cast<int>(dot.first + WIDTH / 2), 
                static_cast<int>(-dot.second + HEIGHT / 2), 
                SIZE, 
                SIZE
            };
            SDL_RenderFillRect(ren, &rect);
        }
        SDL_RenderPresent(ren);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
    }
    SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
    return nullptr;
}

void* thread1(void* arg) {
    while (running) {
        threadX = numA * sin(numW * numTime + numD);
    }
    return nullptr;
}

void* thread2(void* arg) {
    while (running) {
        threadY = numA * sin(numW * numTime + numD);
    }
    return nullptr;
}

int main() {
    pthread_t tDraw;
    int resd = pthread_create(&tDraw, nullptr, threadDraw, nullptr);
    if (resd != 0)
    {
        std::cerr << "Error creating draw thread!" << std::endl;
        return 3;
    }
    pthread_t t1;
    int res1 = pthread_create(&t1, nullptr, thread1, nullptr);
    if (res1 != 0)
    {
        std::cerr << "Error creating first thread!" << std::endl;
        return 1;
    }
    pthread_t t2;
    int res2 = pthread_create(&t2, nullptr, thread2, nullptr);
    if (res2 != 0)
    {
        std::cerr << "Error creating second thread!" << std::endl;
        return 2;
    }

    while (running) {
        int ch;
        std::cout << "Set:\n1. A\n2. W\n3. D\n0. Stop\n" << std::endl;
        std::cin >> ch;
        switch (ch) {
            case 1:
                std::cout << "A = ";
                std::cin >> numA;
                break;
            case 2:
                std::cout << "W = ";
                std::cin >> numW;
                break;
            case 3:
                std::cout << "D = ";
                std::cin >> numD;
                break;
            case 0:
                running = false;
                break;
        }
    }
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(tDraw, nullptr);
    
}
