# Permutation-feed-povray
Creates a PovRay source code that in turn creates a 3D representation of a permutation number (see Permutation-numbers) 

Say you have the following string "001122"

This is a string, but you can also think of it as a ternary number.

Now break the number in three equal parts: "00", "11", "22".

Interpret each part as a ternary number: (0, 4, 8)

Interpret the tuple as a 3D coordinate: P

Plot at P a unit cube, or unit circle, or unit whatever

Repeat for the permutation that follows "001122", up to and including "221100"

Specify light sources, place an observer, specify materials etc etc with PovRay syntax

All the above is done as follows:

./feedpovray --input=001122 --y=2 --z=4 --output=001122.pov --prologue=01.prologue --pigment="pigment { checker color Yellow color MidnightBlue } normal { bumps 0.4 scale 0.2 }  finish { phong 1 }"

Now open povray and load 001122.pov

    povray +P 001122.pov

This should create an image called 001122.png (other filetypes are possible)

Note that currently feedpovray does not adjust the location parameter in the prologue. That is the location
of the observer, which determines the size of the object within the image. It will be necessary to adjust
that value in order to get the desired "view" to the rendered object.
