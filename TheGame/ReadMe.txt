I've made a simple sidescrolling asteroid avoidance game. 

You are a spaceship who can move up and down. Asteroids keep appearing from the right of the screen. Avoid them for as long as you can! If you get hit you die. 

The player can wrap around top and bottom.

Controls: 
W: add upward impulse force
S: Add downward impulse force


Things that I did:
1) Separated Game and Engine code 
2) Simplified main loop to only do game and engine updates
3) Wrote a rendering system to handle all GLib stuff (I didn't otherwise modify any of your GLib library)
4) Neatly handled shutdown