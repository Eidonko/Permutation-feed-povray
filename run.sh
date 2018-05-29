#!/usr/bin/env bash
feedpovray --input=012345678 --y=3 --z=6 --output=3333.pov \
               --prologue=01.prologue \
               --pigment="pigment { checker color Yellow color MidnightBlue } normal \
                   { bumps 0.4 scale 0.2 }  finish { phong 1 }"
