# Rapunzel
## Table of Contents

## General info
Rapunzel is a simple C++ game based on Timber!, which is the first lesson in Beginning C++ Game Programming, 2nd ed. by John Horton. Timber is, in turn, based on Timberman on Steam.
Rapunzel requires the 32-bit versions of SFML 2.6.2 and the corresponding GCC 13.1.0 mingw. I configured my environment in CodeBlocks, but John Horton recommends using Visual Studio Code.
I changed the game from a Timber clone with a lumberjack chopping down a tree and avoiding the branches to a wizard attacking a tower with a staff and avoiding Rapunzel's braids.
All graphics, sounds, and fonts are used under the Creative Commons License, public domain, free for personal/non-commercial use, and similar licenses or terms of use.

## Collaborators
Jason Ash, Computer Science Major

## Technologies
Although Rapunzel was programmed and compiled in CodeBlocks for Windows, John Horton mentions that the projects in his book can be built in Linux and on Macs.

## Setup
1. Download codeblocks-25.03mingw-setup.exe from https://www.codeblocks.org/downloads/binaries/
2. Download GCC 13.1.0 MinGW (DW2) - 32-bit and WinLibs MSVCRT 13.1.0 (32-bit; in the yellow box with red text at the top of the Webpage) from https://www.sfml-dev.org/download/sfml/2.6.2/
3. Extract both of those in suitable folders/directories.
4. Watch the YouTube video by FF Dev on how to set up your CodeBlocks to use SFML at https://www.youtube.com/watch?v=NxB2qsUG-qM&t=556s
5. Alternatively, you could follow the tutorial in the book by John Horton for Visual Studio Code (but I didn't have any luck getting it to work that way).
6. Download main.cpp, the .png graphics files, the font, and the sound .wav files from this repository.
7. Relative to main.cpp, place the .png files in a subfolder called "graphics", the .wav files in a subfolder called "sounds", and the .ttf in a subfolder called "fonts".
8. Compile the .cpp source file in CodeBlocks, and enjoy the game.

## Usage
* The game starts "paused" at a screen similar to the end game screen and prompts the user to press the Enter key.
* Use the right arrow key to attack the tower at the right side of it, and the left arrow key to attack the tower from the left side. Each time the tower is attacked, one is added to the score.
* Each time you attack the tower, Rapunzel's heavy braids come down one position.
* If one of them makes contact with the wizard, he dies, a death wail sound is played, a message displays saying "SQUISHED", and the player must press the Enter key to start another game.
* By attacking the tower, you add to the time remaining, but per the game mechanics, less time keeps getting added the longer gameplay is in progress.
* If you run out of time, a message displays saying, "Out of time!! (This is the second way to lose the game.)
* Press the Esc key at any time to exit the game.

## Minimum hardware requirements
Any computer that is at least a Pentium 4 with 1 or 2 GB of system RAM running Windows 7 SP1 or later with sufficient hard drive space should be able to play this game.

## Project Status
Released on GitHub as-is.

## Release date
22 June, 2025

## Sources
Horton, John. Beginning C++ Game Programming, 2nd ed., Packt Publishing, 2019.
* playerLeft.png and playerRight.png from Wizard by Firkin on https://openclipart.org/detail/229148/wizard (public domain)
* wizardTower.png from Kehlen tower.jpg by Jonny Chicago on https://commons.wikimedia.org/wiki/File:Kehlen_tower.jpg (GNU Free Documentation License)
* fairy.png on https://vectorportal.com/vector/fairy-vector.ai/8216 (Creative Commons Attribution License/royalty free)
* background.png from Mountain Landscape Free Stock Image by Sam Ferrar at https://stocksnap.io/photo/mountain-landscape-D9QN84B8D8 (Commons Deed/public domain)
* staffLeft.png and staffRight.png from Low-Tier Mage Staff by slipled at https://www.deviantart.com/slipled/art/Low-Tier-Mage-Staff-1123583629 (Creative Commons Non-Commerical License)
* 



## Contact
Jason Ash - wizardofki@gmail.com
