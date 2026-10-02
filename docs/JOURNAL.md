# 📓 Journal de Bord — Banc d'Essai Batterie

Ce document retrace l'historique des tests.

---

## 📌 Semaine 1 : Phase Initialisation & Dimensionnement
*Statut :* Terminé  
*Date :* Août 2026  

### 📝 Travail réalisé
- [x] Rédaction et validation du cahier des charges fonctionnel.
- [x] Calculs de dimensionnement de la charge fictive (choix de la résistance de puissance de $5\ \Omega$).
- [x] Choix de l'architecture de mesure : module *INA219* pour la tension/courant et sondes *DS18B20* pour la température.
- [x] Commande de l'ensemble des composants électroniques.
- [x] Initialisation de la documentation et de la traçabilité sur GitHub.

### 🔗 Documents associés
- *Fiche de calculs :* [Consulter la fiche de dimensionnement](./calculs-dimensionnement.md)
- *Suivi des essais :* [Consulter le CDC](./cahier-des-charges.md)

---

## 📌 Semaine 2 : Réception du Matériel & Tests Unitaires 
*Statut :* Terminé
*Date :* Août 2026  

### 🧪 Objectifs à la réception du colis
1. *Inspection visuelle & préparation :*
   - Étamage de la panne du fer à souder, vérification des composants reçus.
2. *Tests unitaires sur breadboard :*
   - [x] Test du capteur INA219 (adresse $I^2C$, mesure de tension/courant sur charge connue).
   - [x] Test des sondes thermiques DS18B20 (adresse $1\text{-Wire}$, lecture température ambiante).
   - [x] Validation de la commande du relais 
  


     ---

## 🚀 Semaine 6 : Validation de la Phase 1 et Phase 2
*Statut :* Terminé
*Date :* Septembre 2026

### 🛠️ Travail réalisé
- [x] *Validation de la Phase 1 :* Automatisation du cycle charge puis décharge de la batterie Li-ion 18650.
- [x] *Validation de la Phase 2 :* Implémentation de la PHASE_RELAXATION (pause de 10s entre charge et décharge avec décompte LCD en temps réel).
- [x] *Résolution de bugs d'affichage & bus I2C :* Correctif du rechargement des chronos d'affichage (dernierChronoLCD) et élimination des écrans blancs lors des transitions d'états.
- [x] *Optimisation de la sécurité globale :* Ajustement du seuil de sous-tension à 2,50V et application d'un masque de sécurité transitoire (500-1000ms) pour éviter les faux déclenchements causés par les appels de courant au démarrage de la décharge.

## 🚀 Semaine 7 : Finalisation du câblage, validation du phase 3 & Commande du PCB

*Statut :* Terminé  
*Date :* Octobre 2026

---

### 🛠️ Travail réalisé

* *Remplacement du relais par un transistor MOSFET :* Amélioration de la réactivité, de la durée de vie du système et suppression des bruits mécaniques lors de la commutation de décharge.
* *Finalisation du câblage global*
* *Conception & routage du PCB sous KiCad :*
  * Création d'un PCB double couche (FR-4, 1.6 mm) avec plan de masse global (GND) sur F.Cu et B.Cu.
  * Élargissement des pistes de puissance (1,5 à 2,0 mm) pour supporter le courant de décharge de la batterie 18650.
  * Ajout de perçages de fixation M3 aux 4 coins.
  * Validation complète du test DRC (0 erreur, 0 advertissement).
* *Mise en fabrication :* Génération des fichiers Gerber & Drill et passage de commande du PCB.

---

### 📌 Prochaine étape (Assemblage et courbes de decharge)

* [ ] Réception et soudure des composants sur le PCB sur-mesure.
* [ ] Validation hardware de la carte reçue.
* [ ] Traitement des données et génération des courbes de décharge (acquisition série / export CSV / tracé).
