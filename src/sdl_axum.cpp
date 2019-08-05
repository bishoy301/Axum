#include <SDL2/SDL.h>

bool handle_event(SDL_Event *event)
{
    bool should_quit = false;
    switch (event->type)
    {
    case SDL_QUIT:
        printf("SDL_QUIT\n");
        should_quit = true;
        break;
    case SDL_WINDOWEVENT:
        switch (event->window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
            printf("SDL_WINDOWEVENT_RESIZED (%d, %d)\n", event->window.data1, event->window.data2);
            break;
        }
    }
    return should_quit;
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        //TODO: SDL_Init didn't work
    }

    SDL_Window *window;
    window = SDL_CreateWindow("Axum",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              1920,
                              1080,
                              SDL_WINDOW_RESIZABLE);

    while (true)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        if (handle_event(&event))
        {
            break;
        }
    }
    SDL_Quit();
    return 0;
}
