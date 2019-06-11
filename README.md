# TrackerGPSArduinoNano V1
Je débute dans la création d'objets connectés et j'aimerai partager ma création avec tout les bugs qu'il comporte :) !

Toutes contributions , commentaires sont les bienvenus !

 
Tracker GPS/ mouchard (Version carte micro SD) pour  arduino nano AT328P
 ```
Version 1 :avec lecteur SD
Version 2 : avec Puce GSM
```

⚠️ la protection de données personnelles vous impose de ne pas recupérer et reutiliser les données d'autrui sans autorisation ⚠️

![Boitier 3D](preview3D_box.png?raw=true "Boitier 3D")

## Bien commencer

Ce programme a été codé sous l'arduino IDE utilisant des libraries open sources.
je prepare une vidéo youtube pour expliquer certain details du code, hardware mais aussi du boitier imprimer en 3D.
Voici un schéma simple de fonctionnement:


* 1 initialisation du CPU
* 2 Allumage GPS
* 3 Phase récuperation position GPS
* 4 Ecriture données au format .GPX sur la carte SD
* 5 Eteint GPS
* 6 CPU en mode Sleep
* 8 Reveil et boucle -> 1

Afin de ne pas vider la batterie en 2 heures , des fonctions de sauvegardes de battery ont été ajoutées comme le temps maximun de 15 sec d'allumage du GPS ( ex: cas bloqué sous un tunnel, le gps ne trouvera jamais de position...).


je vous invite a venir regarder mon tuto en français sur ce projet...
et je prépare la version 2 avec puce GSM.

### Requis Logiciel
* [Arduino IDE](https://www.arduino.cc) - arduino IDE
* [TinyGps++](https://github.com/mikalhart/TinyGPSPlus) - TinyGps++

### Requis Hardware: 9,40 € sur aliexpress !
Arduino Nano (at328/AT328P)->  lien : http://bit.ly/2wLw6Gq

GPS NEO 6(M/G/C) -> lien: http://bit.ly/2Ix3Mx3

Transitor NPN (ic max = 100mA) -> pack transistor :  https://www.banggood.com/custlink/3mmGP9TyV7

Resistance 1kΩ -> pack resisstance https://www.banggood.com/custlink/33KK5Zfhtn

Lecteur carte microSD -> lien: http://bit.ly/2R2ewYd

Batterie(1000maH recommandé) ->  http://bit.ly/31puy2X

Controlleur charge batterie -> http://bit.ly/2WxujnU


### Schéma électronique et cablages


```
Ca arrive
```


## Tests


en cas d'erreur ( access SD) la led Pin 13 clignotera rapidement et le programme stopera.


## Amelioration taille, autonomie...

* Gestion date des fichier GPX
* Version 2 puce GSM
* Arduino en mode standalone ( sans port serie, regulateur...) 
* Impression PCB et réduction de la taille du boitier 

## Consommation et batterie

Mode actif: 
```
 Arduino : 15mAh 
 Gps: 65 mAh
 carte sd: 0.3 mA
```


Mode Sleep: 
```
 Arduino : 3mAh 
 Gps: 0 mAh
 lecteur micro sd: 0.3 mA(pas de mode sleep dans cette version)
```

Batterie 1000mAh:

```
autonomie testé de 6 jours en environement idéal( récuperation signal GPS en 3 secondes)
```

## Contribution

Toutes contribution est la bienvenue sur ce projet.


## Auteur

* **Djamal Guellati** - *Initial work* - [Defdjamel](https://github.com/Defdjamel)

 list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

