# resa - playbook (concept)

**_tbc..._**

## Summery
Simple and very straight forward. You are a lord or king or whatever and get into an unknown, island based, world. You got your ship, some materials and some gold. Now you need to develop your chosen island into a great trading and self-sustaining city. If you lose all your money or your population ist starving to death or leaves your city for other reasons you are defeated.
<br><br>
## Basic Information
- no special century at the moment
- no main character
- point of view: like god
- starting point is a ship and harbor
- materials for buildings:
  - wood
  - stone
  - marble
  - gold
- ressources are limited, except of regrowing and reclaimable things
- islands with different ressources and sizes
- trading ressources between islands by ships
- four different cultures with special trades
- population with development
  - pioneer, citizen, merchant
  - different needs at each level in ressources, buldings and science
  - upgrade and downgrade possible
- mining and farming
- exploration system to increase mining, farming and trading
<br><br>
## Development and Dependencies
- written in C (C99-Standard)
- using [Simple DirectMedia Layer](https://wiki.libsdl.org) SDL2 with SDL_mixer, SDL_image and SDL_ttf
- source code style is based on [Linux Kernel Standard](https://www.kernel.org/doc/html/v4.10/process/coding-style.html)
- branch for releases is ```main```; features or bugfixes need separate branches
- pull request for bugfixes against branch ```main```, except another branch for this bug was created
- versioning: major.features.bugfixes (e.g.: 1.5.21)
- platform independent
- general purpose source code will be included in mpos library
<br><br>
## Rendering
- window mode
- minimum resolution: 800 x 600
- minimum FPS: around 60
- Isometic-2D
<br><br>
## Controls
- arrow keys and wasd to move the world
- F2: debug screen
- F3: screenshot
- mouse button left: everything else
<br><br>
## World structure
- grid layout in 16x16
- world devided in fields
- a field has different layers
  - layer 1: terrain
  - layer 2: structures
  - layer 3: fauna
  - layer 4: flora
  - layer 5: objects
