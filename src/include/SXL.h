#ifndef UNTITLED_LIBRARY_H
#define UNTITLED_LIBRARY_H

#include <Mlib/Attributes.h>
#include <Mlib/Flag.h>
#include <Mlib/Init_list.h>
#include <Mlib/Mem_pool.h>
#include <Mlib/Profile.h>
#include <Mlib/Vector.h>

#include <SDL3/SDL_pixels.h>
#include <functional>

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>

/* clang-format off */
#define __SXL_NAMESPACE_BEGIN \
    namespace SXL             \
    {

#define __SXL_NAMESPACE_END \
    }

#define __SXL_SUB_NAMESPACE(name, ...) \
    __VA_ARGS__ namespace name
/* clang-format on */

using std::milli;
using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::time_point;
#define __this_thread std::this_thread
template <typename T>
using func = std::function<T>;

#define NOPOS                  {0, 0, 0, 0}
#define NOCOLOR                {0, 0, 0, 0}
#define WHITE                  {255, 255, 255, 255}
#define BLACK                  {0, 0, 0, 255}
#define RED                    {255, 0, 0, 255}

#define TOTAL_EVENTS           107
#define FRAME_DELAY(framerate) ((float)1000 / framerate)

__SXL_NAMESPACE_BEGIN
__SXL_SUB_NAMESPACE(utils, inline)
{
    __SXL_SUB_NAMESPACE(functions, inline)
    {
        constexpr unsigned event_to_index(const unsigned type)
        {
            switch (type)
            {
                /*-< Application events >-*/
                case SDL_EVENT_QUIT :
                    return 0;

                case SDL_EVENT_TERMINATING :
                    return 1;

                case SDL_EVENT_LOW_MEMORY :
                    return 2;

                case SDL_EVENT_WILL_ENTER_BACKGROUND :
                    return 3;

                /*-<< These application events have special meaning on iOS.  README-ios.md for
                 * details. >>-*/
                case SDL_EVENT_DID_ENTER_BACKGROUND :
                    return 4;

                case SDL_EVENT_WILL_ENTER_FOREGROUND :
                    return 5;

                case SDL_EVENT_DID_ENTER_FOREGROUND :
                    return 6;

                case SDL_EVENT_LOCALE_CHANGED :
                    return 7;

                case SDL_EVENT_SYSTEM_THEME_CHANGED :
                    return 8;

                case SDL_EVENT_DISPLAY_ORIENTATION :
                    return 9;

                case SDL_EVENT_DISPLAY_ADDED :
                    return 10;

                /*-<< Keyboard events >>-*/
                case SDL_EVENT_DISPLAY_REMOVED :
                    return 11;

                case SDL_EVENT_DISPLAY_MOVED :
                    return 12;

                case SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED :
                    return 13;

                case SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED :
                    return 14;

                case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED :
                    return 15;

                case SDL_EVENT_WINDOW_SHOWN :
                    return 16;

                /*-< Mouse events >-*/
                case SDL_EVENT_WINDOW_HIDDEN :
                    return 17;

                case SDL_EVENT_WINDOW_EXPOSED :
                    return 18;

                case SDL_EVENT_WINDOW_MOVED :
                    return 19;

                case SDL_EVENT_WINDOW_RESIZED :
                    return 20;

                /* Joystick events */
                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED :
                    return 21;

                case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED :
                    return 22;

                case SDL_EVENT_WINDOW_MINIMIZED :
                    return 23;

                case SDL_EVENT_WINDOW_MAXIMIZED :
                    return 24;

                case SDL_EVENT_WINDOW_RESTORED :
                    return 25;

                case SDL_EVENT_WINDOW_MOUSE_ENTER :
                    return 26;

                case SDL_EVENT_WINDOW_MOUSE_LEAVE :
                    return 27;

                case SDL_EVENT_WINDOW_FOCUS_GAINED :
                    return 28;

                case SDL_EVENT_WINDOW_FOCUS_LOST :
                    return 29;

                case SDL_EVENT_WINDOW_CLOSE_REQUESTED :
                    return 30;

                case SDL_EVENT_WINDOW_HIT_TEST :
                    return 31;

                case SDL_EVENT_WINDOW_ICCPROF_CHANGED :
                    return 32;

                case SDL_EVENT_WINDOW_DISPLAY_CHANGED :
                    return 33;

                case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED :
                    return 34;

                case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED :
                    return 35;

                case SDL_EVENT_WINDOW_OCCLUDED :
                    return 36;

                case SDL_EVENT_WINDOW_ENTER_FULLSCREEN :
                    return 37;

                case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN :
                    return 38;

                case SDL_EVENT_WINDOW_DESTROYED :
                    return 39;

                case SDL_EVENT_WINDOW_HDR_STATE_CHANGED :
                    return 40;

                /*-< Touch events >-*/
                case SDL_EVENT_KEY_DOWN :
                    return 41;

                case SDL_EVENT_KEY_UP :
                    return 42;

                case SDL_EVENT_TEXT_EDITING :
                    return 43;

                case SDL_EVENT_TEXT_INPUT :
                    return 44;

                case SDL_EVENT_KEYMAP_CHANGED :
                    return 45;

                case SDL_EVENT_KEYBOARD_ADDED :
                    return 46;

                case SDL_EVENT_KEYBOARD_REMOVED :
                    return 47;

                case SDL_EVENT_TEXT_EDITING_CANDIDATES :
                    return 48;

                case SDL_EVENT_MOUSE_MOTION :
                    return 49;

                case SDL_EVENT_MOUSE_BUTTON_DOWN :
                    return 50;

                case SDL_EVENT_MOUSE_BUTTON_UP :
                    return 51;

                case SDL_EVENT_MOUSE_WHEEL :
                    return 52;

                case SDL_EVENT_MOUSE_ADDED :
                    return 53;

                case SDL_EVENT_MOUSE_REMOVED :
                    return 54;

                case SDL_EVENT_JOYSTICK_AXIS_MOTION :
                    return 55;

                case SDL_EVENT_JOYSTICK_BALL_MOTION :
                    return 56;

                case SDL_EVENT_JOYSTICK_HAT_MOTION :
                    return 57;

                case SDL_EVENT_JOYSTICK_BUTTON_DOWN :
                    return 58;

                case SDL_EVENT_JOYSTICK_BUTTON_UP :
                    return 59;

                case SDL_EVENT_JOYSTICK_ADDED :
                    return 60;

                case SDL_EVENT_JOYSTICK_REMOVED :
                    return 61;

                case SDL_EVENT_JOYSTICK_BATTERY_UPDATED :
                    return 62;

                case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE :
                    return 63;

                case SDL_EVENT_GAMEPAD_AXIS_MOTION :
                    return 64;

                case SDL_EVENT_GAMEPAD_BUTTON_DOWN :
                    return 65;

                case SDL_EVENT_GAMEPAD_BUTTON_UP :
                    return 66;

                case SDL_EVENT_GAMEPAD_ADDED :
                    return 67;

                case SDL_EVENT_GAMEPAD_REMOVED :
                    return 68;

                case SDL_EVENT_GAMEPAD_REMAPPED :
                    return 69;

                case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN :
                    return 70;

                case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION :
                    return 71;

                case SDL_EVENT_GAMEPAD_TOUCHPAD_UP :
                    return 72;

                case SDL_EVENT_GAMEPAD_SENSOR_UPDATE :
                    return 73;

                case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE :
                    return 74;

                case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED :
                    return 75;
                case SDL_EVENT_FINGER_DOWN :
                    return 76;

                case SDL_EVENT_FINGER_UP :
                    return 77;

                case SDL_EVENT_FINGER_MOTION :
                    return 78;

                case SDL_EVENT_CLIPBOARD_UPDATE :
                    return 79;

                case SDL_EVENT_DROP_FILE :
                    return 80;

                case SDL_EVENT_DROP_TEXT :
                    return 81;

                case SDL_EVENT_DROP_BEGIN :
                    return 82;

                case SDL_EVENT_DROP_COMPLETE :
                    return 83;

                case SDL_EVENT_DROP_POSITION :
                    return 84;

                case SDL_EVENT_AUDIO_DEVICE_ADDED :
                    return 85;

                case SDL_EVENT_AUDIO_DEVICE_REMOVED :
                    return 86;

                case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED :
                    return 87;

                case SDL_EVENT_SENSOR_UPDATE :
                    return 88;

                case SDL_EVENT_PEN_PROXIMITY_IN :
                    return 89;

                case SDL_EVENT_PEN_PROXIMITY_OUT :
                    return 90;

                case SDL_EVENT_PEN_DOWN :
                    return 91;

                case SDL_EVENT_PEN_UP :
                    return 92;

                case SDL_EVENT_PEN_BUTTON_DOWN :
                    return 93;

                case SDL_EVENT_PEN_BUTTON_UP :
                    return 94;

                case SDL_EVENT_PEN_MOTION :
                    return 95;

                case SDL_EVENT_PEN_AXIS :
                    return 99;

                case SDL_EVENT_CAMERA_DEVICE_ADDED :
                    return 100;

                case SDL_EVENT_CAMERA_DEVICE_REMOVED :
                    return 101;

                case SDL_EVENT_CAMERA_DEVICE_APPROVED :
                    return 102;

                case SDL_EVENT_CAMERA_DEVICE_DENIED :
                    return 103;

                case SDL_EVENT_RENDER_TARGETS_RESET :
                    return 104;

                case SDL_EVENT_RENDER_DEVICE_RESET :
                    return 105;

                case SDL_EVENT_POLL_SENTINEL :
                    return 106;

                case SDL_EVENT_USER :
                    return 107;

                case SDL_EVENT_LAST :
                    return 108;

                case SDL_EVENT_ENUM_PADDING :
                default :
                    return (unsigned int)-1;
            }
            return (unsigned int)-1;
        }

        /* clang-format off */
        SDL_Texture *create_sdl_texture_from_bitfield(SDL_Renderer *ren, MVector<MVector<int>> data);
        double screen_dpi(int sc_pix_w, int sc_pix_h, double sc_inch_w, double sc_inch_h);
        void   convert_sdl_rect_to_floats(SDL_Rect *rect, float *floats);
        void   sdl_simd_update_rect(SDL_FRect *frect, SDL_FRect *end_frect, float *step_vals);
        void   set_ren_color(SDL_Renderer *ren, SDL_Color *c) noexcept;
        /* clang-format on */
    }
    __SXL_SUB_NAMESPACE(structs, inline)
    {
        struct texture_exceptions_t
        {
            static SDL_Texture *blank_texture;
        };

        struct element_animation_data_t
        {
            float steps;
            float end_x;
            float end_y;
            float end_w;
            float end_h;
            float step_x;
            float step_y;
            float step_w;
            float step_h;
        };
    }
    __SXL_SUB_NAMESPACE(types, inline)
    {
        enum element_internal_state
        {
            MOUSE_INSIDE = 1,
            HIGHLIGHT_ON_HOVER
        };

        using event_callback_t = func<void(SDL_Event ev)>;
        using event_vector_t   = MVector<event_callback_t>;
    }
}

