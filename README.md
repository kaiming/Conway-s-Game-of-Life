# Conway-s-Game-of-Life
A classic rendition of the famous Conway's Game of Life. Conway's Game of Life is a zero-player game that runs indefinitely based on the initial given input and a set of rules. The game revolves around the idea of tracking the behaviour of "cells" across any number of generations (or turns). Cells can either continue living, die, or come alive after each generation based on the set of rules below.

Game rules:
• a living cell with fewer than two live neighbours or more than three live neighbours dies,
• a living cell with either two or three live neighbours continues to live, and
• a dead cell with exactly three live neighbours comes to life; otherwise, it remains dead.

Utilizes design patterns such as observers and MVC (Model View Controller). XWindows graphics is used to provide a GUI for the game board.
