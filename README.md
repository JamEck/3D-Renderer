Simple 3D Renderer written in C++ from scratch, with exception of SDL2.0 for creating a window and listening for keyboard inputs.

SDL2 Framework is a required install. Just download the framework and put it in:
/Library/Frameworks (on Mac)

Draws three types of 3D shapes: Cubes, Spheres and a cluster of Random Points.
Projects the points from 3D space to the 2D screen, 
then interpolates between the points to draw the shapes' edges.

Controls:

Space: cycle through the shapes to select the one you want to interact with.

W,A,S,D: move selected shape left or right, and in or out.

K,P: rotate the selected shape on the vertical axis (y-axis).

RShift,Apostrophe: increase or decrease the Field Of View, respectively.

Esc: end program.