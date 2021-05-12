# APO_SEM

This program is a semestral project for the computer architectures course on CTU FEI in Prague.
GitLab: https://gitlab.fel.cvut.cz/fraloily/apo_sem

Description
=============
This program is a simple video game that is very similar to Pong from 1972. In order to run this game, MicroZed APO hardware is required.

Rules
=============
The game is designed for two players playing the game simultaneously. The game area is divided into two halves. Each of these halves contains a white vertical pad that can be controlled by one of the players. The pad on the left is controlled by the red knob, the pad on the right is controlled by the blue knob. Players control the pads in order to hit a ball that is flying through the game area at constant speed and bounces off everything that it hits. If one of the players fails to hit the ball and the ball reaches the edge of the screen, the other player gets a point and the ball moves back to the center of the game area.

Manual
=============
Navigation:
    Navigate to the right: press blue knob.
    Navigate to the left: press right knob.
    Select option: press green knob.

Pause and exit:
    Pause the game: press green knob while the game is running.
    Emergency exit: press all 3 knobs at the same time.


Additional information
=============
runOnDesk.sh script sends files to a remote folder with scp command, then connects to mzAPO through ssh (key is needed), changes directory, compiles and runs binary file.
In order to use the script you need to change paths to directories, IP addresses and name of the binary file to execute.