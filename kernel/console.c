#include "console.h"

// This contains the current loaded driver for the console
console_interface_t current_driver;

// This contains the default system driver for the console
system_driver_t system_driver;

void console_system_driver_load(system_driver_t driver)
{
    system_driver = driver;
    system_driver(&current_driver);
    system_driver.console_init();
}