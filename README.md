# TrackerGPSArduinoNano V1

 Tracker GPS/ mouchard (Version carte micro SD) pour  arduino nano AT328P
 ```
Version 1 :avec lecteur SD
Version 2 : avec Puce GSM
```

![Boitier 3D](preview3D_box.png?raw=true "Boitier 3D")

## Bien commencer

Ce programme a été codé sous l'arduino IDE utilisant des librarie open sources.
je prepare une vidéo youtube pour expliquer certain details du code, hardware mais aussi du boitier imprimer en 3D.
Voici un schema simple de fonctionnement:
•initialisation du CPU
•Allumage GPS
•Phase recuperation Postion GPS
•Ecriture données au format .GPX sur la carte SD
•Eteint GPS
•CPU en mode Sleep
•Attente de 10 minute avant reveil et  allumage GPS ,CPU et recuperation d'un nouveau signal.

Afin de ne pas vider la batterie en 2 heures , Des fonction de sauvegarde de battery on été ajouté comme le temps maximun de 15sec d'allumage du GPS ( cas blocqué sous un tunnel).
je vous invite a venire regardermin tuto en français sur ce projet...
et je prepare la Version 2 avec puce GSM.

### Requis Logiciel
* [Arduino IDE](https://www.arduino.cc) - arduino IDE
* [TinyGps++](https://github.com/mikalhart/TinyGPSPlus) - TinyGps++

### Requis Hardware
Arduino Nano (at328/AT328P) our autre arduino ...

GPS NEO 6(M/G/C)
Transitor NPN (ic = 100mA en saturé)

Resistance 1kΩ

Lecteur carte microSD

Batterie(1000maH recommandé)

Controlleur charge baterrie


### Schéma électronoque et cablage


```
Ca arrive
```


## Tests
en cas d'erreur ( access SD) la led Pin 13 clignotera rapidement et le programme stopera.



## Deployment

Add additional notes about how to deploy this on a live system


## Amelioration

* Gestion date des fichier GPX

## Consommation et baterrie

Batterie 1000mAh:

```
autonomie testé de 6 jours en environement idéal( récuperation signal GPS en 3 secondes)
```

## Contribution

Toutes contribution est la bienvenue sur ce projet.


## Auteur

* **Djamal Guellati** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

 list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

