#include "cat9554.h"
#include "esphome/core/log.h"

namespace esphome {
namespace cat9554 {

static const char *TAG = "cat9554";

void CAT9554Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up CAT9554...");
  if (!this->read_gpio_()) {
    ESP_LOGE(TAG, "CAT9554 not available under 0x%02X", this->address_);
    this->mark_failed();
    return;
  }

  this->write_gpio_();
  this->read_gpio_();
}
void CAT9554Component::dump_config() {
  ESP_LOGCONFIG(TAG, "CAT9554:");
  LOG_I2C_DEVICE(this)
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with CAT9554 failed!");
  }
}
bool CAT9554Component::digital_read(uint8_t pin) {
  this->read_gpio_();
  return this->input_mask_ & (1 << pin);
}
void CAT9554Component::digital_write(uint8_t pin, bool value) {
  if (value) {
    this->output_mask_ |= (1 << pin);
  } else {
    this->output_mask_ &= ~(1 << pin);
  }

  this->write_gpio_();
}
void CAT9554Component::pin_mode(uint8_t pin, uint8_t mode) {
  switch (mode) {
    case CAT9554_INPUT:
      // Clear mode mask bit
      this->mode_mask_ |= (1 << pin);
      // Write GPIO to enable input mode
      this->write_gpio_();
      break;
    case CAT9554_OUTPUT:
      // Set mode mask bit
      this->mode_mask_ &= ~(1 << pin);
      break;
    default:
      break;
  }
}
bool CAT9554Component::read_gpio_() {
  if (this->is_failed())
    return false;
  bool success;
  uint8_t data[2];
  success = this->read_bytes_raw(data, 1);
  this->input_mask_ = data[0];

  if (!success) {
    this->status_set_warning();
    return false;
  }
  this->status_clear_warning();
  return true;
}
bool CAT9554Component::write_gpio_() {
  if (this->is_failed())
    return false;

  uint16_t value = 0;
  // Pins in OUTPUT mode and where pin is HIGH.
  value |= this->mode_mask_ & this->output_mask_;
  // Pins in INPUT mode must also be set here
  value |= ~this->mode_mask_;

  uint8_t data[2];
  data[0] = value;
  data[1] = value >> 8;
  if (!this->write_bytes_raw(data, 1)) {
    this->status_set_warning();
    return false;
  }

  this->status_clear_warning();
  return true;
}
float CAT9554Component::get_setup_priority() const { return setup_priority::IO; }

void CAT9554GPIOPin::setup() { this->pin_mode(this->mode_); }
bool CAT9554GPIOPin::digital_read() { return this->parent_->digital_read(this->pin_) != this->inverted_; }
void CAT9554GPIOPin::digital_write(bool value) { this->parent_->digital_write(this->pin_, value != this->inverted_); }
void CAT9554GPIOPin::pin_mode(uint8_t mode) { this->parent_->pin_mode(this->pin_, mode); }
CAT9554GPIOPin::CAT9554GPIOPin(CAT9554Component *parent, uint8_t pin, uint8_t mode, bool inverted)
    : GPIOPin(pin, mode, inverted), parent_(parent) {}

}  // namespace cat9554
}  // namespace esphome
