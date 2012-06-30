# Dutch Nao Team Calibration Tool
A simple tool for selecting the HSV color range of certain parts of an image.
It should be compatible with Windows too, but I haven't the vaguest clue how to
compile it (try QtCreator or Visual Studio).

## Dependencies:

* libqt4-dev
* OpenCV

## Compilation instructions
Assuming you want a seperate "build" folder:

    mkdir build
    cd build

Followed by:

    cmake ..
    make

Alternatively you can load in CMakeLists.txt in practically every IDE and use
their build function.
