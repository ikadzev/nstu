#include <iostream>
#include <sys/wait.h>

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
                break;
            case 2:
                if (forked) {
                    kill(forked, SIGTERM);
                    waitpid(forked, NULL, 0);
                }
                forked = 0;
                break;
            case 3:
                if (forked) {
                    kill(forked, SIGTERM);
                    waitpid(forked, NULL, 0);
                }
                exiting = true;
                break; 
        }
    }
    return 0;
}