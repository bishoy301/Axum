#include <SDL2/SDL.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

bool init();
bool set_opengl_attributes();
bool handle_event(SDL_Event *event);
void cleanup();

bool init()
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
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_GLContext gl = SDL_GL_CreateContext(window);

    set_opengl_attributes();

    SDL_GL_GetSwapInterval();

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif

    return true;
}

bool set_opengl_attributes()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    return true;
}

bool handle_event(SDL_Event *event)
{
    bool should_quit = false;
    SDL_Window *window = SDL_GetWindowFromID(event->window.windowID);
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
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            should_quit = true;
        case SDLK_r:
            glClearColor(1.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(window);
            break;
        case SDLK_g:
            glClearColor(0.0, 1.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(window);
            break;
        case SDLK_b:
            glClearColor(0.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(window);
            break;
        }
    }
    return should_quit;
}

void cleanup()
{
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    if (!init())
    {
        return -1;
    }

    while (true)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        if (handle_event(&event))
        {
            break;
        }
    }

    cleanup();
    return 0;
}
