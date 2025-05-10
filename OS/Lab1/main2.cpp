#include <iostream>
#include <sys/wait.h>
#include <vector>

std::vector<pid_t> pids; 

pid_t forkin() {
    pid_t f = fork();
    if (f < 0) {
        std::cout << "EF" << std::endl;
        exit(1);
    } else if (f == 0) {
        execlp("kid/main", "kid/main", NULL);
        exit(0);
    } else {
        return f;
    }
    
}

int main() {
    std::string file = "kid/main";
    bool exiting = false;
    pid_t forked = 0;

    while (!exiting) {
        std::cout << "Введите команду: 1. Запустить процесс 2. Закрыть процесс 3. Закрыть программу" << std::endl;
        int comm;
        std::cin >> comm;
        switch (comm) {
            case 1:
                forked = forkin();
                pids.push_back(forked);
                break;
            case 2:
                if (!pids.empty()) {
                    kill(pids.back(), SIGTERM);
                    waitpid(forked, NULL, 0);
                    pids.pop_back();
                } else {
                    std::cout << "Нет открытых процессов" << std::endl;
                }
                break;
            case 3:
                while (!pids.empty()) {
                    kill(pids.back(), SIGTERM);
                    waitpid(forked, NULL, 0);
                    pids.pop_back();
                }
                exiting = true;
                break; 
        }
    }
    return 0;
}