#include <Engine.hpp>
#include <EventsManager.hpp>
#include <SDL.h>
#include <GeneralUtils.hpp>
#include <GL/GLRenderer.hpp>
#include "SDLWindow.hpp"


SDLWindow::SDLWindow(const Engine& engine,
    std::string_view name,
    size_t width,
    size_t height) :
    Window(width, height),
    _engine(engine)
{
    SDL_version version = { 0, 0, 0 };

    SDL_GetVersion(&version);

    printf("SDL Version: %d.%d.%d\n", version.major, version.minor, version.patch);

    SDL_Init(SDL_INIT_EVERYTHING);

    Uint32 windowFlags = SDL_WINDOW_SHOWN;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    windowFlags |= SDL_WINDOW_OPENGL;

    _window = { SDL_CreateWindow(name.data(),
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             static_cast<int>(width),
                             static_cast<int>(height),
                             windowFlags), SDL_DestroyWindow };
}


void SDLWindow::update()
{
    SDL_Event e;
    const auto& event_manager = _engine.eventsManager();

    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT)
    {
        event_manager.invoke_event(QuitEvent{});
    }
    else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
    {
        event_manager.invoke_event(KeyEvent{ 
            (e.type == SDL_KEYDOWN) ? Action::Down : Action::Up,
            static_cast<utils::KeyCode>(e.key.keysym.scancode)});
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
        MouseButton mb;
        switch (e.button.button)
        {
        case SDL_BUTTON_LEFT: mb = MouseButton::Left; break;
        case SDL_BUTTON_RIGHT: mb = MouseButton::Right; break;
        case SDL_BUTTON_MIDDLE: mb = MouseButton::Middle; break;
        }

        event_manager.invoke_event(MouseEvent{
            glm::vec2(e.button.x, e.button.y),
            (e.type == SDL_MOUSEBUTTONDOWN) ? Action::Down : Action::Up,
            mb});
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
        event_manager.invoke_event(MouseMoveEvent{glm::vec2(e.button.x, e.button.y) });
    }
    else if (e.type == SDL_TEXTINPUT)
    {
        event_manager.invoke_event(TextInputEvent{ e.text.text });
    }
    else if (e.type == SDL_MOUSEWHEEL)
    {
        event_manager.invoke_event(MouseWheelEvent{ e.wheel.y });
    }
}

std::unique_ptr<Renderer> SDLWindow::createRenderer()
{
    return std::make_unique<GLRenderer>(_engine, _window.get());
}

void SDLWindow::swap()
{
    SDL_GL_SwapWindow(_window.get());
}

std::string_view SDLWindow::getClipboardText() const
{
    _clipboard = SDL_GetClipboardText();
    return _clipboard;
}

void SDLWindow::setClipboardText(std::string_view text) const
{
    SDL_SetClipboardText(text.data());
}