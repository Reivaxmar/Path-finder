# Pathfinder
This project finds the shortest and longest path in a NxN grid, where connections between tiles can be open or closed.

## Usage
### Prerequisites
Just some basic stuff:
- Modern C/C++ compiler
- CMake installed

### Building the project
You can download a zip file or use git:
```bash
> mkdir ./Path-finder
> cd ./Path-finder
> git clone \
    https://github.com/Reivaxmar/Path-finder.git \
    Path-finder
> cd Path-finder
```

Great! Now you have the project, now you just need to build it:
```bash
> bash ./build.sh
> make
> ./pathfinder 5
```

Now your project should be up and running.


## External libraries
There is no need to have them installed, CMake will do it:
- SFML

## TODOs
- [x] Implement room graphics
- [x] Implement opening and closing
- [x] Implement algorithms for shortest and longest paths
- [ ] Make it fast (impossible because NP-complete?)