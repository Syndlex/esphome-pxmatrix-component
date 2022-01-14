#include "dmamatrix.h"
#include "esphome/core/application.h"

#define R1_PIN 17
#define G1_PIN 2
#define B1_PIN 16
#define R2_PIN 4
#define G2_PIN 15
#define B2_PIN 12
#define A_PIN 26
#define B_PIN 13 
#define C_PIN 14
#define D_PIN 27
#define E_PIN 22
#define LAT_PIN 33
#define OE_PIN 32
#define CLK_PIN 25


static const char *TAG = "dmamatrix_display";

namespace esphome {
namespace dmamatrix_display {

MatrixPanel_I2S_DMA *dmamatrix = nullptr;



void display_updater() {  }

float DmaMatrixDisplay::get_setup_priority() const { return setup_priority::PROCESSOR; }

void DmaMatrixDisplay::setup() {
  ESP_LOGCONFIG(TAG, "Starting setup...");
  HUB75_I2S_CFG::i2s_pins _pins={R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
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
  dmamatrix->setBrightness8(255); //0-255
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

// void dmamatrixDisplay::set_pin_latch(InternalGPIOPin *pin_latch) { this->pin_latch_ = pin_latch; }

// void dmamatrixDisplay::set_pin_a(InternalGPIOPin *pin_a) { this->pin_a_ = pin_a; }

// void dmamatrixDisplay::set_pin_b(InternalGPIOPin *pin_b) { this->pin_b_ = pin_b; }

// void dmamatrixDisplay::set_pin_c(InternalGPIOPin *pin_c) { this->pin_c_ = pin_c; }

// void dmamatrixDisplay::set_pin_d(InternalGPIOPin *pin_d) { this->pin_d_ = pin_d; }

// void dmamatrixDisplay::set_pin_e(InternalGPIOPin *pin_e) { this->pin_e_ = pin_e; }

// void dmamatrixDisplay::set_pin_oe(InternalGPIOPin *pin_oe) { this->pin_oe_ = pin_oe; }

// void dmamatrixDisplay::set_width(uint8_t width) { this->width_ = width; }

// void dmamatrixDisplay::set_height(uint8_t height) { this->height_ = height; }

// void dmamatrixDisplay::set_brightness(uint8_t brightness) { this->brightness_ = brightness; }

// void dmamatrixDisplay::set_row_patter(uint8_t row_pattern) { this->row_pattern_ = row_pattern; }

// void dmamatrixDisplay::set_driver_chips(DriverChips driver_chips) { this->driver_chips_ = driver_chips; }

// void dmamatrixDisplay::set_color_orders(ColorOrders color_orders) { this->color_orders_ = color_orders; }

// void dmamatrixDisplay::set_scan_patterns(ScanPatterns scan_patterns) { this->scan_patterns_ = scan_patterns; }

// void dmamatrixDisplay::set_mux_patterns(MuxPatterns mux_patterns) { this->mux_patterns_ = mux_patterns; }

// void dmamatrixDisplay::set_mux_delay(uint8_t mux_delay) { this->mux_delay_ = mux_delay; }

// void dmamatrixDisplay::set_rotate(bool rotate) { this->rotate_ = rotate; }

// void dmamatrixDisplay::set_flip(bool flip) { this->flip_ = flip; }

int DmaMatrixDisplay::get_width_internal() { return this->width_; }

int DmaMatrixDisplay::get_height_internal() { return this->height_; }

}  // namespace dmamatrix_display
}  // namespace esphome
