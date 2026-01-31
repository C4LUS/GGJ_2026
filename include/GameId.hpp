#pragma once

namespace GameID {
// State Identifiers
enum class State { None, Menu, InsideCar, Driving, Pause, GameOver };

// Action Identifiers (Inputs)
enum class Action {
  SteerLeft,
  SteerRight,
  Accelerate,
  Brake,
  Confirm, // UI Click/Enter
  Back,    // UI Escape
  Pause
};

// Asset Identifiers
enum class Texture {
  // UI
  TitleScreen,
  ButtonNormal,
  ButtonSelected,
  Dashboard,
  // Game
  PlayerCar,
  TrafficCivilian,
  TrafficPolice,
  Road,
  Background,
  // Masks
  MaskGas,
  MaskSunglasses,
  MaskAntiDrunk
};

enum class Font {
  Main,
  Digital // dashboard clock/speedometer
};

enum class Malus {
  Alcool,
  Stinky,
  Headset,
  Coke,
  Fat,
  None,
};

enum class Sound {
  PhoneRing,
  PhoneVoice_Drunk,
  PhoneVoice_Angry,
  CarEngine,
  CarCrash,
  UI_Click
};
} // namespace GameID
