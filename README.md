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
  <img src="https://github.com/user-attachments/assets/180a22a6-4891-4025-8321-ed03dce79e88">
</p>

> [!IMPORTANT]
> 1 leg of the BT136 triac is connected to the PHASE of the LED strip. The 2nd leg of the BT136 triac is connected to the PHASE of the AC mains. The 3rd leg of the BT136 triac is connected to the gate of the power3061 controller.

> [!CAUTION]
> DO NOT SWAP THE CONNECTION FROM THE 1ST LEG WITH THE 2ND LEG OF THE BT-136 TRIAC BECAUSE IT WILL NOT WORK!

## 3D model
<p align="center">
  <img src="https://github.com/user-attachments/assets/d2a1ea18-531a-4efb-bf9d-450dfcc717a9">
  <img src="https://github.com/user-attachments/assets/e8d78b4d-09ef-4ffb-ac50-9e90cfc52420">
</p>

## Final efect of the controller
A universal Kradex Z112A plastic housing with dimensions of 186x136x40mm was used to enclose the PCB
<p align="center">
  <img src="https://github.com/user-attachments/assets/991df6b9-d29d-41c6-be19-cae3f0de9689">
  <img src="https://github.com/user-attachments/assets/856a504b-72a2-47f8-a37a-7c82b0aec2d1">
  <img src="https://github.com/user-attachments/assets/5484ea67-715c-437e-9b45-e33c243d6e71">
</p>!
