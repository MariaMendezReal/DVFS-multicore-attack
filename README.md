# DVFS-based attack on ARM big-Little multicore architecture

This work was presented at DATE conference in 2020; *Towards malicious exploitation of energy management mechanisms*.
These codes were developped to be used on Hikey960. 

**Voltage Module** folder contains a malicious kernel module for the pushing beyond the limits of the voltage and frequency couples. This attacks code requires changing the name of the regulator in order to adapt it to another SoC/Board. It can be used on Android or on any other Unix device as long as it supports the Kernel Regulator API.
*regulator_get()* or *regulator\_get_exclusive()* are used in order to request access to the regulator. Both functions get the regulator name as a parameter and return a reference towards the requested regulator.
*regulator_set_voltage()* is then used to modify the voltage level.

**Voltage C** folder contains a simple C program able to communicate with the kernel module through nodes.

Finally, **Malicous APP** is an Android APP prototype showing how to load the malicious module after each boot of the system. It may need to be adapted to be used on further devices that do not require a voltage module.
This App was developped using Android studio. It requires priviledge access to be able to load the malicious kernem voltage module, or access it. *intent* function was used to load/change the voltage level after each system boot as show in *com.example.maliciousapp.RunOnStartup*
