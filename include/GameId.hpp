#pragma once

namespace GameID {

// --- STATE SYSTEM ---
enum class State { None, Menu, InsideCar, Driving, Pause, GameOver };

// --- INPUTS ---
enum class Action {
  SteerLeft,
  SteerRight,
  Accelerate,
  Brake,
  Confirm, // UI Click/Enter
  Back,    // UI Escape
  Pause
};

// --- GAMEPLAY MODIFIERS (Merged) ---
// Represents both the Malus Effect and the Mask required to stop it.
enum class Malus {
  None,
  Alcool,  // Drunk Effect / Anti-Alcohol Mask
  Stinky,  // Smelly Passenger / Gas Mask
  Headset, // Muffled Sound / Headphones?
  Coke,    // Jitter Speed / Chill Glasses?
  Fat      // Heavy Physics / ?
};

// --- ASSETS ---
enum class Texture {
  // UI
  /*TitleScreen,
  ButtonNormal,
  ButtonSelected,
  Dashboard,*/

  // Game Entities
  PlayerCar,
  TrafficCivilian,
  //TrafficPolice,
  //Road,
  Background,

  // Mask Icons (Aligned with GameID::Malus for easy loading)
  Mask_Alcool,
  Mask_Stinky, //puer
  Mask_Headset,
  //Mask_Coke,
  Mask_Fat
};

enum class Font {
  Main,
  Digital,
  Cyber
};

enum class Sound {
  //PhoneRing,
  //PhoneVoice_Drunk,
  //PhoneVoice_Angry,
  //CarEngine,
  //CarCrash,
  //UI_Click
  Minuteur, // de 10 seconde
  Test,
};

} // namespace GameID