typedef texture_exceptions_t     texture_exceptions;
typedef element_animation_data_t element_animation_data;

class event_handler_t
{
    DEL_CM_CONSTRUCTORS(event_handler_t);
    utils::event_vector_t   _map[TOTAL_EVENTS] {};
    static event_handler_t *_instance;
    SDL_Event               _ev {};
    event_handler_t(void) = default;

public:
    static event_handler_t *instance(void) noexcept;
    template <typename F>
    __inline__ void
    __attr(__always_inline__, __nodebug__, __nothrow__)
        event_action(const unsigned int ev_t, F &&f) noexcept
    {
        const unsigned int type = event_to_index(ev_t);
        if (type == (unsigned int)-1)
        {
            return;
        }
        _map[type].push_back(std::forward<F>(f));
    }
    void __no_debug __no_throw handle_event(void) noexcept;
};

struct element_text_t
{
    float        x       = -1;
    float        y       = -1;
    float        w       = 0;
    float        h       = 0;
    unsigned int format  = 0;
    int          access  = 0;
    SDL_Texture *texture = nullptr;
    /*-<< Methods >>-*/
    void query_text_texture(float x = -1, float y = -1, SDL_Texture *t = nullptr) noexcept;
};

struct element_t
{
    enum state_flags
    {
        IN_ANIMATION = 1,
        ALIGN_X,
        ALIGN_Y,
        ALIGN_WIDTH,
        ALIGN_HEIGHT
    };
    SDL_FRect       rect;
    SDL_FRect       align_rect;
    SDL_Color       color;
    SDL_Renderer  **renptr;
    element_text_t *text_data;
    bit_flag_t<8>   flags;
    /*-<< Methods >>-*/
    void init(void) noexcept;
    void draw(void) noexcept;
    void add_text_data(float x, float y, SDL_Texture *texture) noexcept;
    void animate(float end_x, float end_y, float end_w, float end_h, int duration_ms) noexcept;
    void set_borders(float size, SDL_Color color) noexcept;
    void set_highlight_on_hover(SDL_Color color) noexcept;
    /*-<< Constructor >>-*/
    element_t(SDL_Color color, SDL_FRect rect) noexcept;
    element_t(void) noexcept;

private:
    bit_flag_t<8> state;
    float         border_size;
    SDL_Color     border_color;
    SDL_Color     highlight_color;
    /*-<< Methods >>-*/
    void draw_borders(void) noexcept;
};

