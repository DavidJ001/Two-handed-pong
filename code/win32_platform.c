#include "utils.c"
#include "math.c"
#include "string.c"

#include "platform_common.c"

#include <windows.h>

// Global Variables for the game
global_variable Render_Buffer render_buffer;
global_variable f32 current_time;
global_variable b32 lock_fps = true;
global_variable struct Os_Job_Queue *general_queue;

// Compiler specific intrinsic
#define interlocked_compare_exchange(a, b, c) InterlockedCompareExchange((volatile long*)a, b, c)

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_NO_STDIO
#define STBI_NO_FAILURE_STRINGS
#define STBI_ASSERT assert
#include "stb_image.h"

#include "wav_importer.h"
#include "ogg_importer.h"

#include "cooker_common.c"
#include "asset_loader.c"

#include "profiler.c"
#include "software_rendering.c"
#include "console.c"
#include "audio.c"
#include "game.c"

HWND win32_window;
b32 win32_lock_mouse = true;
Input win32_input = {0};
v2i win32_center_screen;
BITMAPINFO win32_bitmap_info;
f32 frequency_counter;
b32 win32_paused = false;
HCURSOR win32_cursor;
v2i win32_old_mouse_p;
WINDOWPLACEMENT win32_window_position;
#define WINDOW_FLAGS WS_VISIBLE|WS_OVERLAPPEDWINDOW

#define HIDE_CURSOR 1