VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes
TAP_DANCE_ENABLE = yes

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_matrix_user.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dance_setup.c
    SRC += tap_dance_mac_caps.c
    SRC += tap_dance_win_caps.c
endif
