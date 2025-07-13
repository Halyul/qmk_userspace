VIA_ENABLE = yes
MOUSEKEY_ENABLE = no
ENCODER_MAP_ENABLE = yes
ENCODER_ENABLE = yes        # Enable Encoder
TAP_DANCE_ENABLE = no

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_matrix_user.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dance_user.c
    SRC += tap_dance_setup.c
    SRC += tap_dance_mac_caps.c
    SRC += tap_dance_win_caps.c
endif
