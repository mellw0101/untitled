#include "../include/SXL.h"

__SXL_NAMESPACE_BEGIN
/* Add a element to the window. */
element *
window::new_element(SDL_Color color, SDL_FRect rect, init_list<unsigned> flags) noexcept
{
    element *elem = APP->mem_pool.alloc<element>();
    if (!elem)
    {
        logE("Mem alloc failed, 'new(nothrow)' return`ed 'nullptr'.");
        APP->exit_clean(1);
    }
    elem->color      = color;
    elem->rect       = rect;
    elem->renptr     = &ren;
    elem->flags      = flags;
    elem->init();
    elements.push_back(elem);
    logI("mem_pool used: %lu.", APP->mem_pool.used_memory());
    return elem;
}

/* Add a element to the window. */
button_element *
window::new_button_element(SDL_Color color, SDL_FRect rect, init_list<unsigned> flags) noexcept
{
    button_element *elem = APP->mem_pool.alloc<button_element>();
    if (elem == nullptr)
    {
        logE("mem_pool_t failed to alloc chunk of memory.");
        APP->exit_clean(1);
    }
    elem->color      = color;
    elem->rect       = rect;
    elem->renptr     = &ren;
    elem->flags      = flags;
    elem->init();
    elements.push_back(elem);
    logI("mem_pool used: %lu.", APP->mem_pool.used_memory());
    return elem;
}

/* Init win and ren for the window. */
void
window::init(void) noexcept
{
    w   = 800;
    h   = 600;
    win = SDL_CreateWindow(
        (title == nullptr ? "placeholder" : title), (int)w, (int)h, SDL_WINDOW_RESIZABLE);
    if (win == nullptr)
    {
        logE("Failed to create window, SDL_ERROR: %s.", SDL_GetError());
        APP->exit_clean(1);
    }
    ren = SDL_CreateRenderer(win, nullptr);
    if (ren == nullptr)
    {
        logE("Failed to create renderer, SDL_ERROR: %s.", SDL_GetError());
        APP->exit_clean(1);
    }
}

/* Cleanup window. */
void
window::cleanup(void) noexcept
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
}

/* Set window size. */
void
window::set_size(const float width, const float height) noexcept
{
    SDL_SetWindowSize(win, (int)width, (int)height);
    w = width;
    h = height;
}

/* Set window position. */
void
window::set_position(const int x, const int y) noexcept
{
    SDL_SetWindowPosition(win, x, y);
}

/* Set window title. */
void
window::set_title(const char *str) noexcept
{
    SDL_SetWindowTitle(win, str);
}

/* Set window min size. */
void
window::set_min_size(const int w, const int h) noexcept
{
    SDL_SetWindowMinimumSize(win, w, h);
}
__SXL_NAMESPACE_END
