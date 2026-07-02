#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include <raylib.h>
#include <raygui.h>

#define CONFIG_SCREEN_WIDTH 800
#define CONFIG_SCREEN_HEIGHT 800
#define CONFIG_TIMER_TEXT_SIZE 160
#define CONFIG_TEXT_COLOR BLACK
#define CONFIG_WORK_BACKGROUND_COLOR SKYBLUE
#define CONFIG_REST_BACKGROUND_COLOR GREEN
#define CONFIG_WORK_MINUTES 25
#define CONFIG_REST_MINUTES 5
#define CONFIG_START_RESTING true

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    InitWindow(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, "Pomodoro Timer");
    SetTargetFPS(60);

    bool is_resting = CONFIG_START_RESTING;
    ssize_t minute_count = CONFIG_WORK_MINUTES;
    ssize_t seconds_count = 0;
    if (is_resting == true) {
        minute_count = CONFIG_REST_MINUTES;
    }

    float elapsed_time = 0;
    while (!WindowShouldClose()) {
        elapsed_time += GetFrameTime();
        if (elapsed_time > 1.0f) {
            seconds_count--;

            if (seconds_count < 0) {
                minute_count--;
                seconds_count = 59;
            }

            if (minute_count < 0) {
                if (is_resting == true) {
                    is_resting = false;
                    minute_count = 25;
                    seconds_count = 0;
                } else {
                    is_resting = true;
                    minute_count = 5;
                    seconds_count = 0;
                }
            }

            elapsed_time = 0.0f;
        }

        BeginDrawing();
        if (is_resting == true) {
            ClearBackground(CONFIG_REST_BACKGROUND_COLOR);
        } else {
            ClearBackground(CONFIG_WORK_BACKGROUND_COLOR);
        }

        char line_buffer[64] = {0};
        snprintf(line_buffer, 63, "%zu:%zu", minute_count, seconds_count);

        int text_size = MeasureText(line_buffer, CONFIG_TIMER_TEXT_SIZE);
        Vector2 text_position = (Vector2) {
            (CONFIG_SCREEN_WIDTH - text_size) / 2.0f,
            (CONFIG_SCREEN_HEIGHT - CONFIG_TIMER_TEXT_SIZE) / 2.0f
        };
        DrawText(line_buffer,
                 text_position.x, text_position.y,
                 CONFIG_TIMER_TEXT_SIZE,
                 CONFIG_TEXT_COLOR);

        EndDrawing();
    }

    CloseWindow();
}
