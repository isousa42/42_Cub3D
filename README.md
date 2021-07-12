
# 42_Cub3D

![42](https://user-images.githubusercontent.com/76601369/110706242-77158d00-81ef-11eb-8085-5da6f0988553.jpg)
> *"This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever."*

> *"Now, it’s your turn to relive History..."*




## Description

The aim of this project is to explore ray-casting with the goal to make a dynamic view inside a maze.

It is the first design project in the 42Cursus and the students are able to learn about graphics, events and masks, colors, fill shapes, windows, etc.

To be able to do this 3D Game is necessary to "explore the playful practical applications of mathematics without having to understand the specifics.

The project must be done using the Ray-Casting principles and it should be a 3D graphical representation from inside of a maze from a first-person perpective.


  
## Documentation

[42 Docs - MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)

[Raycasting - Lode Vandevenne](https://lodev.org/cgtutor/raycasting.html)



  
## Compilation Process

To compile the mandatory part of the Project:

```bash
  make all
```

To compile the bonus part of the Project:

```bash
  make bonus
```

§ You must be in the root of the repository to do the compilation.

§ You can delete the object and the executable using:
```bash
  make fclean
```

  
## 🛠 Skills
Rigor, Imperative Programming, Graphics, Algorithms & AI, C Language

  
## Basics of the Project

My Cub3D can be divided in two parts: Mandatory and Bonus.

Bonus is, basically, some improvements to the Mandatory part of the Project.
Mandatory uses the Raycasting Algorithm, from a first-person view, to put images
between the ceiling and the floor of the maze, with the necessary calculations
to make it realistic (like the Plane of View we have). 

The Height and Width of the textures will depend on the distance that the player is from the wall.
If it is far, the wall will be smaller. If it is close, the wall will be bigger.
This effect is obtained because the window of the game is divided in two parts (ceiling and floor)
and the textures are uploaded to this window, between these two parts, after the calculations
to know the size are made.

The player is able to move inside the maze. To make it possible is needed to use events and masks,
so the user can use the keyboard to go around the maze. Everytime WASD or Arrow-Up and Arrow-Down are pressed
the player will move and the program will run the calculations again and upload the new
images to the window. It is always updating the window, so it looks like the player is actualy
inside of a maze. 

The Map and the configurations of the game are passed to the program by argument with the .cub file.
This file contains some util information like the Resolution of the window, the Map of the game, the colour of the ceiling and floor and the path to the textures that will be used.
Without this file, the program will not run and will display an Error Message to remember the User to pass the 
path of the .cub file.

In some situations, like the Map is not completely closed or there are more than one player of the Map, the program will exit
and display an Customized Error Message. If he configrations are not accordingly to the needs of the program, it will not work.

In the Bonus, it is included the upload of the textures for the ceiling and floor as well as the Sprites around the Map. 
Wall and Sprite Colision was also implemented so the player can't pass throught it.

All the code will be commented for better understanding.





  
## Feedback or Questions

If you have any feedback or Questions about the code, please send me an email to isousa@student.42lisboa.com
