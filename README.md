## Design and Build An Accurate Noninvasive Glucometer

### Table of Contents
1. [Overview](#overview)
2. [Example Sensors  (Glucosans)](#example-sensors-glucosans)
3. [Lessons Learned](#current-competitors)
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
| Correlations | None / Weak  | TODO |
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

## Lessons Learned

<b>Nov 15, 2024:</b> Initial tests with Glucosan 1 have showed weak to no correlation with blood glucose levels.  This is after gaining a wider range of data (see UserTwoLogData.csv) to verify outputs.  This may be due a few causes, including:

* Flexibility in the finger clamp was intended to allow a better seal on the finger from ambient light.  Distance of light source to sensor significantly affects readings.  Very possible minute changes in finger position are overshadowing any blood glucose levels which could be detected. For example, reference 2 sees a ~0.25 volt difference over ~800 mg/dl shift.  Given it is a different setup, but it shows the range of values they are looking at. With Glucosan 1, in one log we can see 0.3 volt pk to pk heartbeat with a .1 V drift in the readings with a steady finger. Slightly moving the finger forward or backward in the clamp can almost immediatly exceed a .25V difference.  Possible solutions are puting the emitter and sensor in fixed positions where the clamp is not flexivble, or including IMUs on the sensor and emitter such that the distance between the two can be calculated.
* Similarly, Nothing controlling movement, shaking, or vibrations when taking readings, or tracking them to filter against. A solution could be to use IMUs could monitor movement, or alert the user the device/finger is not stable enough to take a measurement. 
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



