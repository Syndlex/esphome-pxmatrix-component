#include "dmamatrix.h"
#include "esphome/core/application.h"




static const char *TAG = "dmamatrix_display";

namespace esphome {
namespace dmamatrix_display {

MatrixPanel_I2S_DMA *dmamatrix = nullptr;



void display_updater() {  }

float DmaMatrixDisplay::get_setup_priority() const { return setup_priority::PROCESSOR; }

void DmaMatrixDisplay::setup() {
  ESP_LOGCONFIG(TAG, "Starting setup...");
  HUB75_I2S_CFG::i2s_pins _pins={
    pin_r1_->get_pin(), pin_g1_->get_pin(), pin_b1_->get_pin(), pin_r2_->get_pin(), pin_g2_->get_pin(), 
    pin_b2_->get_pin(), pin_a_->get_pin() , pin_b_->get_pin(), pin_c_->get_pin(), pin_d_->get_pin(), 
    pin_e_->get_pin() , pin_latch_->get_pin() ,pin_oe_->get_pin() ,pin_clk_->get_pin() };
  HUB75_I2S_CFG mxconfig(
      width_,   // module width
      height_,   // module height
      1,    // Chain length
      _pins, // pin mapping
      HUB75_I2S_CFG::FM6124,
      true
    );

  mxconfig.clkphase = false;
 
  this->dma_matrix_ = new MatrixPanel_I2S_DMA(mxconfig);
  dmamatrix = this->dma_matrix_;
  dmamatrix->begin();
  dmamatrix->setBrightness8(this->brightness_); //0-255
  dmamatrix->clearScreen();
  ESP_LOGI(TAG, "Finished Setup");
}

void HOT DmaMatrixDisplay::draw_absolute_pixel_internal(int x, int y, Color color) {
  uint16_t matrix_color = display::ColorUtil::color_to_565(color, display::ColorOrder::COLOR_ORDER_BGR);
  this->dma_matrix_->drawPixel(x, y, matrix_color);
}

void DmaMatrixDisplay::fill(Color color) {
  uint16_t matrix_color = display::ColorUtil::color_to_565(color,  display::ColorOrder::COLOR_ORDER_BGR);
  this->dma_matrix_->fillScreen(matrix_color);
}

void DmaMatrixDisplay::update() {
  this->do_update_();
}

void HOT DmaMatrixDisplay::display() {}

void DmaMatrixDisplay::set_pin_latch(InternalGPIOPin *pin_latch) { this->pin_latch_ = pin_latch; }

void DmaMatrixDisplay::set_pin_r1(InternalGPIOPin *pin_r1) { this->pin_r1_ = pin_r1; }

void DmaMatrixDisplay::set_pin_r2(InternalGPIOPin *pin_r2) { this->pin_r2_ = pin_r2; }

void DmaMatrixDisplay::set_pin_g1(InternalGPIOPin *pin_g1) { this->pin_g1_ = pin_g1; }

void DmaMatrixDisplay::set_pin_g2(InternalGPIOPin *pin_g2) { this->pin_g2_ = pin_g2; }

void DmaMatrixDisplay::set_pin_b1(InternalGPIOPin *pin_b1) { this->pin_b1_ = pin_b1; }

void DmaMatrixDisplay::set_pin_b2(InternalGPIOPin *pin_b2) { this->pin_b2_ = pin_b2; }

void DmaMatrixDisplay::set_pin_clk(InternalGPIOPin *pin_clk) { this->pin_clk_ = pin_clk; }

void DmaMatrixDisplay::set_pin_a(InternalGPIOPin *pin_a) { this->pin_a_ = pin_a; }

void DmaMatrixDisplay::set_pin_b(InternalGPIOPin *pin_b) { this->pin_b_ = pin_b; }

void DmaMatrixDisplay::set_pin_c(InternalGPIOPin *pin_c) { this->pin_c_ = pin_c; }

void DmaMatrixDisplay::set_pin_d(InternalGPIOPin *pin_d) { this->pin_d_ = pin_d; }

void DmaMatrixDisplay::set_pin_e(InternalGPIOPin *pin_e) { this->pin_e_ = pin_e; }

void DmaMatrixDisplay::set_pin_oe(InternalGPIOPin *pin_oe) { this->pin_oe_ = pin_oe; }

void DmaMatrixDisplay::set_width(uint8_t width) { this->width_ = width; }

void DmaMatrixDisplay::set_height(uint8_t height) { this->height_ = height; }

void DmaMatrixDisplay::set_brightness(uint8_t brightness) { this->brightness_ = brightness; }

int DmaMatrixDisplay::get_width_internal() { return this->width_; }

int DmaMatrixDisplay::get_height_internal() { return this->height_; }

}  // namespace dmamatrix_display
}  // namespace esphome
