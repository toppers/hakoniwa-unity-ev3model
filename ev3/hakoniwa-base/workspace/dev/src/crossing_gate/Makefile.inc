mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += util.o timer_ex.o horn.o manual_switch.o train_detector.o train_checker.o gate_rotator.o warning_light.o railroad_crossing.o

SRCLANG := c

# APPL_DIR += $(mkfile_path)app

# INCLUDES += \
# 	-I$(mkfile_path)app \
