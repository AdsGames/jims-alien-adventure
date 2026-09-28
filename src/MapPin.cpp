#include "MapPin.h"

std::array<asw::Texture, 2> MapPin::pin_images = {nullptr};

// Construct
MapPin::MapPin(int x, int y, const std::string& folder, bool completed) {
  if (pin_images[0].get() == nullptr) {
    pin_images[0] =
        asw::assets::load_texture("assets/images/map/pin.png", "pin");
    pin_images[1] =
        asw::assets::load_texture("assets/images/map/pin_grey.png", "pin_grey");
  }

  draw_background = false;
  set_texture(pin_images[completed], true);
  transform.position = asw::Vec2f(x, y - (transform.size.y / 2));

  image =
      asw::assets::load_texture("assets/images/levels/" + folder + "/icon.png");
}

// Draw pin, and the level image beside the focused pin or the cursor
void MapPin::draw(asw::ui::Context& ctx) {
  Button::draw(ctx);

  if (is_focused()) {
    asw::draw::sprite(image, transform.get_center());
  } else if (is_hovered()) {
    asw::draw::sprite(image, asw::input::get_mouse().position);
  }
}
