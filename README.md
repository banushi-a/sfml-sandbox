# sfml-sandbox
Sandbox Style SFML Application

<img width="1000" alt="example_sandbox" src="https://github.com/banushi-a/sfml-sandbox/assets/89368127/daddf05a-6f9e-4bb4-8002-6ff070910f22">

## Running the Program
Either double click `prog` or navigate to the folder where `prog` is using terminal and run `./prog`

Left click and hold to place materials. Using the keyboard, press:
- (b) to switch to bricks
- (s) to switch to sand
- (w) to switch to water
- (r) to remove everything from the screen

## Latest Update

- 12/07/2023 I want to refine the water physics. Maybe we can use some graph algorithm such as DFS or BFS. I would also like to work on adding density to materials. For example, dense materials such as bricks and sand sink below water. Maybe we can explore this / implement based on the ordering of the enum.

## Old Updates

- 12/06/2023 I am working to add different materials such as Sand, Water, Bricks, and Air. My goal at the moment is to continue to ensure that the materials interact with eachother properly. 

- 12/05/2023 I am currently working on setting up the project. Since this is my first time working with SFML, I want to spend time familiarizing myself with the library.
Next steps include organizing the game loop, abstracting into different files, and adding support for different types of materials.
