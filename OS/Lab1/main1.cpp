#include <iostream>
#include <sys/wait.h>

int main() {
    std::string file = "task.txt";
    pid_t forked = fork();

    if (forked < 0) {
        std::cout << "Failed to fork procces!" << std::endl;
        exit(1);
    } else if (forked == 0) {
        execlp("gnome-text-editor", "gnome-text-editor", file.c_str(), NULL);
    } else {
        waitpid(forked, NULL, 0);
        std::cout << "File closed!" << std::endl;
    }
    return 0;
}