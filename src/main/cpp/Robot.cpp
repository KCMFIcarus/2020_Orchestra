#include "Robot.h"

void Robot::LoadMusicSelection(int offset)
{
    /* increment song selection */
    _songSelection += offset;
    /* wrap song index in case it exceeds boundary */
    if (_songSelection >= SONG_COUNT) {
        _songSelection = 0;
    }
    if (_songSelection < 0) {
        _songSelection = SONG_COUNT - 1;
    }
    /* load the chirp file */
    _orchestra->LoadMusic(_songs[_songSelection]); 

    /* print to console */
    printf("Song selected is: %s.  Press left/right on d-pad to change.\n", _songs[_songSelection].c_str());
    
    /* schedule a play request, after a delay.  
        This gives the Orchestra service time to parse chirp file.
        If play() is called immedietely after, you may get an invalid action error code. */
    _timeToPlayLoops = 10;
}

void Robot::RobotInit() {
    /* Create the orchestra with the TalonFX instruments */
    _orchestra = new Orchestra();

    _fxes = new TalonFX * [TALON_COUNT];
    /* Initialize the TalonFX's to be used */
    for (int i = 0; i < TALON_COUNT; ++i) {
        _fxes[i] = new TalonFX(i+21);
        _orchestra->AddInstrument(*_fxes[i]);
    }
    _joy = new frc::Joystick(0);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
    /* load whatever file is selected */
    LoadMusicSelection(0);
}
void Robot::TeleopPeriodic() {
    /* poll gamepad */
    int currentPOV = _joy->GetPOV();

    /* if song selection changed, auto-play it */
    if (_timeToPlayLoops > 0) {
        --_timeToPlayLoops;
        if (_timeToPlayLoops == 0) {
            /* scheduled play request */
            printf("Auto-playing song.\n");
            _orchestra->Play();
        }
    }


    /* has POV/D-pad changed? */
    if (_lastPOV != currentPOV) {
        _lastPOV = currentPOV;

        switch (currentPOV) {
            case 90:
                /* increment song selection */
                LoadMusicSelection(+1);
                break;
            case 270:
                /* decrement song selection */
                LoadMusicSelection(-1);
                break;
            case 0:
                if (_orchestra->IsPlaying()) {
                    _orchestra->Pause();
                    printf("Song stopped.\n");
                }  else {
                    _orchestra->Play();
                    printf("Playing song...\n");
                }
                break;
        }
    }
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
