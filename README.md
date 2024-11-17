## Design and Build An Accurate Noninvasive Glucometer

### Table of Contents
1. [Overview](#overview)
2. [Example Sensors  (Glucosans)](#example-sensors-glucosans)
3. [Testing Notes](#testing-notes)
4. [Resources and References](#resources-and-references)

## Overview
This was originally to host a competition to design and build the most accurate noninvasive glucometer sensor.  Despite some interest, there were no entries.  Instead, now it currently just hosts my designs.  

The $1750 set aside for prizes will be kept available as a fund for anyone interested in developing a noninvasive glucometer sensor. If you have an idea for a design and want to chat about it or request some support, or if you are interested in refining these designs, reach out to noninvasiveglucometer@gmail.com

The motivation for the competition and designs is to increase the information available to the general public on noninvasive sensors by evaluating the accuracy of different sensor designs and to provide all the information needed to recreate those designs freely.  This is in the hopes that in the near future there may be an affordable sensor which can reliably provide accurate readings, and reduce the pain, cost, and waste associated with typical glucometers.
 
The information provided here has not been evaluated by the Food and Drug Administration.  The information provided here is not intended to diagnose, treat, cure, or prevent any disease.

Please feel free to reach out to noninvasiveglucometer@gmail.com with any questions, suggestions, comments, or concerns.

## Example Sensors (Glucosans)
This repository contains example "Glucosans" for reference. These are various designs to approach the problem, and the succeses and failures of them will be shared. 

**Glucosan**
 * **G**lucometer
 * **L**ightweight
 * **U**niversal
 * **C**ost-effective
 * **O**pen **S**ource
 * **A**ccurate
 * **N**oninvasive

| Overview | Glucosan 1 | Glucosan 2 |
| :--------- | :-------- | :------- |
| Image | <img src="mechanical/Glucosan1/assembled.jpg" width="300" />| Coming Soon! |
| Method | IR Spectrometry | IR Spectrometry |
| Design | Done | In Progress |
| Build | Done | TODO |
| Log Data | 2 Persons, ~150 logs, 76-447mg/dl | TODO |
| Analysis Algorithims | External, Post Processing, Linear Regression | TODO |
| Correlations | Weak to None  | TODO |
| Emitters   | 1 x 617nm, 1 x 940nm | 1 x 670nm, 1 x 850nm, 1 x 950nm, 1 x 1300nm, 1 x 1550nm |
| Reflectance Detectors  | Phototransistors 1 x 630nm, 1 x 940nm (Si)  | None |
| Transmittance Detectors   | Phototransistors 1 x 630nm, 1 x 940nm (Si) | Photodiodes, 1 x 950nm (Si), 1 x 1650nm (InGaAs) |
| ADC | bypass caps, 12 bit resolution | analog front end IC, 14 bit resolution |
| Core Platform   | Adafruit Feather M0 Adalogger | Adafruit Feather RP2040 Adalogger |
| Display   | 128x64 OLED  | 128x64 OLED |
| SD Card   | CSV or Binary Logging | CSV or Binary Logging |
| Wireless   | None | None |
| IMU   | None  | 2 x Accel, 2 x Gyro |
| Temperature   | None  | 1 x Temp |
| Size   | TODO  | TODO |
| Weight   | TODO  | TODO |
| Power   | TODO  | TODO |
| Cost   | $48.33  | $188.31 |

## Testing Notes

<b>Nov 17, 2024:</b> Additional logs were taken with Glucosan 1 over a wide range of blood glucose levels. Looking closer at the log data showed what appeared to be corrupt signal readings, with a single sensor log showing multiple samples of the same photoplethysmogram (PPG) waveform slightly shifted. Because they were clearly shifted, but otherwise near identical signals representing the same PPG data, it does not look like an aliasing artifact from outside noise.  This can be seen looking at the readings from all sensors (regardless of LED state).  In some logs the corruption appears to "toggle" off and on, where the separation between duplicate signals widens.  My initial suspician is there is a hardware failure causing coupling between the sensors. It was not identified until reviewing a large set of samples. This should be kept in mind when referring to data from logs 85 to 174.  See log data folder for more details.

Initial tests with Glucosan 1 have showed weak to no correlation with blood glucose levels.  This is after gaining a wider range of data (see UserTwoLogData.csv) to verify outputs.  This may be due a few causes, including:
* Flexibility in the finger clamp was intended to allow a better seal on the finger from ambient light.  Distance of light source to sensor significantly affects readings.  Very possible changes in finger (emitter/sensor) positions are overshadowing any blood glucose levels changes detected by the sensor. Slightly moving the finger forward or backward in the clamp can almost immediatly exceed a .25V difference.  Possible solutions are puting the emitter and sensor in fixed positions where the clamp is not flexible, or including IMUs on the sensor and emitter such that the distance between the two can be calculated.
* Similarly, Nothing controlling movement, shaking, or vibrations when taking readings, or tracking them to filter against. A solution could be to use IMUs could monitor movement, or alert the user the device/finger is not stable enough to take a valid measurement. 
* Lack of environmental controls.  Glucosan 1 is portable and used in a variety of environments, and could be influenced by factors like various lighting. Possible solution is to always use in the same position for tests.

<b>July, 2024:</b> So far with Glucosan 1, only weak correlations have been observed.  This has relatively little significance at this point though, because it has only logged a very small amount of data with a relatively small range of blood glucose levels.  Getting a large set of samples, with a range in blood glucose levels, to both train and test models, is a challenge for any new sensor developemnt.  Without a range of data, initial results, such as MARD or RMSE, can be very misleading.
   * <b>YoutTube Video - Noninvasive Glucometer, Part 1, Initial Design Progress </b>
[![YoutTube Video, Noninvasive Glucometer, Part 1, Initial Design Progress](https://img.youtube.com/vi/Cop63ntB-sQ/0.jpg)](https://www.youtube.com/watch?v=Cop63ntB-sQ)


## Resources and References

1. Hina A, Saadeh W. Noninvasive Blood Glucose Monitoring Systems Using Near-Infrared Technology-A Review. Sensors (Basel). 2022 Jun 27;22(13):4855. doi: 10.3390/s22134855. PMID: 35808352; PMCID: PMC9268854.
   * https://www.mdpi.com/1424-8220/22/13/4855
2. Javid B, Fotouhi-Ghazvini F, Zakeri FS. Noninvasive Optical Diagnostic Techniques for Mobile Blood Glucose and Bilirubin Monitoring. J Med Signals Sens. 2018 Jul-Sep;8(3):125-139. doi: 10.4103/jmss.JMSS_8_18. PMID: 30181961; PMCID: PMC6116315.
   * https://pmc.ncbi.nlm.nih.gov/articles/PMC6116315/
3. Meter, G. (2015, August 27). Open Source Non-Invasive Glucose Meter - Expensive, Wasteful, and Annoying. YouTube
   * https://youtu.be/2np7Va2ASF0?si=skVRlG87lIETs9TL
4. Bhuyan, Muhibul. (2020). Design and Implementation of an NIR-Technique Based Non-Invasive Glucometer using Microcontroller. 20. 
   * https://tinyurl.com/j6b6d8wd
5. Beckers, I. (n.d.). Measuring glucose concentration nir absorption spectroscopy. Oxford Instruments. 
   * https://andor.oxinst.com/learning/view/article/spectral-response-of-glucose 
6. Naresh M, Nagaraju VS, Kollem S, Kumar J, Peddakrishna S. Non-invasive glucose prediction and classification using NIR technology with machine learning. Heliyon. 2024 Mar 28;10(7):e28720. doi: 10.1016/j.heliyon.2024.e28720. PMID: 38601525; PMCID: PMC11004754.
   * https://www.sciencedirect.com/science/article/pii/S2405844024047510


