#pragma once

#include "esphome/core/component.h"
#include "esphome/components/display/display_buffer.h"
#include "esphome/core/log.h"

#define PxMATRIX_double_buffer true

#include <PxMatrix.h>  // NOLINT

namespace esphome {
namespace pxmatrix_display {

enum DriverChips {
  SHIFT = driver_chips::SHIFT,
  FM6124 = driver_chips::FM6124,
  FM6126A = driver_chips::FM6126A,
};
enum ColorOrders {
  RRGGBB = color_orders::RRGGBB,
  RRBBGG = color_orders::RRBBGG,
  GGRRBB = color_orders::GGRRBB,
  GGBBRR = color_orders::GGBBRR,
  BBRRGG = color_orders::BBRRGG,
  BBGGRR = color_orders::BBGGRR,
};
enum ScanPatterns {
  LINE = scan_patterns::LINE,
  ZIGZAG = scan_patterns::ZIGZAG,
  VZAG = scan_patterns::VZAG,
  WZAGZIG = scan_patterns::WZAGZIG,
  ZAGGIZ = scan_patterns::ZAGGIZ,
  ZZAGG = scan_patterns::ZZAGG,
};
enum MuxPatterns {
  BINARY = mux_patterns::BINARY,
  STRAIGHT = mux_patterns::STRAIGHT,
};

class PxmatrixDisplay : public PollingComponent, public display::DisplayBuffer {
 public:
  void display();
  void setup() override;
  void update() override;
  void fill(Color color) override;

  void set_pin_latch(InternalGPIOPin *pin_latch);
  void set_pin_a(InternalGPIOPin *pin_a);
  void set_pin_b(InternalGPIOPin *pin_b);
  void set_pin_c(InternalGPIOPin *pin_c);
  void set_pin_d(InternalGPIOPin *pin_d);
  void set_pin_e(InternalGPIOPin *pin_e);
  void set_pin_oe(InternalGPIOPin *pin_oe);
  void set_width(uint8_t width);
  void set_height(uint8_t height);
  void set_brightness(uint8_t brightness);
  void set_row_patter(uint8_t row_pattern);
  void set_driver_chips(DriverChips driver_chips);
  void set_color_orders(ColorOrders color_orders);
  void set_scan_patterns(ScanPatterns scan_patterns);

  void set_mux_patterns(MuxPatterns mux_patterns);
  void set_mux_delay(uint8_t mux_delay);

  void set_rotate(bool rotate);
  void set_flip(bool flip);

 protected:
  void draw_absolute_pixel_internal(int x, int y, Color color) override;
  int get_width_internal() override;
  int get_height_internal() override;

  PxMATRIX *px_matrix_;

  HighFrequencyLoopRequester high_freq_;

  InternalGPIOPin *pin_latch_{nullptr};
  InternalGPIOPin *pin_a_{nullptr};
  InternalGPIOPin *pin_b_{nullptr};
  InternalGPIOPin *pin_c_{nullptr};
  InternalGPIOPin *pin_d_{nullptr};
  InternalGPIOPin *pin_e_{nullptr};
  InternalGPIOPin *pin_oe_{nullptr};

  uint8_t width_ = 32;
  uint8_t height_ = 32;
  uint8_t brightness_ = 255;
  uint8_t row_pattern_ = 16;
  uint8_t mux_delay_ = 5;
  bool rotate_ = false;
  bool flip_ = false;

  DriverChips driver_chips_;
  ColorOrders color_orders_;
  ScanPatterns scan_patterns_;
  MuxPatterns mux_patterns_;
  // block_patterns BLOCK_PATTERN = block_patterns::ABCD;
};

}  // namespace pxmatrix_display
}  // namespace esphome
