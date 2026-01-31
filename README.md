Project: Masked Delivery (Game Jam)
🎮 Game Overview & Mechanics
This game is a Session-Based Hybrid mixing a Static Puzzle phase with an Action Runner phase. The core theme is "Masks," used as protection against gameplay modifiers (Maluses).

The Loop
Inside Car (Office Phase):

The Hook: The phone rings. A client calls for a delivery or a passenger wants a ride.

The Clue: Based on the voice (e.g., slurping = drunk) or the number, you must identify the threat.

The Choice: Select the correct Mask from the dashboard (e.g., Anti-Alcohol Mask).

Transition: You start the engine.

Driving (Runner Phase):

The Action: Vertical scroller. Avoid traffic and obstacles.

The Malus System:

If you chose the Wrong Mask, you get a Malus (e.g., Drunk Mode: controls are inverted).

If you pick up a Passenger, they add a Malus (e.g., Smelly: screen covered in green fog).

Cumulative: Maluses stack up. If you survive a run, you carry the damage/score to the next day.

End Condition:

Survival (Score accumulated).

Crash (Game Over).

📂 Architecture: The include/ Directory
The architecture relies on a State Machine for flow control and a Shared Context for data persistence.

1. Core Infrastructure
Files that keep the engine running.

Game.hpp

Role: The root class. It initializes the Window, holds the StateStack, and runs the main loop (processInput -> update -> draw).

Key Method: run() - The heartbeat of the application.

GameId.hpp

Role: Contains all globally used Identifiers (Enums).

Contents: GameID::State (Menu, Driving), GameID::Texture (Player, Road), GameID::Action (SteerLeft, Pause).

SharedContext.hpp

Role: The "Brain" of the game. It defines the Context struct passed to every state.

Key Struct: SessionData - This acts as our "save file" in RAM. It stores activeMaluses, currentScore, and currentMask so data survives the switch from Office to Driving.

InputManager.hpp

Role: The Translator. It converts raw hardware signals (Key 'A', Joystick Button 0) into logical Game Actions (Action::SteerLeft).

Why: Allows us to rebind keys easily without breaking game code.

2. State System (Game Flow)
Files that manage the distinct screens of the game.

StateStack.hpp

Role: The Manager. It holds a list of active states. It handles the logic of switching screens (e.g., "Pop Menu, Push Game").

State.hpp

Role: The Abstract Base Class (Interface). All screens must inherit from this.

Key Interface: handleEvent() (Menus), update(dt) (Logic), draw().

InsideCarSystem.hpp

Role: Contains classes specific to the Office Phase.

Components:

PhoneSystem: Logic for the ringing phone, randomizing callers, and voice hints.

MaskSelector: UI logic for clicking masks on the dashboard.

3. Gameplay & Physics (Driving Phase)
Files dedicated to the "Runner" portion of the game.

World.hpp

Role: The Manager for the driving scene. It owns the Player, Traffic, and Road. It checks for collisions and updates the scrolling speed.

Entities.hpp

Role: The objects in the world.

Classes:

SceneNode: Base class for anything visible (supports parent/child hierarchy).

Entity: Adds velocity/movement logic.

PlayerCar: The hero object (reads input).

TrafficCar: Obstacles (simple AI).

MalusSystem.hpp

Role: The "Twist" Logic.

Classes:

MalusManager: Holds the list of active punishments.

Malus (Base Class): Defines how a punishment works (modifyInput, applyScreenEffect).

Example: DrunkMalus overrides modifyInput to flip Left/Right.

4. Utilities
Helper files.

GUI.hpp

Role: Provides a standard Button class. Used in the Main Menu and the Mask Selector. Handles mouse hover/click states internally.

🛠 How to Add Content (Quick Guide)
1. How to add a new Malus (e.g., "Slippery Road")
Go to GameId.hpp and add Slippery to GameID::Malus.

Go to MalusSystem.hpp (or a specific cpp file).

Create a class SlipperyMalus : public Malus.

Override getSpeedMultiplier() or modifyInput() to make steering harder.

Register it in MalusManager::loadFromSession.

2. How to add a new Asset (Texture/Sound)
Go to GameId.hpp and add the ID (e.g., Texture::Radio).

In Game.cpp (constructor), call mTextures.load(Texture::Radio, "assets/radio.png");.

Access it anywhere via context.textures->get(Texture::Radio).

3. How to create a new Screen (State)
Add ID to GameId.hpp (State::GameOver).

Create GameOverState.hpp inheriting from State.

Register it in Game::registerStates() using mStateStack.registerState<GameOverState>(State::GameOver).
