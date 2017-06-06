/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_Gosu_WRAP_H_
#define SWIG_Gosu_WRAP_H_

namespace Swig {
  class Director;
}


class SwigDirector_TextInput : public Gosu::TextInput, public Swig::Director {

public:
    SwigDirector_TextInput(VALUE self);
    virtual ~SwigDirector_TextInput();
    virtual std::string filter(std::string text) const;
};


class SwigDirector_Window : public Gosu::Window, public Swig::Director {

public:
    SwigDirector_Window(VALUE self, unsigned int width, unsigned int height, bool fullscreen = false, double update_interval = 16.666666);
    virtual ~SwigDirector_Window();
    virtual void show();
    virtual bool tick();
    virtual void close();
    virtual void update();
    virtual void draw();
    virtual bool needs_redraw() const;
    virtual bool needs_cursor() const;
    virtual void lose_focus();
    virtual void release_memory();
    virtual void button_down(Gosu::Button arg0);
    virtual void button_up(Gosu::Button arg0);
    virtual void drop(std::string const &filename);
    virtual Gosu::Color background_color() const;
};


#endif
