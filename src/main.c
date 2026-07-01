#include <stdio.h>

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

    size_t minute_count = 5;
    size_t seconds_count = 0;

    while (!WindowShouldClose()) {
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
