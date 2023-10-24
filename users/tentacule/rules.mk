CONSOLE_ENABLE = yes
COMBO_ENABLE = no
TAP_DANCE_ENABLE  = yes
PROGRAMMER_ENABLE = yes

SRC += common.c
SRC += altcodes.c

ifeq ($(PROGRAMMER_ENABLE),yes)
	SRC += programmer.c
endif

ifeq ($(TAP_DANCE_ENABLE),yes)
	SRC += dances.c
endif
