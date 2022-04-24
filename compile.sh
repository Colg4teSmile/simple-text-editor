#!/bin/bash

gcc `pkg-config --cflags gtk+-3.0` -o text_editor main.c  gap_buffer.c  tools.c gui.c `pkg-config --libs gtk+-3.0`