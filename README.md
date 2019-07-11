# Permutation-feed-povray
Creates a PovRay source code that in turn creates a 3D representation of a permutation number (see also https://github.com/Eidonko/CombinatorialMusic) 

Say you have the following string, "001122"

Break the string into three equal parts: "00", "11", "22".

Interpret each part as a ternary number: (0, 4, 8)

Interpret the tuple as a 3D point, say P.

Plot at P a unit cube or unit circle.

Repeat for the permutations that follow "001122", up to and including the last permutation, "221100"
(the order of generation is not important in this case, as we are generating objects in a 3D space).

Specify light sources, place an observer, specify materials with PovRay syntax.


All the above is done as follows:

./feedpovray --input=001122 --y=2 --z=4 --output=001122.pov --prologue=01.prologue --pigment="pigment { checker color Yellow color MidnightBlue } normal { bumps 0.4 scale 0.2 }  finish { phong 1 }"

Now open povray and load 001122.pov as follows:

    povray +P 001122.pov

This should create an image called 001122.png (depending on your povray installation, the actual filetype may differ.)

Note that currently feedpovray does not adjust the location parameter in the prologue. That is the location
of the observer, which determines the size of the object within the image. It will be necessary to adjust
that value in order to get the desired "view" to the rendered object.


A second example follows:

    ./feedpovray --input=000011222 --y=3 --z=6 --output=000011222.pov --prologue=prologue.2.012222222 --pigment="pigment { checker color Yellow color MidnightBlue } normal { bumps 0.4 scale 0.2 } finish { phong 1 }"
    povray +P 000011222.pov

The resulting picture is available as 000011222.png.


A third example is as follows:

    ./feedpovray --input=001122222222 --y=4 --z=8 --output=001122222222.pov --prologue=prologue.001122222222 --pigment="pigment { checker color Yellow color MidnightBlue } normal { bumps 0.4 scale 0.2 } finish { phong 1 }"
    povray +P 001122222222.pov

Please share with me the pictures that you create and like the most!

(Eidon@tutanota.com)

