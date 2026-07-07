#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>

#include <raylib.h>
#include <raygui.h>

#include "config.h"

float calculate_time_percentage(bool is_resting, ssize_t minute_count, ssize_t seconds_count)
{
    assert((minute_count >= 0));
    assert((seconds_count >= 0));

    float total_seconds = CONFIG_WORK_MINUTES * 60;
    if (is_resting) {
        total_seconds = CONFIG_REST_MINUTES * 60;
    }

    float elapsed_seconds = minute_count * 60 + seconds_count;
    return 1.0f - (elapsed_seconds / total_seconds);
}

void draw_centered_text(char *text, size_t y, size_t font_size)
{
    int text_size = MeasureText(text, font_size);
    float x = (CONFIG_SCREEN_WIDTH - text_size) / 2.0f;
    DrawText(text,
             x, y,
             font_size,
             CONFIG_TEXT_COLOR);

}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        fprintf(stderr, "ERROR: could not initialize the audio system\n");
        exit(EXIT_FAILURE);
    }

    Sound ring_sound = LoadSound(CONFIG_RING_SOUND_PATH);
    if (!IsSoundValid(ring_sound)) {
        fprintf(stderr, "ERROR: could not load ring sound (path: \"%s\"\n", CONFIG_RING_SOUND_PATH);
        exit(EXIT_FAILURE);
    }
    Sound noise_sound = LoadSound(CONFIG_NOISE_SOUND_PATH);
    if (!IsSoundValid(noise_sound)) {
        fprintf(stderr, "ERROR: could not load ring sound (path: \"%s\"\n", CONFIG_NOISE_SOUND_PATH);
        exit(EXIT_FAILURE);
    }

    InitWindow(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, "Pomodoro Timer");
    SetTargetFPS(60);

    bool is_resting = CONFIG_START_RESTING;
    ssize_t minute_count = CONFIG_WORK_MINUTES;
    ssize_t seconds_count = 0;
    if (is_resting == true) {
        minute_count = CONFIG_REST_MINUTES;
    }

    PlaySound(noise_sound);

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
                    minute_count = CONFIG_WORK_MINUTES;
                    seconds_count = 0;
                } else {
                    is_resting = true;
                    minute_count = CONFIG_REST_MINUTES;
                    seconds_count = 0;
                }

                PlaySound(ring_sound);
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
        float timer_text_y = (CONFIG_SCREEN_HEIGHT - CONFIG_TIMER_TEXT_SIZE) / 2.0f;
        draw_centered_text(line_buffer, timer_text_y, CONFIG_TIMER_TEXT_SIZE);

        float percentage_elapsed = calculate_time_percentage(is_resting,
                                                             minute_count,
                                                             seconds_count);
        DrawRectangle(0, CONFIG_SCREEN_HEIGHT - 160,
                      CONFIG_SCREEN_WIDTH * percentage_elapsed, 20,
                      CONFIG_TEXT_COLOR);

        char *state_text = "WORK";
        if (is_resting) {
            state_text = "REST";
        }
        draw_centered_text(state_text, 160, CONFIG_STATE_TEXT_SIZE);

        EndDrawing();

        if (!IsSoundPlaying(noise_sound)) {
            PlaySound(noise_sound);
        }
    }


    CloseWindow();
    CloseAudioDevice();
}
