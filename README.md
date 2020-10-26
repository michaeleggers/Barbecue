# Barbecue
Two Player Sokoban-Clone. Made at the Barbecue Gamejam 2017 within 8 hrs.

![alt text](https://github.com/michaeleggers/Barbecue/blob/master/readmeassets/bbq.png "gameplay")

This was our first jam.

There is quite a bit of code smell going on but that's ok. The goal was to actually get something done rather than aiming for the best possible design.

## Building for Microsoft Visual Studio 2015

You will need SDL2 and SDL2_Image. The Dev libraries can be downloaded here:

https://www.libsdl.org/download-2.0.php

https://www.libsdl.org/projects/SDL_image/

You will need the 64bit ones for Visual Studio.

1.) clone the repo

2.) Extract the downloaded SDL2 and SDL2_Image libraries in ThirdParty so the folder structure looks like this:

`..\Barbecue\ThirdParty\SDL2_image-2.0.1`

`..\Barbecue\ThirdParty\SDL2-2.0.5`


3.) In the Barbecue folder: `mkdir build && cd build`

4.) `cmake -G "Visual Studio 14 2015 Win64" ..`

for Visual Studio 2017: `Visual Studio 15 2017 Win64`

5.) copy all DLLs from `ThirdParty/sdlimage/bin/x64/`

to the release/debug folders in build folder.

6.) done :)

