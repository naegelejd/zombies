NOTES
=====

logical flow:

- load resources
- create main window
- main menu:
  - get input
  - determine which button has focus
  - determine if button pressed
    if so, change state or exit
  - display background
  - display buttons
- options menu:
  - get input
  - determine which button has focus
  - determine if button pressed
    if so, toggle option or go back a state
  - display background
  - display buttons
- playing state:
  - load correct level
  - get input
  - determine if menu requested
    if so, push state
  - update environment/level
  - update player
  - update enemies
  - check for collision
  - draw background
  - draw middleground
  - draw enemies
  - draw player

## Hierarchy

Game
 State
  Systems
   Entities
    Components

## Systems

- movement
  - position
  - velocity
- rendering
  - renderable
  - position
- animation
  - renderable
- collision
  - position
- sound
  - sf sound

## Components

- position
  - x
  - y
- velocity
  - x
  - y
- renderable
  - sf::Sprite
- sound
  - sf::Sound

## Resource Manager

- map resource identifiers to file paths
- map resource identifiers to SFML resource types
  - sf::Texture
  - sf::Font
  - sf::Sound
- dynamically load resources when requested
- implements `get<typename T>(resource id string)`

## Game

- contains a stack of States
- implements a run method

## States

- include menus, load screens, pause screen, and the gameplay itself
- need to be able to pop themselves off the state stack
- implement input, update and render methods
- contain combinations of drawable entities

possible state changes:
- main menu -> options -> main menu
- main menu -> play -> main menu
- main menu -> play -> options -> play -> main menu
- main menu -> play -> pause -> play -> main menu

## Buttons

- contain sprites/animations
- can have focus
- has action method
- implements update and render methods

## Player

- contains:
  - animations
  - velocity
  - health
- methods:
  - change velocity
  - change health
- implements update and render methods

## Enemies

- contains:
  - animations
  - velocity
  - health
  - attacks/damage
- methods:
- implements update and render methods

## Lua integration

Master configuration:
- main window title
- default resolution

Resource configuration:
- table of resource ids and respective file paths

Levels:
- resources, entity locations
