#include <termios.h>
#include <unistd.h>

void disableBufferedInput() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);          // Получаем текущие настройки терминала
    t.c_lflag &= ~ICANON;                 // Отключаем канонический режим
    t.c_lflag &= ~ECHO;                   // Отключаем эхо-ввод
    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Применяем изменения
}

void restoreBufferedInput() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);          // Получаем текущие настройки терминала
    t.c_lflag |= ICANON;                  // Включаем канонический режим
    t.c_lflag |= ECHO;                    // Включаем эхо-ввод
    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Применяем изменения
}
