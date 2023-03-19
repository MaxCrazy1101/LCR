
#include "retarget.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "bsp_usart.h"

#if !defined(OS_USE_SEMIHOSTING)

//#define STDIN_FILENO  0
//#define STDOUT_FILENO 1
//#define STDERR_FILENO 2

/* 固定方法  */
__attribute__((weak)) int _isatty(int fd) {
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 1;

    errno = EBADF;
    return 0;
}

__attribute__((weak)) int _close(int fd) {
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 0;

    errno = EBADF;
    return -1;
}

__attribute__((weak)) int _lseek(int fd, int ptr, int dir) {
    (void) fd;
    (void) ptr;
    (void) dir;

    errno = EBADF;
    return -1;
}

__attribute__((weak)) int _fstat(int fd, struct stat *st) {
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO) {
        st->st_mode = S_IFCHR;
        return 0;
    }

    errno = EBADF;
    return 0;
}

/* 自实现方法  */
uint8_t __io_putchar(uint8_t ch) {
    usart_send_data(ch);
    return ch;
}

__attribute__((weak)) int _read(int file, char *ptr, int len) {
    (void) file;
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++) {
        *ptr++ = usart_receive_data();
    }
    return len;
}

__attribute__((weak)) int _write(int file, char *ptr, int len) {
//    (void) file;
//    int DataIdx;
//    for (DataIdx = 0; DataIdx < len; DataIdx++) {
//        __io_putchar(*ptr++);
//    }
//    return len;
    for (int i = 0; i < len; i++) {
        __io_putchar(*ptr++);
    }
    return len;
}

#endif //#if !defined(OS_USE_SEMIHOSTING)