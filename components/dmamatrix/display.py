import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import display
from esphome.const import CONF_WIDTH, \
    CONF_ID, CONF_LAMBDA, CONF_PAGES, CONF_BRIGHTNESS, CONF_RGB_ORDER, \
    CONF_PIN_A, CONF_PIN_B, CONF_PIN_C, CONF_PIN_D, \
    CONF_CHIPSET, CONF_MULTIPLEXER


pxmatrix_ns = cg.esphome_ns.namespace('dmamatrix_display')

pxmatrix_gpio = pxmatrix_ns.class_('DmaMatrixDisplay', cg.PollingComponent, display.DisplayBuffer)

# new Consts
CONF_HEIGHT = 'height'
CONF_PIN_E = 'pin_e'
CONF_PIN_LATCH = 'pin_latch'
CONF_PIN_OE = 'pin_oe'
CONF_PIN_R1 = 'pin_R1'
CONF_PIN_G1 = 'pin_G1'
CONF_PIN_B1 = 'pin_B1'
CONF_PIN_R2 = 'pin_R2'
CONF_PIN_G2 = 'pin_G2'
CONF_PIN_B2 = 'pin_B2'
CONF_PIN_CLK = 'pin_clk'


DriverChips = pxmatrix_ns.enum('DriverChips')
DRIVER_CHIPS = {
    "FM6126A": DriverChips.FM6126A,
    "FM6124": DriverChips.FM6124
}

CONFIG_SCHEMA = cv.All(
    display.FULL_DISPLAY_SCHEMA.extend({
        cv.GenerateID(): cv.declare_id(pxmatrix_gpio),
        cv.Optional(CONF_WIDTH, default="64"): cv.uint8_t,
        cv.Optional(CONF_HEIGHT, default="64"): cv.uint8_t,
        cv.Optional(CONF_BRIGHTNESS, default="255"): cv.uint8_t,
        # cv.Optional(CONF_PIN_LATCH, default="GPIO33"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_R1  , default="GPIO17"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_G1  , default="GPIO2"):  pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_B1  , default="GPIO16"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_R2  , default="GPIO04"):  pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_G2  , default="GPIO15"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_B2  , default="GPIO12"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_A   , default="GPIO26"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_B   , default="GPIO13"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_C   , default="GPIO14"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_D   , default="GPIO27"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_E   , default="GPIO22"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_OE  , default="GPIO32"): pins.gpio_output_pin_schema,
        # cv.Optional(CONF_PIN_CLK , default="GPIO25"): pins.gpio_output_pin_schema,
        cv.Optional(CONF_CHIPSET, default="FM6124"): cv.enum(DRIVER_CHIPS),
     }).extend(cv.polling_component_schema('.1s')),
    cv.has_at_most_one_key(CONF_PAGES, CONF_LAMBDA))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    yield cg.register_component(var, config)
    yield display.register_display(var, config)

    if CONF_LAMBDA in config:
        lambda_ = yield cg.process_lambda(config[CONF_LAMBDA], [(display.DisplayBufferRef, 'it')],
                                          return_type=cg.void)
        cg.add(var.set_writer(lambda_))

    if CONF_PIN_LATCH in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_LATCH])
        cg.add(var.set_pin_latch(latch))


    if CONF_PIN_B1 in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_B1])
        cg.add(var.set_pin_a(latch))
    
    if CONF_PIN_B2 in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_B2])
        cg.add(var.set_pin_a(latch))

    if CONF_PIN_R2 in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_R2])
        cg.add(var.set_pin_a(latch))

    if CONF_PIN_R1 in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_R1])
        cg.add(var.set_pin_a(latch))

    if CONF_PIN_G1 in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_G1])
        cg.add(var.set_pin_a(latch))

    if CONF_PIN_G2 in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_G2])
        cg.add(var.set_pin_a(latch))

    if CONF_PIN_CLK in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_CLK])
        cg.add(var.set_pin_a(latch))


    if CONF_PIN_A in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_A])
        cg.add(var.set_pin_a(latch))

    if CONF_PIN_B in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_B])
        cg.add(var.set_pin_b(latch))

    if CONF_PIN_C in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_C])
        cg.add(var.set_pin_c(latch))

    if CONF_PIN_D in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_D])
        cg.add(var.set_pin_d(latch))

    if CONF_PIN_E in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_E])
        cg.add(var.set_pin_e(latch))

    if CONF_PIN_OE in config:
        latch = yield cg.gpio_pin_expression(config[CONF_PIN_OE])
        cg.add(var.set_pin_oe(latch))

    if CONF_WIDTH in config:
        cg.add(var.set_width(config[CONF_WIDTH]))

    if CONF_HEIGHT in config:
        cg.add(var.set_height(config[CONF_HEIGHT]))

    if CONF_BRIGHTNESS in config:
        cg.add(var.set_brightness(config[CONF_BRIGHTNESS]))

    cg.add_library("Spi", "1.0")
    cg.add_library("Wire", "1.0")
    cg.add_library("Adafruit BusIO", "1.10.1")
    # Adafruit GF https://github.com/adafruit/Adafruit-GFX-Library/releases
    cg.add_library("adafruit/Adafruit GFX Library", "1.10.12")
    # https://github.com/2dom/PxMatrix/blob/master/PxMatrix.h
    cg.add_library("mrfaptastic/ESP32 HUB75 LED MATRIX PANEL DMA Display", "2.0.6")
