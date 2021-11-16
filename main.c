/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "pico/bootrom.h"

#define UART_ID uart1
#define BAUD_RATE 115200
#define LED_PIN 25

#define UART_TX_PIN 8
#define UART_RX_PIN 9

const uint sw1 = 16;
const uint sw2 = 17;
const uint sw3 = 18;

const uint sw[30] = {2, 3, 4, 5, 6, 7, 8, 13, 16, 17, 18, 19, 20, 21, 22, 23, 25};

uint segPin[8] = {9, 10, 11, 12, 15, 14, 24, 10};
const int i, p;
int pin;

int sevenseg[7][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1, 0}, // 2
    {1, 1, 1, 1, 0, 0, 1, 0}, // 3
    {0, 1, 1, 0, 0, 1, 1, 0}, // 4
    {1, 0, 1, 1, 0, 1, 1, 0}, // 5
    {0, 0, 1, 1, 1, 1, 1, 0}, // 6
};

void swnum(int n)
{
    gpio_init(sw1);
    gpio_init(sw2);
    gpio_init(sw3);
    gpio_set_dir(sw1, GPIO_OUT);
    gpio_set_dir(sw2, GPIO_OUT);
    gpio_set_dir(sw3, GPIO_OUT);

    for (pin = 0; pin < 8; pin++)
    {
        gpio_init(segPin[pin]);
        gpio_set_dir(segPin[pin], GPIO_OUT);
    }

    //uint led[8] = {a, b, c, d, e, f, g, dp};

    while (1)
    {

        switch (n)
        {
        case 0:
            gpio_put(segPin[0], 0);
            gpio_put(segPin[1], 0);
            gpio_put(segPin[2], 0);
            gpio_put(segPin[3], 0);
            gpio_put(segPin[4], 0);
            gpio_put(segPin[5], 0);
            gpio_put(segPin[6], 0);
            gpio_put(segPin[7], 0);

            gpio_put(sw1, 1);
            gpio_put(sw2, 0);
            gpio_put(sw3, 0);
            // for (p = 0; p < 8; p++)
            // {
            //     gpio_put(segPin[p], sevenseg[0][p]);
            //     sleep_ms(1000);
            // }
            break;

        case 1:
            gpio_put(segPin[0], 0);
            gpio_put(segPin[1], 1);
            gpio_put(segPin[2], 1);
            gpio_put(segPin[3], 0);
            gpio_put(segPin[4], 0);
            gpio_put(segPin[5], 0);
            gpio_put(segPin[6], 0);
            gpio_put(segPin[7], 1);

            gpio_put(sw1, 1);
            gpio_put(sw2, 0);
            gpio_put(sw3, 0);
            break;

        case 2:
            gpio_put(segPin[0], 1);
            gpio_put(segPin[1], 1);
            gpio_put(segPin[2], 0);
            gpio_put(segPin[3], 1);
            gpio_put(segPin[4], 1);
            gpio_put(segPin[5], 0);
            gpio_put(segPin[6], 1);
            gpio_put(segPin[7], 1);

            gpio_put(sw1, 0);
            gpio_put(sw2, 1);
            gpio_put(sw3, 0);
            break;
        case 3:
            gpio_put(segPin[0], 1);
            gpio_put(segPin[1], 1);
            gpio_put(segPin[2], 1);
            gpio_put(segPin[3], 1);
            gpio_put(segPin[4], 0);
            gpio_put(segPin[5], 0);
            gpio_put(segPin[6], 1);
            gpio_put(segPin[7], 1);

            gpio_put(sw1, 0);
            gpio_put(sw2, 0);
            gpio_put(sw3, 1);
            break;
        case 4:
            gpio_put(segPin[0], 0);
            gpio_put(segPin[1], 1);
            gpio_put(segPin[2], 1);
            gpio_put(segPin[3], 0);
            gpio_put(segPin[4], 0);
            gpio_put(segPin[5], 1);
            gpio_put(segPin[6], 1);
            gpio_put(segPin[7], 1);

            gpio_put(sw1, 0);
            gpio_put(sw2, 0);
            gpio_put(sw3, 0);
            break;
        case 5:
            gpio_put(segPin[0], 1);
            gpio_put(segPin[1], 0);
            gpio_put(segPin[2], 1);
            gpio_put(segPin[3], 1);
            gpio_put(segPin[4], 0);
            gpio_put(segPin[5], 1);
            gpio_put(segPin[6], 1);
            gpio_put(segPin[7], 0);
            break;

        default:
            break;
        }
    }
}
int main()
{
    stdio_init_all();

    char s1[10];
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    //UART Setup
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);



    while (1)
    {
        uint8_t ch = uart_getc(UART_ID);

        if (ch == '2')
        {
            swnum(2);
        }

        if (ch == '1')
        {
            swnum(1);
        }

        if (ch == '3')
        {
            swnum(3);
            gpio_put(LED_PIN, 1);
            sleep_ms(1000);
            gpio_put(LED_PIN, 0);
            sleep_ms(1000);
        }
        sleep_ms(1000);
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
        gpio_put(LED_PIN, 0);
    }

    return 0;
}