struct button_element_t : element_t
{
    std::function<void(SDL_MouseButtonEvent ev)> _action = nullptr;
    template <typename F>
    __always_inline void
    action(F &&f) noexcept
    {
        _action = std::forward<F>(f);
        _add_callback();
    }

private:
    void _add_callback(void) noexcept;
};

/* clang-format off */
struct window_t
{
    /* Data vars. */
    SDL_Window                 *win       = nullptr;
    SDL_Renderer               *ren       = nullptr;
    const char                 *title     = nullptr;
    int                         framerate = 480;
    float                       w         = 800;
    float                       h         = 600;
    MVector<element_t *>        elements;
    MVector<button_element_t *> button_elements;
    /* Methods. */
    element_t *__warn_unused        new_element(SDL_Color color, SDL_FRect rect, init_list<unsigned> flags)        noexcept;
    button_element_t *__warn_unused new_button_element(SDL_Color color, SDL_FRect rect, init_list<unsigned> flags) noexcept;
    void init(void)                          noexcept;
    void cleanup(void)                       noexcept;
    void set_size(float width, float height) noexcept;
    void set_position(int x, int y)          noexcept;
    void set_title(const char *str)          noexcept;
    void set_min_size(int w, int h)          noexcept;
};
/* clang-format on */

class app_t
{
    static app_t                                           *_instance;
    std::function<void()>                                   _main_loop = nullptr;
    bit_flag_t<8>                                           _flags;
    MVector<SDL_Texture *>                                  _alloced_textures;
    MVector<TTF_Font *>                                     _alloced_fonts;
    MVector<std::pair<element_t *, element_animation_data>> _anim_data;

