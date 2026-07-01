#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include <raylib.h>
#include <raygui.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define TIMER_TEXT_SIZE 160

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pomodoro Timer");
    SetTargetFPS(60);

    ssize_t minute_count = 1;
    ssize_t seconds_count = 0;

    float elapsed_time = 0;
    while (!WindowShouldClose()) {
        elapsed_time += GetFrameTime();
        if (elapsed_time > 1.0f) {
            seconds_count--;

            if (seconds_count < 0) {
                minute_count--;
                seconds_count = 59;
            }

            elapsed_time = 0.0f;
        }

        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        char line_buffer[64] = {0};
        snprintf(line_buffer, 63, "%zu:%zu", minute_count, seconds_count);

        int text_size = MeasureText(line_buffer, TIMER_TEXT_SIZE);
        Vector2 text_position = (Vector2) {
            (SCREEN_WIDTH - text_size) / 2.0f,
            (SCREEN_HEIGHT - TIMER_TEXT_SIZE) / 2.0f
        };
        DrawText(line_buffer, text_position.x, text_position.y, TIMER_TEXT_SIZE, BLACK);

        EndDrawing();
    }

    CloseWindow();
}
