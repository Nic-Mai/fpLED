/**
 * Copyright (c) 2020 University of Applied Sciences Western Switzerland / Fribourg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * Project: HEIA-FR / Fast parallel ws281x LED control via USB
 *
 * Purpose: This module is a demo measuring performances with various parameters
 *
 * Author:  Nicolas Maier
 * Date:    June 2020
 */

#include "lib/led_controller.hpp"

#include <iostream>
#include <string>
#include <chrono>
#include <random>

int main(int argc, char** argv) {
    if (argc < 16) {
        std::cout << "Usage:" << std::endl;
        std::cout << argv[0] << " path_to_device strip_n led_n do_gamma_correction use_data_reduction use_huffman_coding recompute_code random_colors background_percentage max_r max_g max_b background_r background_g background_b" << std::endl;
        return 0;
    }

    size_t param_i = 0;
    std::cout << "Running benchmark with the following parameters:" << std::endl;
    std::cout << "           path_to_device: " << argv[++param_i] << std::endl;
    std::cout << "                  strip_n: " << argv[++param_i] << std::endl;
    std::cout << "                    led_n: " << argv[++param_i] << std::endl;
    std::cout << "      do_gamma_correction: " << argv[++param_i] << std::endl;
    std::cout << "       use_data_reduction: " << argv[++param_i] << std::endl;
    std::cout << "       use_huffman_coding: " << argv[++param_i] << std::endl;
    std::cout << "           recompute_code: " << argv[++param_i] << std::endl;
    std::cout << "            random_colors: " << argv[++param_i] << std::endl;
    std::cout << "    background_percentage: " << argv[++param_i] << std::endl;
    std::cout << "                    max_r: " << argv[++param_i] << std::endl;
    std::cout << "                    max_g: " << argv[++param_i] << std::endl;
    std::cout << "                    max_b: " << argv[++param_i] << std::endl;
    std::cout << "             background_r: " << argv[++param_i] << std::endl;
    std::cout << "             background_g: " << argv[++param_i] << std::endl;
    std::cout << "             background_b: " << argv[++param_i] << std::endl;
    std::cout << "(total: " << param_i << " parameters)" << std::endl << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    size_t strip_n = std::stoi(argv[2]);
    size_t led_n = std::stoi(argv[3]);
    bool use_huffman_coding = std::stoi(argv[6]);
    bool recompute_code = std::stoi(argv[7]) && use_huffman_coding;
    size_t random_colors = std::stoi(argv[8]);
    size_t background_percentage = std::stoi(argv[9]);

    LedController lc(argv[1], std::stoi(argv[4]), std::stoi(argv[5]), strip_n, led_n);

    ColorRGB max_color = {
        (uint8_t)std::stoi(argv[10]),
        (uint8_t)std::stoi(argv[11]),
        (uint8_t)std::stoi(argv[12]),
    };

    ColorRGB background_color = {
        (uint8_t)std::stoi(argv[13]),
        (uint8_t)std::stoi(argv[14]),
        (uint8_t)std::stoi(argv[15]),
    };
    
    for (size_t i = 0; i < strip_n; i++) {
        for (size_t j = 0; j < led_n; j++) {
            ColorRGB actual_color = dis(gen) * 100 < background_percentage
                ? background_color
                : random_colors
                    ? ColorRGB {
                        (uint8_t)(dis(gen) * max_color.r),
                        (uint8_t)(dis(gen) * max_color.g),
                        (uint8_t)(dis(gen) * max_color.b),
                    }
                    : max_color;
            lc.set_pixel_color(i, j, actual_color);
        }
    }
    if (use_huffman_coding) {
        lc.update_huffman_code();
    }
    lc.render();

    size_t count = 0;
    size_t max_count = 64;
    size_t total_sent_size = 0;
    std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
    for(;;) {
        if (recompute_code) {
            lc.update_huffman_code();
        }
        total_sent_size += lc.render();

        count++;
        if (count % max_count == 0) {
            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
            double elapsed_seconds = (std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count()/1000000.0);
            double fps = max_count/elapsed_seconds;
            std::cout << "fps: " << fps << " (" << (total_sent_size/1000.0 / elapsed_seconds) << " KB/s)" << std::endl;
            t0 = t1;
            total_sent_size = 0;
        }
    }

    return 0;
}
