#include "../include/serial.h"

#define TX_PIN 1
#define RX_PIN 3

void serial_init() {
    // Define UART configurations
    const int uart_num = UART_NUM_0;  // Choose the UART number (0 or 1)
    const int uart_rx_buffer_size = 1024;  // Adjust the buffer size as needed

    uart_config_t uart_config = {
        .baud_rate = 115200,  // Set the baud rate to match your serial device
        .data_bits = UART_DATA_8_BITS,  // Set the data bits
        .parity    = UART_PARITY_DISABLE,  // Set parity (disable for none)
        .stop_bits = UART_STOP_BITS_1,  // Set stop bits
    };

    // Configure UART
    uart_param_config(uart_num, &uart_config);
    uart_set_pin(uart_num, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(uart_num, uart_rx_buffer_size, 0, 0, NULL, 0);
}