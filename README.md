# DYI-Launchpad
Acest proiect consta in realizarea unui Launchpad DIY care se poate conecta direct prin USB la un software DAW fara a fi nevoie de un alt software intermediar.
## Componente folosite:
* Adafruit Itsy Bitsy 32u4
* Adafruit MPR121 ( modul cu 12 intrari capacitive )
* Piesa metalica x12 ( ce se comporta ca un buton capacitiv )
* Potentiometru glisant x2
* Potentiometru rotativ x4
* Carcasa imprimata 3D

Pentru realizarea interfetei MIDI s-a folosit libraria "MIDIUSB.h" valabila pentru Arduino ce transmite direct prin USB catre DAW informatii MIDI.
Cele 12 piese metalice sunt conectate la cei 12 pini ai modulului MPR121 prin cate un fir, astfel comportandu-se ca niste butoane capacitive, 


Carcasa a fost proiectata in programul Fusion 360:
![](images/screenshot1.png)   

Dupa imprimarea 3D a carcasei, piesele au fost lipite cu lipici fierbinte si cablajul fixat cu suruburi.
![](images/screenshot2.png)
