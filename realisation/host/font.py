
font = {
    '0': [
        0x38,
        0x44,
        0x44,
        0x44,
        0x44,
        0x44,
        0x44,
        0x38,
    ],
    '1': [
        0x30,
        0x10,
        0x10,
        0x10,
        0x10,
        0x10,
        0x10,
        0x7C,
    ],
    '2': [
        0x38,
        0x44,
        0x04,
        0x08,
        0x10,
        0x20,
        0x44,
        0x7C,
    ],
    '3': [
        0x38,
        0x44,
        0x04,
        0x18,
        0x04,
        0x04,
        0x44,
        0x38,
    ],
    '4': [
        0x0C,
        0x14,
        0x14,
        0x24,
        0x44,
        0x7E,
        0x04,
        0x0E,
    ],
    '6': [
        0x3C,
        0x20,
        0x20,
        0x38,
        0x04,
        0x04,
        0x44,
        0x38,
    ],
    '5': [
        0x1C,
        0x20,
        0x40,
        0x78,
        0x44,
        0x44,
        0x44,
        0x38,
    ],
    '7': [
        0x7C,
        0x44,
        0x04,
        0x08,
        0x08,
        0x08,
        0x10,
        0x10,
    ],
    '8': [
        0x38,
        0x44,
        0x44,
        0x38,
        0x44,
        0x44,
        0x44,
        0x38,
    ],
    '9': [
        0x38,
        0x44,
        0x44,
        0x44,
        0x3C,
        0x04,
        0x08,
        0x70,
    ],
}


def font_is_on(c, x, y):
    return font[c][x] & (1 << (7-y)) != 0
