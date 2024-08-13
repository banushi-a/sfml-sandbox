# sfml-sandbox

Sandbox Style SFML Application

<img width="1000" alt="example sandbox" src="https://github.com/banushi-a/sfml-sandbox/assets/89368127/1829d230-bb7a-48b5-a814-97fe9e992837">

## Running the Program

Either double click `prog` or navigate to the folder where `prog` is using terminal and run `./prog`

Left click and hold to place materials. Using the keyboard, press:

- (b) to switch to bricks
- (s) to switch to sand
- (w) to switch to water
- (g) to switch to gasoline
- (f) to switch to fire
- (t) to switch to steam
- (r) to remove everything from the screen

You can add materials in an n x n area for n in { 1, 3, 5, 7, 9 } by pressing the corresponding number. By default materials spawn in a 3x3 area.

## Building the Program

1. Run brew info sfml

My output is

```
==> sfml: stable 2.6.1 (bottled), HEAD
Multi-media library with bindings for multiple languages
https://www.sfml-dev.org/
/usr/local/Cellar/sfml/2.6.1 (812 files, 12.6MB) *
```

2. Locate the path, mine is /usr/local/Cellar/sfml/2.6.1

3. Run the following command, replacing path with wherever your sfml is located

`g++ -std=c++17 ./src/*.cpp -I ./include/ -I[path]/include -o prog -L[path]/lib -lsfml-graphics -lsfml-window -lsfml-system`

5. Run ./prog!

## Change Log

### Latest Update

- 08/11/2024 Random number generation now follows the singleton design pattern in its own class, yay less overhead!

### Old Updates

- 08/10/2024 Reworked File Structure! Headers have been moved to ./include and source into.... well ./src

- 08/09/2024 It's been a minute! Fire now interacts with gas

- 12/17/2023 The spawning has been reworked, again. You now can spawn in nxn for n in { 1, 3, 5, 7, 9 }. With larger spawn areas, we encounter performance issues. I would like to investigate routes we can take to optimize the computations.

- 12/17/2023 The spawning has been reworked. It now works by checking a 3x3 area surrounding the cursor and using random numbers to determine when to spawn materials. Pressing f lets the user spawn fire. The goal is to make this ignite with gas in the future.

- 12/16/2023 I have some basic fluid simulation working. The bricks now sink to the bottom of water. Future TODO is to abstract fluid type so that bricks sink to the bottom of any fluid.

- 12/07/2023 I want to refine the water physics. Maybe we can use some graph algorithm such as DFS or BFS. I would also like to work on adding density to materials. For example, dense materials such as bricks and sand sink below water. Maybe we can explore this / implement based on the ordering of the enum.

- 12/06/2023 I am working to add different materials such as Sand, Water, Bricks, and Air. My goal at the moment is to continue to ensure that the materials interact with eachother properly.

- 12/05/2023 I am currently working on setting up the project. Since this is my first time working with SFML, I want to spend time familiarizing myself with the library.
  Next steps include organizing the game loop, abstracting into different files, and adding support for different types of materials.
