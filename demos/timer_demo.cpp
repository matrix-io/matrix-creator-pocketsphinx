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
#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>

#include "matrix_hal/everloop.h"
#include "matrix_hal/everloop_image.h"
#include "matrix_hal/gpio_control.h"
#include "matrix_hal/matrixio_bus.h"

namespace hal = matrix_hal;

void clear(hal::EverloopImage *image1d) {
  for (hal::LedValue &led : image1d->leds) {
    led.red = 0;
    led.green = 0;
    led.blue = 0;
    led.white = 0;
  }
}

void setColor(hal::EverloopImage *image1d, int pos, int r, int g, int b,
              int w) {
  image1d->leds[pos % image1d->leds.size()].red = r;
  image1d->leds[pos % image1d->leds.size()].green = g;
  image1d->leds[pos % image1d->leds.size()].blue = b;
  image1d->leds[pos % image1d->leds.size()].white = w;
}

void drawProgress(hal::EverloopImage *image1d, unsigned counter) {
  int min = counter % image1d->leds.size();
  unsigned green = image1d->leds.size();
  for (int y = 0; y <= min; y++) {
    setColor(image1d, y, y * 2, green, 0, 0);
    green = image1d->leds.size() - y;
  }
}

void drawSeconds(hal::EverloopImage *image1d, unsigned seconds) {
  int sec = seconds % image1d->leds.size();
  setColor(image1d, sec, 0, 0, 40, 0);
}

int main(int argc, char *argv[]) {
  const unsigned ticks = 16;  // Beeps on alarm
  const int speakerpin = 15;  // GPIO pin for speaker
  const int outputmode = 1;

  hal::MatrixIOBus bus;
  bus.Init();

  hal::GPIOControl gpio;
  gpio.Setup(&bus);
  gpio.SetMode(speakerpin, outputmode);

  hal::EverloopImage image1d(bus.MatrixLeds());
  hal::Everloop everloop;
  everloop.Setup(&bus);

  unsigned counter = 0;
  unsigned seconds = 0;
  uint16_t speaker = 0;
  unsigned tick = 0;
  bool start_alarm = false;

  // configuration time (default 3min)
  float config_time = 180.0 / image1d.leds.size();
  if (argc == 2) {
    std::istringstream iss(argv[1]);
    int val;
    if (iss >> val) {
      std::cout << "config time set to: " << argv[1] << " secs.\n";
      config_time = (float)(val / image1d.leds.size());
      std::cout << "led config time: " << config_time << "\n";
    }
  }

  clear(&image1d);
  gpio.SetGPIOValue(speakerpin, 0);

  std::chrono::time_point<std::chrono::system_clock> smin, now, ssec, sbeep;
  smin = std::chrono::system_clock::now();
  ssec = sbeep = smin;

  while (1) {
    now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_minutes = now - smin;
    std::chrono::duration<double> elapsed_seconds = now - ssec;
    std::chrono::duration<double> elapsed_beep = now - sbeep;

    if (elapsed_minutes.count() > config_time) {
      smin = std::chrono::system_clock::now();
      ++counter;
    }

    if (elapsed_seconds.count() > config_time / image1d.leds.size()) {
      ssec = std::chrono::system_clock::now();
      ++seconds;
    }

    if (elapsed_beep.count() > 0.03) {
      sbeep = std::chrono::system_clock::now();
      speaker = ~speaker;
      tick++;
    }

    if ((counter % image1d.leds.size()) == 0 && tick < ticks) {
      gpio.SetGPIOValue(speakerpin, speaker);
      start_alarm = true;
    } else {
      gpio.SetGPIOValue(speakerpin, 0);
    }

    if ((counter % image1d.leds.size()) == image1d.leds.size() - 1) {
      start_alarm = false;
      tick = 0;
    }

    if (start_alarm && tick < ticks) {
      if (speaker) {
        clear(&image1d);
      } else {
        drawProgress(&image1d, counter);
        drawSeconds(&image1d, seconds);
      }
    } else {
      clear(&image1d);
      drawProgress(&image1d, counter);
      drawSeconds(&image1d, seconds);
    }
    everloop.Write(&image1d);
  }

  return 0;
}
