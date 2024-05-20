## _An Engineering Competition to Design and Build The Most Accurate Noninvasive Glucometer_
### Table of Contents
1. [Overview](#overview)
2. [Prizes](#prizes)
3. [How To Enter](#how-to-enter)
4. [Requirements, Rules, Constraints](#requirements-rules-constraints)
5. [How Entries Will Be Evaluated](#how-entries-will-be-evaluated)
6. [Example Sensor](#example-sensor)
7. [Current Competitors](#current-competitors)

## Overview
This is a competition to design and build the most accurate noninvasive glucometer sensor. 

The motivation for the competition is to increase the information available to the general public on noninvasive sensors by evaluating the accuracy of different sensor designs and to provide all the information needed to recreate those designs freely.  This is in the hopes that in the near future there may be an affordable sensor which can reliably provide accurate readings, and reduce the pain, cost, and waste associated with typical glucometers.

This repository is setup to also act as an Arduino library.  The design rules are setup such that the sensor should interface like a Wing with an Adafruit Feather.  See https://learn.adafruit.com/adafruit-feather/overview for reference.

The information provided here has not been evaluated by the Food and Drug Administration.  The information provided here is not intended to diagnose, treat, cure, or prevent any disease.

## Prizes
To encourage some friendly competition, the following prizes are offered.  It should be noted though, that all competitors are contributing to the information available to the general public.  Knowing both what works well, and what does not, is of benefit to the public.
 - First Place $1000
 - Second Place $500
 - Third Place $250
 - Everyone, TBD, Stickers maybe?

## How To Enter
Make sure you are looking at the official repository at https://github.com/knowthebird/NoninvasiveGlucometer/. Updates to the compeition and results will be sent to the email address provided in the registration form.

  1. Fill out the [Registration Form](https://forms.gle/nVtzwGYVJsYVfvGZ8) no later than November 1, 2024. You can enter as an individual or as a team.
  2. Withing a few business days, you will receive an email notification that you have been entered into the contest. It will contain instructions for where to mail you sensor, source code, and documentation. (Will be East Coast United States).
  3. Design and build your sensor, following the requirements below.
  4. Mail your package per the instructions you received when you registered such that it arrives no later than December 1, 2024. Your sensor will be sent back to you after the competition is over.
  5. The winners and leaderboard will be announced by Jan 31, 2025.

## Requirements, Rules, Constraints
All of the following requirements must be met for the competition.

  1. Human Interface
     1. The Sensor must not harm the user.
     2. The Sensor must estimate the user's blood glucose level in milligrams per deciliter.
     3. The Sensor must attach to either a finger, wrist, or ear lobe.
     4. The Sensor must not puncture the skin.
  2. SWaP-C
     1. The Sensor must fit in a USPS Small Flat Rate Box (8 5/8″ x 5 3/8″ x 1 5/8").
     2. The Sensor must weigh less than 2 lbs.
     3. The Sensor must consume less than 10 watts power.
     4. The Sensor components must cost less than $200 USD in total.
  3. Electrical Interface
     1. The Sensor must use the Adafruit Feather footprint, pinout, and female headers to allow connection to an Adafruit Feather M0 Adalogger microcontroller.
     2. When connected to the microcontroller, the Sensor must not prevent use of Serial Communications or SD card logging.
     3. When connected to the microcontroller, the Sensor must not prevent the microcontroller from using an Adafruit 128x64 OLED FeatherWing display or buttons.
     4. The Sensor must not require physical modifications to the Adafruit Feather M0 Adalogger microcontroller or Adafruit 128x64 OLED FeatherWing.
     5. The Sensor must not damage the Adafruit Feather M0 Adalogger microcontroller or Adafruit 128x64 OLED FeatherWing.
  4. Software Interface
     1. The software repository must use this repository's structure and continue to function as an Arduino library.
     2. The software must fit and run on an Adafruit Feather M0 Adalogger microcontroller when compiled in the example TestHarness (Total compiled size less than 262144 bytes).
     3. The software interface must implement the pure virtual methods provided in the GlucometerSensor class of this repository [Initialize, PositionSensor(GlucometerDisplay display), and GetConcentration_mg_dl]. Overloads may be implemented, but are not required, and will not be used for the competition.
     4. The Initialize() method must contain all logic to initialize and calibrate the sensor, and must return 0 in less than 60 seconds of being called to confirm successful execution.
     5. The PositionSensor(GlucometerDisplay display) method must contain all logic to ensure the sensor is properly positioned on the user, and must complete in less than 60 seconds of being called.
     6. The GetConcentration_mg_dl() method must contain all logic to measure and return the user's blood glucose level in milligrams per deciliter, and must complete in less than 60 seconds of being called.
 5. Documentation
     1. All documentation must be provided under the MIT License. By entering the competition, you agree all documentation submitted can be shared publicly under the MIT License with the final results.
     2. All of the following documentation must be provided:
        1. A parts list, containing the Supplier, Part Number, Quantity Used, and Cost per Component for each component used.
        2. Dimensional drawings or STL files for any custom made mechanical components.
        3. A wiring schematic for the sensor.
        4. All source code used.
    3. Your documentation does not need to be shared publicly before the final results and winners are announced. If you share it, you agree to allow competitors to use it. It is your responsibility to protect your documentation before then if that is not desired.

## How Entries Will Be Evaluated
All entries will be evaluated using the same methods.  The method used will not be shared prior to the results being announced.  Any additional information will be added to this section in the official repository at https://github.com/knowthebird/NoninvasiveGlucometer/

## Example Sensor
I will be working on an example sensor while the competition is running and will update this repository as I make updates.  The example sensor will not be eligible to win any of the prizes.  You are not competing with the example.  It is just provided for reference on how things can be implemented and will show what I am working on.

## Current Competitors
| Alias or Team Name | Individual or Team | School, Business, or Organization |
| :--------- | :-------- | :------- |
| None yet   | None yet  | None yet |


