# Pacman
A simple 3D game written in C++ with OpenGL

## Usage
Requirements:
```bash
sudo apt-get install libglew-dev libsoil-dev freeglut3-dev
```
Starting game
```bash
git clone https://github.com/kczarnota/Pacman_openGL
cd Pacman_openGL
mkdir build
cd build
cmake ..
make
./Pacman
```
Controls:
* use arrow keys to rotate the board
* use 'm' key to turn off/on fog effect
* use 'i' and 'k' keys to change the lightning
* use '+' and '-' to zoom in/out the board
* use 'w','a','s', 'd' to move Pacman