    DEL_CM_CONSTRUCTORS(app_t);

    app_t(void) noexcept;
    static void _destroy(void) noexcept;
    void        _cleanup(void) noexcept;
    void        _perform_amimation(void) noexcept;
    /* These are used to calculate correct frame dalay based on time to render frame. */
    TIME_POINT<HIGH_RES_CLOCK> _frame_start_time;
    void                       _frame_start(void) noexcept;
    void                       _frame_end(void) noexcept;

public:
    mem_pool_t<8> mem_pool;
    window_t     *root;

    static app_t *__warn_unused instance(void) noexcept;
    int                         run(void) noexcept;
    void                        set_main_loop(const std::function<void()> &loop) noexcept;
    void                        quit(void) noexcept;
    TTF_Font *__warn_unused     retrieve_new_font(int size, const char *file) noexcept __no_null(3);
    SDL_Texture *__warn_unused  make_text_texture(TTF_Font *font, const char *text, SDL_Color fg,
                                                  SDL_Color bg) noexcept __no_null(2, 3);
    SDL_Texture *__warn_unused  make_destroy_text_texture(SDL_Texture *old_texture, TTF_Font *font,
                                                          const char *text, SDL_Color fg,
                                                          SDL_Color bg) noexcept __no_null(3, 4);
    void                        render_text(float x, float y, SDL_Texture *texture) noexcept;
    float __warn_unused         width(void) const noexcept;
    float __warn_unused         height(void) const noexcept;
    void __no_return            exit_clean(int status) noexcept;
    void animate_element(element_t *element, element_animation_data data) noexcept;
};
__SXL_NAMESPACE_END

typedef SXL::event_handler_t  event_handler;
typedef SXL::element_text_t   element_text;
typedef SXL::element_t        element;
typedef SXL::button_element_t button_element;
typedef SXL::window_t         window;
typedef SXL::app_t            app;

/* Flags for 'sdl_app'. */
#define APP_RUNNING   1

#define APP           app::instance()
#define EVENT_HANDLER event_handler::instance()

#endif // UNTITLED_LIBRARY_H
