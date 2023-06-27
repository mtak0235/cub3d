# 1. What is cub3D?

This project is the implementation of simple Ray Caster to render 3D map from the given texture file.

# 2. How to compile the implemented program?

There is a `Makefile` which provides the common rules (all, clean, fclean, re) including bonus rule in the folder. After compiling all of the source codes, the program file will be generated.
But i didn't make bonus part.
* For the Mandatory
> make all

# 3. How to execute the implemented program?
The name of this program is `cub3D` and it takes the name of the scene file which ends with `.cub` as a string argument. To execute the program, type the command listed below.
> ./cub3D ./maps/\<scene-name>

# 4. How to save the Scene as a BMP file?
cub3D supports to save the scene as a BMP file. It is necessary to specity `--save` option after the execution command.
> ./cub3D ./maps/\<scene-name> --save

# 5. Which are the allowed external functions?

1. `open` on \<fcntl.h>
2. `close` on \<fcntl.h>
3. `read` on \<unistd.h>
4. `write` on \<unistd.h>
5. `printf` on \<stdio.h>
6. `perror` on \<stdio.h>
7. `strerror` on \<string.h>
8. `malloc` on \<stdlib.h>
9. `free` on \<stdlib.h>
10. `exit` on \<stdlib.h>

# 6. Features

1. Internally this program use the MiniLibX library. 
2. MiniLibX is using the AppKit and OpenGL to render the pixels on the Screen. To make the executable file, AppKit and OpenGL is used as a framework option on the Compile Command.
3. It is allowed to accept Key Hook Events. Press ESC on the Keyboard to terminate the program. Also, it is okay to press the cross button on the Top-Left Corner of the Screen. 

# 7. Demo

