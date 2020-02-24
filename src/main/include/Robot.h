#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <string>
#include "ctre/Phoenix.h"

#define TALON_COUNT 8
#define SONG_COUNT 11

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;
private:

  void LoadMusicSelection(int offset);


    /* The orchestra object that holds all the instruments */
    Orchestra *_orchestra;

    /* Talon FXs to play music through.  
    More complex music MIDIs will contain several tracks, requiring multiple instruments.  */
    TalonFX **_fxes;

    /* An array of songs that are available to be played, can you guess the song/artists? */
    std::string _songs[SONG_COUNT] = {
        "BohemianRhapsody.chrp"
        "CrabRave.chrp"
        "Frankenstien.chrp"
        "HighwaytoHell.chrp"
        "ImperialMarch.chrp"
        "Jaws.chrp"
        "Peaches.chrp"
        "Pirates.chrp"
        "Thunderstruck.chrp"
        "Tusk.chrp"
        "WeWillRockYou.chrp"
        //"Megalovania.chrp"
    };

    /* track which song is selected for play */
    int _songSelection = 0;

    /* overlapped actions */
    int _timeToPlayLoops = 0;

    /* joystick vars */
    frc::Joystick *_joy;
    int _lastPOV = 0;
};
