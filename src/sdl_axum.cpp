#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdint.h>

#define global_variable static
#define internal static
#define local_persist static

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

global_variable SDL_Texture *texture;
global_variable void *bitmap_memory;
global_variable int bitmap_width;
global_variable int bitmap_height;
global_variable int bytes_per_pixel;

bool handle_event(SDL_Event *event);
internal void SDL_resize_texture(SDL_Renderer *renderer, int width, int height);
internal void SDL_update_window(SDL_Window *window, SDL_Renderer *renderer);
void cleanup();

bool handle_event(SDL_Event *event)
{
    bool should_quit = false;
    SDL_Window *window = SDL_GetWindowFromID(event->window.windowID);
    SDL_Renderer *renderer = SDL_GetRenderer(window);
    switch (event->type)
    {
    case SDL_QUIT:
        printf("SDL_QUIT\n");
        should_quit = true;
        break;
    case SDL_WINDOWEVENT:
        switch (event->window.event)
        {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_resize_texture(renderer, event->window.data1, event->window.data2);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            printf("Focus gained\n");
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_update_window(window, renderer);
            break;
        }
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            should_quit = true;
        case SDLK_r:
            break;
        case SDLK_g:
            break;
        case SDLK_b:
            break;
        }
    }
    return should_quit;
}

internal void SDL_resize_texture(SDL_Renderer *renderer, int width, int height)
{
    if (bitmap_memory)
    {
        free(bitmap_memory);
    }
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                width,
                                height);
    bitmap_width = width;
    bitmap_height = height;
    bitmap_memory = malloc(bitmap_width * bitmap_height * bytes_per_pixel);
}

internal void SDL_update_window(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_UpdateTexture(texture,
                      0,
                      bitmap_memory,
                      bitmap_width * bytes_per_pixel);
    SDL_RenderCopy(renderer,
                   texture,
                   0,
                   0);
    SDL_RenderPresent(renderer);
}

void cleanup()
{
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Failed to init SDL\n");
        return false;
    }

    SDL_Window *window;
    window = SDL_CreateWindow("Axum",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              1920,
                              1080,
                              SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
    if (window)
    {
        SDL_Renderer *renderer = SDL_CreateRenderer(window,
                                                    -1,
                                                    0);
        if (renderer)
        {
            bool running = true;
            int width, height;
            SDL_GetWindowSize(window, &width, &height);
            while (true)
            {
                SDL_Event event;
                SDL_WaitEvent(&event);
                if (handle_event(&event))
                {
                    break;
                }
            }
        }
        else
        {
            // TODO: Logging
        }
    }
    else
    {
        // TODO: Logging
    }

    cleanup();
    return 0;
}
