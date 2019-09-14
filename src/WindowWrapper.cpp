#include <Gosu/Gosu.hpp>

namespace Gosu
{
  class WindowForWrapper : public Gosu::Window
  {
  struct Callbacks
  {
    void (*update)(void *data) = nullptr;
    void (*draw)(void *data) = nullptr;
    void (*button_down)(void *data, unsigned btn) = nullptr;
    void (*button_up)(void *data, unsigned btn) = nullptr;
    void (*drop)(void *data, const char *filename) = nullptr;
    int (*needs_redraw)(void* data) = nullptr; // explicitly set to prevent segfault
    int (*needs_cursor)(void* data) = nullptr;
    void (*close)(void *data) = nullptr;

    void *update_data = nullptr;
    void *draw_data = nullptr;
    void *button_down_data = nullptr;
    void *button_up_data = nullptr;
    void *drop_data = nullptr;
    void *needs_redraw_data = nullptr;
    void *needs_cursor_data = nullptr;
    void *close_data = nullptr;
  } callbacks;

  public:
      WindowForWrapper(int width, int height, bool fullscreen, double update_interval, bool resizable);
      void set_draw(void function(void *data), void *data);
      void set_update(void function(void *data), void *data);
      void set_button_down(void function(void *data, unsigned btn), void *data);
      void set_button_up(void function(void *data, unsigned btn), void *data);
      void set_drop(void function(void *data, const char *filename), void *data);
      void set_needs_redraw(int function(void *data), void *data);
      void set_needs_cursor(int function(void *data), void *data);
      void set_close(void function(void *data), void *data);

      void update() override;
      void draw() override;
      void gosu_button_down(unsigned btn); // Enables fullscreen toggle
      void button_down(Gosu::Button btn) override;
      void button_up(Gosu::Button btn) override;
      void drop(const std::string& filename) override;
      bool needs_redraw() const override;
      bool needs_cursor() const override;
      void close() override;

      void close_immediately();
  };
}

Gosu::WindowForWrapper::WindowForWrapper(int width, int height, bool fullscreen,
                                         double update_interval, bool resizable)
: Gosu::Window(width, height, fullscreen, update_interval, resizable) {
}

void Gosu::WindowForWrapper::set_update(void function(void *data), void *data)
{
  callbacks.update = function;
  callbacks.update_data = data;
}

void Gosu::WindowForWrapper::set_draw(void function(void *data), void *data)
{
  callbacks.draw = function;
  callbacks.draw_data = data;
}

void Gosu::WindowForWrapper::set_button_down(void function(void *data, unsigned btn), void *data)
{
  callbacks.button_down = function;
  callbacks.button_down_data = data;
}

void Gosu::WindowForWrapper::set_button_up(void function(void *data, unsigned btn), void *data)
{
  callbacks.button_up = function;
  callbacks.button_up_data = data;
}

void Gosu::WindowForWrapper::set_drop(void function(void *data, const char *filename), void *data)
{
  callbacks.drop = function;
  callbacks.drop_data = data;
}

void Gosu::WindowForWrapper::set_needs_redraw(int function(void *data), void *data)
{
  callbacks.needs_redraw = function;
  callbacks.needs_redraw_data = data;
}

void Gosu::WindowForWrapper::set_needs_cursor(int function(void *data), void *data)
{
  callbacks.needs_cursor = function;
  callbacks.needs_cursor_data = data;
}

void Gosu::WindowForWrapper::set_close(void function(void *data), void *data)
{
  callbacks.close = function;
  callbacks.close_data = data;
}

void Gosu::WindowForWrapper::update()
{
  if (callbacks.update != nullptr) {
    callbacks.update(callbacks.update_data);
  }
}

void Gosu::WindowForWrapper::draw()
{
  if (callbacks.draw != nullptr) {
    callbacks.draw(callbacks.draw_data);
  }
}

void Gosu::WindowForWrapper::gosu_button_down(unsigned btn)
{
  Gosu::Window::button_down(Gosu::ButtonName(btn));
}

void Gosu::WindowForWrapper::button_down(Gosu::Button btn)
{
  if (callbacks.button_down != nullptr) {
    callbacks.button_down(callbacks.button_down_data, btn.id());
  }
}

void Gosu::WindowForWrapper::button_up(Gosu::Button btn)
{
  if (callbacks.button_up != nullptr) {
    callbacks.button_up(callbacks.button_up_data, btn.id());
  }
}

void Gosu::WindowForWrapper::drop(const std::string& filename)
{
  if (callbacks.drop != nullptr) {
    callbacks.drop(callbacks.drop_data, filename.c_str());
  }
}

bool Gosu::WindowForWrapper::needs_redraw() const
{
  if (callbacks.needs_redraw != nullptr) {
    return callbacks.needs_redraw(callbacks.needs_redraw_data);
  }
  else {
    return true;
  }
}

bool Gosu::WindowForWrapper::needs_cursor() const
{
  if (callbacks.needs_cursor != nullptr) {
    return callbacks.needs_cursor(callbacks.needs_cursor_data);
  }
  else {
    return false;
  }
}

void Gosu::WindowForWrapper::close()
{
  if (callbacks.close != nullptr) {
    callbacks.close(callbacks.close_data);
  }
  else {
    Gosu::Window::close();
  }
}

void Gosu::WindowForWrapper::close_immediately()
{
  Gosu::Window::close();
}

