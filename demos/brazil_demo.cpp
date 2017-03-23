/*
 * Copyright 2016 <Admobilize>
 * MATRIX Labs  [http://creator.matrix.one]
 * This file is part of MATRIX Creator HAL
 *
 * MATRIX Creator HAL is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <iostream>

#include "matrix_hal/everloop_image.h"
#include "matrix_hal/everloop.h"
#include "matrix_hal/wishbone_bus.h"

namespace hal = matrix_hal;

int main() {
  hal::WishboneBus bus;

  bus.SpiInit();

  hal::Everloop everloop;
  hal::EverloopImage image1d;

  everloop.Setup(&bus);

  // unsigned counter = 0;

 while (1) {
    for (hal::LedValue& led : image1d.leds) {
      led.red = 0;
      led.green = 0;
      led.blue = 0;
      led.white = 0;
    }
    
    for (int i = 0; i < 12; ++i){
      image1d.leds[i].green = 20;
    }
    for (int i = 12; i < 23; ++i){
      image1d.leds[i].white = 20;
    }
    for (int i = 23; i < 35; ++i){
      image1d.leds[i].blue = 20;
    }

    everloop.Write(&image1d);
    // ++counter;
    usleep(20000);
  }

  return 0;
}