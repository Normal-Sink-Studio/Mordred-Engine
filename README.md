
# Mordred Engine

Mordred Engine is an open source Entity Component System based game engine build in the Zig programming Language

## Why ECS
Entity Component System, or ECS for short, provides a simple, modular approach to game design using the principles of Data Oriented design principles. ECS also provides a way of keeping data stored in the CPU's Cache rather then constantly requesting data from RAM. As such, when done correctly ECS can provide many optimizations over the traditional approach of Object Oriented Design.

## Requirements
Zig 13.0.0 || Makefile (optional)

## Downloading
to download the Mordred Engine you can use

`git clone https://github.com/Normal-Sink-Studio/Mordred-Engine.git`

## Building
Mordred Engine has two build systems the `build.zig` file and the `Makefile`

 ### Build.zig
 to utilize the `build.zig` file you must type one of the following commands depending on OS (note other operating systems will be added later once Windows version is working)
 - **(Windows)** `zig build -Dtarget=x86_64-windows-msvc`
<!-- 
    - **(Linux)** `zig build -Dtarget=x86_64-linux-gnu`
    - **(MacOS)** `zig build -Dtarget=x86_64-macos`
    -->
 
 ### Makefile
 for a much simpler approach you can build the Engine using `make` in the `Mordred-Engine` directory on your machine

## Used in

- Feral Soul by Normal Sink Studios

  ![Feral Soul](docs/images/projects/FeralSoulTitle.png)

#



## Developers
- [Oreboat](https://github.com/Oreboat)
- [Yuki-Scribbles](https://github.com/yuki-scribbles)

![Normal Sink Studios](docs/images/logos/Normal_Sink_Studio3.png)
