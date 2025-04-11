<h1>Solar-system-project</h1>

Modeling and visualization of the solar system using OpenGL in C++ using aspects of textures and matrix transformations. Final project for the Computer Graphics course (DCA0114) at the Federal University of Rio Grande do Norte.

<img src="giphy_solar_system.gif" alt="animated" />

<h2>Dependencies</h2>

*   OpenGL
*   GNU GCC compiler

<h2>Note</h2>

If you are using the Windows operating system and want to run the code and use OpenGL, we recommend that you follow this [guide](https://medium.com/swlh/setting-opengl-for-windows-d0b45062caf) to install the dependencies.


<h2>Setup</h2>

    git clone https://github.com/reilta/solar-system-project

<h2>Running the code</h2>


    g++ -o main -lopengl32 -lglu32


<h2>Controls</h2>

*   **a** - moves the camera to the left
*   **d** - moves the camera to the right
*   **w** - moves the camera forward
*   **s** - moves the camera backwards
*   **q** - moves the camera up
*   **e** - moves the camera down

*   **i** - increases the camera's tilt
*   **I** - decrements the camera's tilt

*   **z** - zoom in
*   **Z** - zoom out
*   **r** - rotates the camera clockwise
*   **R** - rotates the camera counter-clockwise

*   **p** - rotates objects on their own axis
*   **y** - rotates objects around the starting point
*   **g** - automatic object rotation

