#include "Button.h"

#include "Controls.h"

Button::Button(float x, float y) : Button() {
  transform.position.x = x;
  transform.position.y = y;
}

// Load images from file
void Button::setImages(const std::string& image1, const std::string& image2) {
  images[0] = asw::assets::load_texture(image1);
  images[1] = asw::assets::load_texture(image2);
  transform.size = asw::util::get_texture_size(images[0]);
}

bool Button::hover() const {
  const auto& mouse = asw::input::get_mouse();
  return transform.contains(mouse.position);
}

void Button::setFocus(bool focus_mode, bool focused) {
  this->focus_mode = focus_mode;
  this->focused = focused;
}

bool Button::highlighted() const {
  return focus_mode ? focused : hover();
}

bool Button::clicked() const {
  if (focus_mode) {
    return focused && asw::input::get_action_down(controls::UI_CONFIRM);
  }

  return hover() &&
         asw::input::get_mouse_button_down(asw::input::MouseButton::Left);
}

void Button::draw() {
  if (images[highlighted()]) {
    asw::draw::sprite(images[highlighted()], transform.position);
  }
}
