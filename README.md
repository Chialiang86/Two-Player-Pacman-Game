# A Customized Pac-Man Game
![pac-man-demo-3](https://github.com/user-attachments/assets/ffabd87d-9d27-4718-99c9-c952d63cbe2c)
- For single user, the player can use up, down, left, and right arrow to control the hac-man
- For double users, the players can use up, down, left, and right arrow or w,a,s, and d key to control the hac-mans
  
![pac-man-demo-4](https://github.com/user-attachments/assets/74574902-49e0-4f5e-b9d0-8a7b2bc521bc)
- The map can also be modified by the user.

## Platform and Language
- Use Qt5 for game implementation
- Tested on Windows 10, Ubuntu 20.04, and MacOC

## Power Pellets
- When taking the huge pellets, the ghost can't kill the pac-man.

## Pac-man

- Pac-man may keep going straight forward and player can use four keys to change its direction.
- If Pac-man collide with the ghost, game over.

## Ghost

- There are four ghosts in the corner of the gameboard.
    - Red ghost: will shoot magic bullet to the hac-man.
    - Blue ghost: will slowly chase the hac-man.
    - Pink ghost: will randomly move on the map but the speed is SUPPER FAST!
    - Yellow ghost: will mimic the motions of the "knight" piece in chess game and move to the hac-man.
      
- Four ghosts have four different algorithm to chase pac-man.
- If the ghost collide with the pac-man, pac-man die and game over.


## Polymorphism
- Apply polymorphism technique on class `Pacman` and `Ghost` for implementation.
- Both of them have a method `move()` called by pointer of base class.
