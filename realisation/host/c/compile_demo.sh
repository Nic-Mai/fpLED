# Copyright (c) 2020 University of Applied Sciences Western Switzerland / Fribourg
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#
# Project: HEIA-FR / Fast parallel ws281x LED control via USB
#
# Purpose: This script compiles the demo programs (which use the C lib)
#
# Author:  Nicolas Maier
# Date:    June 2020

gcc demo_telecom_tower_line.c lib/led_controller.c lib/led_matrix.c -Ofast -Wall -Wextra -o demo_telecom_tower_line
gcc demo_telecom_tower_text.c lib/led_controller.c lib/led_matrix.c -Ofast -Wall -Wextra -o demo_telecom_tower_text
