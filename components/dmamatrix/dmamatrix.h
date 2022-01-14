#pragma once

#include "esphome/core/component.h"
#include "esphome/components/display/display_buffer.h"
#include "esphome/core/log.h"
#include "esphome/core/gpio.h"
#include "esphome/core/color.h"
#include "esphome/components/display/display_color_utils.h"

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>  // NOLINT

namespace esphome {
namespace dmamatrix_display {


class DmaMatrixDisplay : public PollingComponent, public display::DisplayBuffer {
 public:
  void display();
  float get_setup_priority() const override;
  void setup() override;
  void update() override;
  void fill(Color color) override;

  void set_pin_latch(InternalGPIOPin *pin_latch);
  void set_pin_r1(InternalGPIOPin *pin_r1);
  void set_pin_r2(InternalGPIOPin *pin_r2);
  void set_pin_g1(InternalGPIOPin *pin_g1);
  void set_pin_g2(InternalGPIOPin *pin_g2);
  void set_pin_b1(InternalGPIOPin *pin_b1);
  void set_pin_b2(InternalGPIOPin *pin_b2);
  void set_pin_a(InternalGPIOPin *pin_a);
  void set_pin_b(InternalGPIOPin *pin_b);
  void set_pin_c(InternalGPIOPin *pin_c);
  void set_pin_d(InternalGPIOPin *pin_d);
  void set_pin_e(InternalGPIOPin *pin_e);
  void set_pin_oe(InternalGPIOPin *pin_oe);
  void set_pin_clk(InternalGPIOPin *pin_clk);
  void set_width(uint8_t width);
  void set_height(uint8_t height);
  void set_brightness(uint8_t brightness);


 protected:
  void draw_absolute_pixel_internal(int x, int y, Color color) override;
  int get_width_internal() override;
  int get_height_internal() override;

  MatrixPanel_I2S_DMA *dma_matrix_ ;

  InternalGPIOPin *pin_latch_{nullptr};
  InternalGPIOPin *pin_r1_{nullptr};
  InternalGPIOPin *pin_r2_{nullptr};
  InternalGPIOPin *pin_g1_{nullptr};
  InternalGPIOPin *pin_g2_{nullptr};
  InternalGPIOPin *pin_b1_{nullptr};
  InternalGPIOPin *pin_b2_{nullptr};
  InternalGPIOPin *pin_clk_{nullptr};
  InternalGPIOPin *pin_a_{nullptr};
  InternalGPIOPin *pin_b_{nullptr};
  InternalGPIOPin *pin_c_{nullptr};
  InternalGPIOPin *pin_d_{nullptr};
  InternalGPIOPin *pin_e_{nullptr};
  InternalGPIOPin *pin_oe_{nullptr};

  uint8_t width_ = 64;
  uint8_t height_ = 64;
  uint8_t brightness_ = 255;
};

}  // namespace dmamatrix_display
}  // namespace esphome
