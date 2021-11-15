<br />
<p align="center">
  <p align="center">
    <h2 align="center">Projet voilier</h2>
    <br />
    <a href="https://github.com/Manah7/Voilier/commits/main"><strong>Voir les versions »</strong></a>
    <br />
    <br />
    <a href="readme.md">Documentation</a>
    ·
    <a href="https://github.com/Manah7/Voilier">Voir le projet</a>
  </p>

# Documentation
Répertoire de travail pour le projet voilier de 4 IR. Ce répertoire est privé. Le code produit est sous licence GNU GPL 3. Vous trouverez ci-après une synthèse des implémentations.

## Liste des fonctions implémentées
* Bordage automatique : **pleinement fonctionnel**
* Orientation voilier : **pleinement fonctionnel**
* Système anti-chavirement : *reconfiguration I2C nécessaire* (voir détails)
* Transmission d'informations : **pleinement fonctionnel**
* Transmission de l'heure : *reconfiguration I2C nécessaire* (voir détails)

### Détails des implémentations
#### Bordage automatique 
La fonction est implémentée avec un bordage linéaire à l'orientation du vent. La précision du réglage des voiles est de 100 pas. 

#### Orientation du voilier
Le voiler est orientable à partir de la télécommande, proportionnellement à la commande utilisateur.

#### Système anti-chavirement et transmission de l'heure
Le système est implémenté, mais l'I2C présente des problème de configuration. La configuration actuelle suit la documentation technique mais la fréquence n'est pas valide. Nous avons fait de nombreuses recherches sur le sujet sans succès.

Hormis le problème de configuration, l'ensemble des fonction anti-chavirement et de la RTC sont opérationnellles.

#### Transmission de l'information
La communication avec la télécommande est bidirectionnelle et est pleinement utilisée par les autres composants. 

## Partiques de codages et méthodologie
Le projet est géré par Git et hébergé sur GitHub.

## Contact
Pour plus d'information, merci de contacter les étudiants du projet.
