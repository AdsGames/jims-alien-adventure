#include "key_data.h"

// Init key
key_data::key_data (int newValue) {
  value = newValue;
}

// Destroy key
key_data::~key_data() { }

int key_data::getValue() {
  return value;
}
