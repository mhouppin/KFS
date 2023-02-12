#ifndef CONSOLE_COM_H
#define CONSOLE_COM_H

enum com_port
{
    COM1 = 0x3F8,
    COM2 = 0x2F8,
    COM3 = 0x3E8,
    COM4 = 0x2E8,
};

enum com_register
{
    COM_DATA = 0,
    COM_INTERRUPT_ENABLE = 1,
    COM_BAUD_RATE_LOW = 0,
    COM_BAUD_RATE_HIGH = 1,
    COM_INTERRUPT_IDENTIFICATION = 2,
    COM_FIFO_CONTROL = 2,
    COM_LINE_CONTROL = 3,
    COM_MODEM_CONTROL = 4,
    COM_LINE_STATUS = 5,
    COM_MODEM_STATUS = 6,
    COM_SCRATCH = 7,
};

enum com_line_control
{
    COM_LINE_CONTROL_DLAB = 0x80,
    COM_LINE_CONTROL_8BIT = 0x03,
};

enum com_line_status
{
    COM_LINE_STATUS_DATA_READY = 0x01,
    COM_LINE_STATUS_TRANSMITTER_EMPTY = 0x20,
};

enum com_interrupt_enable
{
    COM_INTERRUPT_ENABLE_TRANSMITTER_EMPTY = 0x02,
};

enum com_interrupt_identification
{
    COM_INTERRUPT_IDENTIFICATION_TRANSMITTER_EMPTY = 0x02,
};

enum com_fifo_control
{
    COM_FIFO_CONTROL_ENABLE = 0x01,
    COM_FIFO_CONTROL_CLEAR_RECEIVE = 0x02,
    COM_FIFO_CONTROL_CLEAR_TRANSMIT = 0x04,
    COM_FIFO_CONTROL_DMA_MODE = 0x08,
    COM_FIFO_CONTROL_64BYTE = 0x20,
};

enum com_modem_control
{
    COM_MODEM_CONTROL_DTR = 0x01,
    COM_MODEM_CONTROL_RTS = 0x02,
};

enum com_modem_status
{
    COM_MODEM_STATUS_CTS = 0x10,
    COM_MODEM_STATUS_DSR = 0x20,
    COM_MODEM_STATUS_RI = 0x40,
    COM_MODEM_STATUS_DCD = 0x80,
};

void com_init();

void com_write_char(char character);
void com_write(void *buffer, unsigned int size);
void com_write_string(char *string);


#endif