#include <iostream>
#include <sys/wait.h>

int main() {
    execlp("gnome-text-editor", "gnome-text-editor", "/home/ikadzev/hotaru/proj/nstu/OS/Lab1/task.txt", NULL);
	return 1;
}
