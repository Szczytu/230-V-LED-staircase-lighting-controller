# 230-V-LED-staircase-lighting-controller
Controller for a large staircase consisting of 3 parts, total 26 stairs on 230 V LED strips. The controller has a built-in twilight sensor, the sensitivity of which can be adjusted using a potentiometer.
The construction of the controller was due to an unusual staircase and the desire not to use a separate power supply for 12-24V LEDs 
# Schematic and project controller of 230V LED
The project schematic, sample 3D model and gerber file is in the folder "PCB_LED_STAIRS"
The project was made in KiCad 8.0.
## Schematic
<p align="center">
  <img src="https://github.com/user-attachments/assets/b3d995f3-3b78-4d07-9395-5294634fcef2">
</p>

## Simplified schematic
<p align="center">
  <img src="https://github.com/user-attachments/assets/f8bdff5c-1816-40cd-b986-1e4a3083f6c1">
</p>

> [!IMPORTANT]
> 1 leg of the BT136 triac is connected to the PHASE of the LED strip. The 2nd leg of the BT136 triac is connected to the PHASE of the AC mains. The 3rd leg of the BT136 triac is connected to the gate of the power3061 controller.

> [!CAUTION]
> DO NOT SWAP THE CONNECTION OF THE 1ST LEG WITH THE 2ND LEG BECAUSE IT WILL NOT WORK!

## 3D model
<p align="center">
  <img src="https://github.com/user-attachments/assets/d2a1ea18-531a-4efb-bf9d-450dfcc717a9">
  <img src="https://github.com/user-attachments/assets/e8d78b4d-09ef-4ffb-ac50-9e90cfc52420">
</p>
