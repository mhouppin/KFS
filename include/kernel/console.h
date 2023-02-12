#ifndef CONSOLE_H
#define CONSOLE_H

struct console_interface
{
    void (*console_init)();
    void (*console_destroy)();
};

typedef struct console_interface console_interface_t;

enum console_driver
{
    CONSOLE_DRIVER_SYSTEM = 0,
    CONSOLE_DRIVER = 1,
};

typedef void (* system_driver_t)(console_interface_t *current_driver);

#endif