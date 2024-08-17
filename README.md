# 3D Robotic Arm

This repository contains an OpenGL project for drawing a 3D robotic arm. The user can interact with the robotic arm and rotate its parts using the specified keys.

## Screenshot
<div align="center">
  <img src="img/arm.png" alt="3D Robotic Arm" height="400em">
</div>

## Prerequisites

To ensure the project runs correctly on different platforms, specific libraries are included based on the operating system:

```c
#ifdef __APPLE__ // MacOS
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else // Windows and Linux
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
```

## Features

- **Shoulder Rotation:**
  - Key `o`: Rotates the shoulder clockwise.
  - Key `O`: Rotates the shoulder counterclockwiseo.
  
- **Elbow Rotation:**
  - Key `c`: Rotates the elbow clockwise.
  - Key `C`: Rotates the elbow counterclockwise.

- **Hand Rotation:**
  - Key `m`: Rotates the hand clockwise
  - Key `M`: Rotates the hand counterclockwise.

- **Thumb Rotation:**
  - Key `p`: Rotates the thumb clockwise.
  - Key `P`: Rotates the thumb counterclockwise.
  
- **Index Finger Rotation:**
  - Key `i`: Rotates the index finger clockwise.
  - Key `I`: Rotates the index finger counterclockwise.
  
- **Ring Finger Rotationr:**
  - Key `a`: Rotates the ring finger clockwise.
  - Key `A`: Rotates the ring finger counterclockwise.
  
- **Full Arm Rotation Around Y-Axis:**
  - Key `y`: Rotates the entire arm clockwise.
  - Key `Y`: Rotates the entire arm counterclockwise.
  
- **Exit the Program:**
  - Key `ESC`: Closes the program.

## Contribution

Feel free to open issues or submit pull requests. All contributions are welcome!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