extern "C" {
  #include <Gosu/Window.h>
  #include <Gosu/TextInput.h>

  // Constructor
  Gosu_Window* Gosu_Window_create(int width, int height, bool fullscreen, double update_interval, bool resizable)
  {
    return reinterpret_cast<Gosu_Window*>( new Gosu::WindowForWrapper(width, height, fullscreen, update_interval, resizable) );
  };

  // Callbacks
  void Gosu_Window_set_draw(Gosu_Window *window, void function(void *data), void *data)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_draw(function, data);
  }

  void Gosu_Window_set_update(Gosu_Window *window, void function(void *data), void *data)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_update(function, data);
  }

  void Gosu_Window_set_button_down(Gosu_Window *window, void function(void *data, unsigned btn), void *data)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_button_down(function, data);
  }

  void Gosu_Window_gosu_button_down(Gosu_Window *window, unsigned btn)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->gosu_button_down(btn);
  }

  void Gosu_Window_set_button_up(Gosu_Window *window, void function(void *data, unsigned btn), void *data)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_button_up(function, data);
  }

  void Gosu_Window_set_drop(Gosu_Window *window, void function(void *data, const char *filename), void *data)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_drop(function, data);
  }

  void Gosu_Window_set_needs_redraw(Gosu_Window *window, int function(void *data), void *data)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_needs_redraw(function, data);
  }

  void Gosu_Window_set_needs_cursor(Gosu_Window *window, int function(void *data), void *data)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_needs_cursor(function, data);
  }

  void Gosu_Window_set_close(Gosu_Window *window, void function(void *data), void *data)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_close(function, data);
  }


  Gosu_TextInput* Gosu_Window_text_input(Gosu_Window* window)
  {
    Gosu::Window *gosu_window = reinterpret_cast<Gosu::WindowForWrapper *>( window );
    return reinterpret_cast<Gosu_TextInput*>( gosu_window->input().text_input() );
  }

  void Gosu_Window_set_text_input(Gosu_Window* window, Gosu_TextInput* text_input)
  {
    Gosu::Window *gosu_window = reinterpret_cast<Gosu::WindowForWrapper *>( window );
    gosu_window->input().set_text_input( reinterpret_cast<Gosu::TextInput*>( text_input ));
  }


  void Gosu_Window_show(Gosu_Window* window)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->show();
  }

  bool Gosu_Window_tick(Gosu_Window* window)
  {
    return reinterpret_cast<Gosu::WindowForWrapper*>( window )->tick();
  }

  void Gosu_Window_close_immediately(Gosu_Window* window)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->close_immediately();
  }

  bool Gosu_Window_fullscreen(Gosu_Window* window)
  {
    return reinterpret_cast<Gosu::WindowForWrapper*>( window )->fullscreen();
  }

  const char* Gosu_Window_caption(Gosu_Window* window)
  {
    return reinterpret_cast<Gosu::WindowForWrapper*>( window )->caption().c_str();
  }

  void Gosu_Window_set_caption(Gosu_Window* window, const char* caption)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_caption(caption);
  }

  double Gosu_Window_update_interval(Gosu_Window* window)
  {
    return reinterpret_cast<Gosu::WindowForWrapper*>( window )->update_interval();
  }

  void Gosu_Window_set_update_interval(Gosu_Window* window, double update_interval)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->set_update_interval(update_interval);
  }

  void Gosu_Window_set_mouse_x(Gosu_Window* window, double x)
  {
    Gosu::Window* gosu_window = reinterpret_cast<Gosu::WindowForWrapper*>( window );
    gosu_window->input().set_mouse_position(x, gosu_window->input().mouse_x());
  }

  void Gosu_Window_set_mouse_y(Gosu_Window* window, double y)
  {
    Gosu::Window* gosu_window = reinterpret_cast<Gosu::WindowForWrapper*>( window );
    gosu_window->input().set_mouse_position(gosu_window->input().mouse_x(), y);
  }

  double Gosu_Window_mouse_x(Gosu_Window* window)
  {
   return reinterpret_cast<Gosu::WindowForWrapper*>( window )->input().mouse_x();
  }

  double Gosu_Window_mouse_y(Gosu_Window* window)
  {
   return reinterpret_cast<Gosu::WindowForWrapper*>( window )->input().mouse_y();
  }

  int Gosu_Window_width(Gosu_Window* window)
  {
    return reinterpret_cast<Gosu::WindowForWrapper*>( window )->width();
  }

  void Gosu_Window_set_width(Gosu_Window* window, int width)
  {
    Gosu::Window* gosu_window = reinterpret_cast<Gosu::WindowForWrapper*>( window );
    gosu_window->resize(width, gosu_window->height(), gosu_window->fullscreen());
  }

  int Gosu_Window_height(Gosu_Window* window)
  {
    return reinterpret_cast<Gosu::WindowForWrapper*>( window )->height();
  }


  void Gosu_Window_set_height(Gosu_Window* window, int height)
  {
    Gosu::Window* gosu_window = reinterpret_cast<Gosu::WindowForWrapper*>( window );
    gosu_window->resize(gosu_window->width(), height, gosu_window->fullscreen());
  }

  void Gosu_Window_resize(Gosu_Window* window, int width, int height, bool fullscreen)
  {
    reinterpret_cast<Gosu::WindowForWrapper*>( window )->resize(width, height, fullscreen);
  }

  int Gosu_Window_is_button_down(Gosu_Window* window, unsigned btn)
  {
    return reinterpret_cast<Gosu::WindowForWrapper*>( window )->input().down(Gosu::Button(btn));
  }

  // Destructor
  void Gosu_Window_destroy(Gosu_Window* window)
  {
    delete( reinterpret_cast<Gosu::WindowForWrapper*>( window ));
  }
}