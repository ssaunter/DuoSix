#include "matrix.h"
#include "quantum.h"
#include "i2c_master.h"

#define EXPANDER_ADDR 0x40
#define CUSTOM_I2C_TIMEOUT 100

matrix_row_t matrix[MATRIX_ROWS];

void matrix_init(void) {
    i2c_init();

    uint8_t init_state = 0xFF;
    i2c_transmit(EXPANDER_ADDR, &init_state, 1, CUSTOM_I2C_TIMEOUT);

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}

uint8_t matrix_scan(void) {
    uint8_t cols[3] = {2, 3, 4};

    for (uint8_t col = 0; col < 3; col++) {
        // Pull current column LOW
        uint8_t col_state = ~(1 << cols[col]);
        i2c_transmit(EXPANDER_ADDR, &col_state, 1, CUSTOM_I2C_TIMEOUT);
        wait_us(30);

        // Read the expander state
        uint8_t port_state = 0xFF;
        i2c_receive(EXPANDER_ADDR, &port_state, 1, CUSTOM_I2C_TIMEOUT);

        // Standard Switches (Rows 0 and 1)
        for (uint8_t row = 0; row < 2; row++) {
            if (!(port_state & (1 << row))) {
                matrix[row] |= (1 << col); 
            } else {
                matrix[row] &= ~(1 << col); 
            }
        }

        // Encoder Clicks (Virtual Row 2)
        if (col == 0) {
            if (!(port_state & (1 << 5))) { matrix[2] |= (1 << 0); } else { matrix[2] &= ~(1 << 0); }
            if (!(port_state & (1 << 6))) { matrix[2] |= (1 << 1); } else { matrix[2] &= ~(1 << 1); }
        }
    }

    // Reset pins to HIGH
    uint8_t reset_state = 0xFF;
    i2c_transmit(EXPANDER_ADDR, &reset_state, 1, CUSTOM_I2C_TIMEOUT);

    return 1;
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
}