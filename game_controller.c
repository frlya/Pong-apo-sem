#include "game_controller.h"

bool stateSwitch = true;
int scale;
int state;

struct timespec loopDelay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};

pads_t pads = {
    .p1Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2,
    .p2Pos = SCREEN_HEIGHT / 2 - PAD_HEIGHT / 2,
    .p1Vel = 1,
    .p2Vel = -1
};

ball_t ball = {
    .x = START_POS_X,
    .y = START_POS_Y,
    .xVel = 1,
    .yVel = 1,
    .left = true,
    .speed = BASE_BALL_SPEED
};

void update(int *state) {
    int p1Offset;
    int p2Offset;
    switch (*state) {
    case RUNNING:
        p1Offset = getPlayerOffset(1);
        p2Offset = getPlayerOffset(2);
        updatePads(&pads, p1Offset, p2Offset);
        updateBall(&ball, &pads);
        if (checkWin()) {
            initWinSnakeLED();
            *state = RESULT;
        }

        if (greenReleased) {
            *state = PAUSE;
        }

        if (ball.left && *state == RUNNING) {
            *state = READY;
        }
        break;
    case PAUSE:
        handlePause(state);
        break;
    case READY:
        updateText(state);
        snakeLED();
        break;
    case RESULT:
        if (greenReleased) {
            resetPlayers();
            *state = MENU;
            menu.state = MENU_BUTTONS;
        }
        winSnakeLED();
        break;
    case MENU:
        updateMenu();
        if (menu.state == STARTED) {
            resetBall(&ball);
            resetPads(&pads);
            resetPlayers();
            initSnake();
            *led_line = 0;
            *state = RUNNING;
        }
        break;
    }
}

void render(int *state) {
    clearScreen();
    switch (*state) {
    case RUNNING:
        renderCentralLine();
        renderBall(&ball);
        renderPads(&pads);
        renderText(*state);
        break;
    case READY:
        renderCentralLine();
        renderBall(&ball);
        renderPads(&pads);
        renderText(*state);
        break;
    case RESULT:
        renderText(*state);
        break;
    case MENU:
        renderMenu();
        break;
    case PAUSE:
        renderText(*state);
        break;
    }
    updateLed();
    renderScreenData(parlcdMemBase);
}

void exitGame() {
    clearScreen();
    renderScreenData(parlcdMemBase);
    *led_line = 0;
    *rgb_led1 = 0;
    *rgb_led2 = 0;
    printf("Bye! See you soon!\n");
    free(fb);
    exit(0);
}