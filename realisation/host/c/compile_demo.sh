
gcc main.c driver/led_controller.c -Ofast -Wall -Wextra -o main
gcc demo_telecom_tower.c driver/led_controller.c driver/neopixel_matrix.c -Ofast -Wall -Wextra -o demo_telecom_tower
