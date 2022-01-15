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

  void set_pin_latch(GPIOPin *pin_latch);
  void set_pin_r1(GPIOPin *pin_r1);
  void set_pin_r2(GPIOPin *pin_r2);
  void set_pin_g1(GPIOPin *pin_g1);
  void set_pin_g2(GPIOPin *pin_g2);
  void set_pin_b1(GPIOPin *pin_b1);
  void set_pin_b2(GPIOPin *pin_b2);
  void set_pin_a(GPIOPin *pin_a);
  void set_pin_b(GPIOPin *pin_b);
  void set_pin_c(GPIOPin *pin_c);
  void set_pin_d(GPIOPin *pin_d);
  void set_pin_e(GPIOPin *pin_e);
  void set_pin_oe(GPIOPin *pin_oe);
  void set_pin_clk(GPIOPin *pin_clk);
  void set_width(uint8_t width);
  void set_height(uint8_t height);
  void set_brightness(uint8_t brightness);


 protected:
  void draw_absolute_pixel_internal(int x, int y, Color color) override;
  int get_width_internal() override;
  int get_height_internal() override;

  MatrixPanel_I2S_DMA *dma_matrix_ ;

  GPIOPin *pin_latch_{nullptr};
  GPIOPin *pin_r1_{nullptr};
  GPIOPin *pin_r2_{nullptr};
  GPIOPin *pin_g1_{nullptr};
  GPIOPin *pin_g2_{nullptr};
  GPIOPin *pin_b1_{nullptr};
  GPIOPin *pin_b2_{nullptr};
  GPIOPin *pin_clk_{nullptr};
  GPIOPin *pin_a_{nullptr};
  GPIOPin *pin_b_{nullptr};
  GPIOPin *pin_c_{nullptr};
  GPIOPin *pin_d_{nullptr};
  GPIOPin *pin_e_{nullptr};
  GPIOPin *pin_oe_{nullptr};

  uint8_t width_ = 64;
  uint8_t height_ = 64;
  uint8_t brightness_ = 255;
};

}  // namespace dmamatrix_display
}  // namespace esphome
