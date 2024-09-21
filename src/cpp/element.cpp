#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>
#include "../include/SXL.h"

__SXL_NAMESPACE_BEGIN
/*-<< sdl_element_text >>-*/
void
element_text::query_text_texture(float x, float y, SDL_Texture *t) noexcept
{
    (x != -1) ? this->x = x : 0;
    (y != -1) ? this->y = y : 0;
    (t != nullptr) ? texture = t : nullptr;
    if (!SDL_GetTextureSize(texture, &w, &h))
    {
        logE("Failed to query texture, SDL_ERROR: %s.", SDL_GetError());
    }
}

/*-<< sdl_element >>-*/
void
element::init(void) noexcept
{
    EVENT_HANDLER->event_action(SDL_EVENT_MOUSE_MOTION, [this](SDL_Event ev) {
        SDL_MouseMotionEvent e = ev.motion;
        if (((e.x >= rect.x && e.x <= rect.x + rect.w) &&
             (e.y >= rect.y && e.y <= rect.y + rect.h)))
        {
            state.set<MOUSE_INSIDE>();
        }
        else if (state.is_set<MOUSE_INSIDE>())
        {
            state.unset<MOUSE_INSIDE>();
        }
    });
}

void
element::draw_borders(void) noexcept
{
    if (border_size <= 0 || border_size >= rect.w || border_size >= rect.h)
    {
        return;
    }
    SDL_SetRenderDrawColor(*renptr, border_color.r, border_color.g, border_color.b, border_color.b);
    SDL_FRect r;
    /* Left border. */
    r = {rect.x, rect.y, border_size, rect.h};
    SDL_RenderFillRect(*renptr, &r);
    /* Right border. */
    r = {rect.x + rect.w - border_size, rect.y, border_size, rect.h};
    SDL_RenderFillRect(*renptr, &r);
    /* Top border. */
    r = {rect.x, rect.y, rect.w, border_size};
    SDL_RenderFillRect(*renptr, &r);
    /* Bottom border. */
    r = {rect.x, rect.y + rect.h - border_size, rect.w, border_size};
    SDL_RenderFillRect(*renptr, &r);
}

void
element::draw(void) noexcept
{
    if (state.is_set<HIGHLIGHT_ON_HOVER>() && state.is_set<MOUSE_INSIDE>())
    {
        SDL_SetRenderDrawColor(*renptr, highlight_color.r,
                                        highlight_color.g,
                                        highlight_color.b,
                                        highlight_color.a);
    }
    else
    {
        SDL_SetRenderDrawColor(*renptr, color.r, color.g, color.b, color.a);
    }
    SDL_RenderFillRect(*renptr, &rect);
    draw_borders();
    if (!text_data)
    {
        return;
    }
    if (!text_data->texture)
    {
        logE("texture is nullptr.");
        return;
    }
    if (text_data->texture == texture_exceptions::blank_texture)
    {
        return;
    }
    SDL_FRect r = {rect.x + text_data->x, rect.y + text_data->y, text_data->w, text_data->h};
    if (!SDL_RenderTexture(*renptr, text_data->texture, nullptr, &r))
    {
        logE("SDL_RenderCopyFailed. SDL_ERROR: %s.", SDL_GetError());
    }
}

void
element::add_text_data(float x, float y, SDL_Texture *texture) noexcept
{
    if (texture == nullptr)
    {
        logE("texture == nullptr.");
        return;
    }
    if (text_data == nullptr)
    {
        text_data = APP->mem_pool.alloc<element_text>();
        if (text_data == nullptr)
        {
            APP->exit_clean(1);
        }
    }
    text_data->query_text_texture(x, y, texture);
}

void
element::animate(float end_x, float end_y, float end_w, float end_h, int duration_ms) noexcept
{
    if (!flags.is_set(IN_ANIMATION))
    {
        float steps  = (duration_ms / FRAME_DELAY(APP->root->framerate));
        float step_x = (end_x - rect.x) / steps;
        float step_y = (end_y - rect.y) / steps;
        float step_w = (end_w - rect.w) / steps;
        float step_h = (end_h - rect.h) / steps;
        logI("steps: %f", steps);
        logI("step_x: %f", step_x);
        logI("step_y: %f", step_y);
        logI("step_w: %f", step_w);
        logI("step_h: %f", step_h);
        element_animation_data animation_data {
            steps, end_x, end_y, end_w, end_h, step_x, step_y, step_w, step_h,
        };
        APP->animate_element(this, animation_data);
    }
}

void
element::set_borders(float size, SDL_Color color) noexcept
{
    border_size  = size;
    border_color = color;
}

void
element::set_highlight_on_hover(SDL_Color color) noexcept
{
    highlight_color = color;
    state.set<HIGHLIGHT_ON_HOVER>();
}

/* Constructor. */
element::element_t(SDL_Color c, SDL_FRect r) noexcept
{
    color       = c;
    rect        = r;
    text_data   = nullptr;
    renptr      = nullptr;
    border_size = 0;
}

element::element_t(void) noexcept
: rect{0, 0, 0, 0},
  align_rect{0, 0, 0, 0},
  color{0, 0, 0, 0},
  renptr(nullptr),
  text_data(nullptr),
  border_size(0),
  border_color{0, 0, 0, 0},
  highlight_color{0, 0, 0, 0}
{}

/*-<< sdl_button_element >>-*/
void
button_element::_add_callback(void) noexcept
{
    EVENT_HANDLER->event_action(SDL_EVENT_MOUSE_BUTTON_DOWN, [this](SDL_Event ev) {
        SDL_MouseButtonEvent e = ev.button;
        if (((e.x >= rect.x && e.x <= (rect.x + rect.w)) &&
             (e.y >= rect.y && e.y <= (rect.y + rect.h))))
        {
            if (_action)
            {
                _action(e);
            }
        }
    });
}
__SXL_NAMESPACE_END
