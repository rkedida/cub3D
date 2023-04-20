# Cub3D

This is a project for the 42 school curriculum, which is about creating a "realistic" 3D graphical representation of the inside of a maze from a first-person perspective using the Ray-Casting principles.

## Installation
To run this project, you need to have the miniLibX library installed on your system. If you're on a Mac, it should already be installed. If not, you can get it from the official repo. After that, clone the repository and run make in the root directory to build the executable file.
```
git clone https://github.com/rkedida/cub3D.git
```
```
cd repo
```
```
make
```
## Usage
To run the program, you need to provide a valid .cub file as an argument. For example:
```
./cub3D maps/map.cub
```
The program will display a window showing the 3D representation of the map described in the .cub file. You can use the arrow keys to look around, and the `W`, `A`, `S`, `D` keys to move. Press `ESC` or click the red cross on the window's frame to quit the program.

## Map format
The map file must be in the format of .cub. The map must be composed of only 6 possible characters: `0` for an empty space, `1` for a wall, and `N`, `S`, `E` or `W` for the player’s start position and spawning orientation.
The map must be closed/surrounded by walls, and except for the map content, each type of element can be separated by one or more empty line(s). Except for the map content which always has to be the last, each type of element can be set in any order in the file.
Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order.

## Contributors
This project was completed by:
Robel Kedida @robelkedida
Shettima Ali @Shetteemah

Built With

