# pd2-pacman

## Score
- GUI 5%
- Dashboard 5%
- Dots 5%
- Power Pellets 5%
- Pac-man 10%
- Ghost 10%
- Polymorphism 10%
- Demo 50%
- (Bonus up to 20%)

## Power Pellets

- If the ghost collide with the pac-man and pac-man has eaten power pellets
    - Pac-man eat the ghost and get the point
    - ghost die and bring back to life in a few seconds

## Pac-man

- Pac-man may keep going straight forward and player can use four keys to change its direction
- If Pac-man collide with the ghost, game over
    - You don't need to make pac-man life, it only have one life

## Ghost

- There are four ghosts in the corner of the gameboard
- Four ghosts should have four different algorithm to chase pac-man
    - you can take [this](https://en.wikipedia.org/wiki/Pac-Man#Enemy_behavior) as reference
- If the ghost collide with the pac-man, pac-man die and game over


## Polymorphism
- You should use polymorphism technique on class `Pacman` and `Ghost`.
- Both of them should implement method `move()`, and be called by pointer of base class.
