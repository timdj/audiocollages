DAS BOOT // eSPEAK-NG INSTALLATIE
==================================

Om de eSPEAK knop met volledige FX te gebruiken:

1. Download deze 3 bestanden van jsdelivr CDN:
   https://cdn.jsdelivr.net/espeakng.js/1.49.0/espeakng.min.js
   https://cdn.jsdelivr.net/espeakng.js/1.49.0/espeakng.worker.js
   https://cdn.jsdelivr.net/espeakng.js/1.49.0/espeakng.worker.data

2. Upload alle 4 bestanden naar dezelfde map op je server:
   - das-boot-sam.html
   - espeakng.min.js
   - espeakng.worker.js
   - espeakng.worker.data

3. Voeg in das-boot-sam.html voor </head> toe:
   <script src="espeakng.min.js"></script>

4. Open das-boot-sam.html via je server (niet als file://)

5. Klik op de oranje eSPEAK-NG knop
   → Audio gaat door ALLE 9 SAM effecten!
   → Loop, opname, alles werkt

WEB SPEECH (blauw) werkt altijd, ook zonder server.
SAM (groen) werkt altijd als single file.
