#define _POSIX_C_SOURCE 200112L

#include "game_controller.h"
#include <stdio.h>

void setupScreen() {
    state = MENU;
    // Screen data init
    fb = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint16_t));
    if (fb == NULL) {
        exit(-1);
    }

    // LCD screen setup
    parlcdMemBase = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (parlcdMemBase == NULL) {
        exit(-1);
    }
    // parlcd_hx8357_init(parlcdMemBase);

    // Clear the screen
    parlcd_write_cmd(parlcdMemBase, 0x2c);
    int ptr = 0;
    uint32_t c;
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            c = 0;
            fb[ptr] = c;
            parlcd_write_data(parlcdMemBase, fb[ptr++]);
        }
    }
}

void setupLoop() {
    // Loop timer setup
    loopDelay.tv_sec = 0;
    loopDelay.tv_nsec = 17 * 1000 * 1000;
}

void setupFont() {
    // Font is added
    fdes = &font_winFreeSystem14x16;
    scale = 10;
}

void setupPeripherials() {
    // Lights init
    uint8_t *spiled_mem_base =
        map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (spiled_mem_base == NULL) {
        fprintf(stderr, "Peripheral init failed!\n");
        exit(1);
    }
    led_line = (volatile uint32_t *)(spiled_mem_base + SPILED_REG_LED_LINE_o);
    rgb_led1 = (volatile uint32_t *)(spiled_mem_base + SPILED_REG_LED_RGB1_o);
    rgb_led2 = (volatile uint32_t *)(spiled_mem_base + SPILED_REG_LED_RGB2_o);
    knobs = (volatile uint32_t *)(spiled_mem_base + SPILED_REG_KNOBS_8BIT_o);
}

void setup() {
    setupScreen();
    setupLoop();
    setupFont();
    setupPeripherials();
    menuInit(&state);
    initPlayers();
}

int main(int argc, char *argv[]) {
    setup();
    printf("Welcome to Pong!\n");
    while (true) {

        update(&state);
        render(&state);
        inputHandler();

        if (knobPressed == URGENT_EXIT) {
            exitGame();
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loopDelay, NULL);
    }
}
