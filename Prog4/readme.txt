Welcome to Qbert version off Tijl Gommers

The game works mostly with oop but every object his functionallity is mostly by components.

Music can be muted with th M button.
Levels can be skipped with the F1 button.
When skipping through the 3 lvls off this game. you enter the victory screen.
if you have an higher score then one off the 5 storred scores (on txt file).
You can enter your name and store your new score.

During the game you can pause the game with ENTER button.
while paused, you can chose to exit and chose an other gamemode or continue the game.

Player controls are explained on the screen after chosing your gamemode.

The engine has multiple scenes, which are handeld by a menuState machine.
When you switch to a new gamemode theough the menus (or halfway game)
this state machine will call an ApplyGameMode function to all the objects that needs to be reset.
 
CharacterInput is by ActorCommand which will go through the statemachine off the character. Which ensures a correct input for the correct state.
This input will be dissabled when not in GameMenu.This is done by setting the actor to nullptr and back to his actor when activating (storred in an other variable).



