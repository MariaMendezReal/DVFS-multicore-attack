# Lockout_ransom

The folder **Voltage Module** contains the kernel module for modifying the voltage. It requires changing the name of regulator the adapt it to another SoC/Board and it can be user on Android or any other Unix devices as long as it supports Kernel Regulator API
We use *regulator_get()* or *regulator\_get_exclusive()* to request access to the regulator. Both functions get regulator name as parameter and return a reference toward the requested regulator.
*regulator_set_voltage()* is then used to modify the voltage.

The folder **Voltage C** contains a simple C program able to communicate with the kernel module through nodes.

Finally, **Malicous APP** is a Android APP prototype and show the way to load the malicious module after each load. It may be adapted to other devices that does not require a voltage module like Hikey960.
This App was made using Android studio. It need root access to be able to load the voltage module or access it. We also used *intent* to load/change voltage after each boot as show in *com.example.maliciousapp.RunOnStartup*
