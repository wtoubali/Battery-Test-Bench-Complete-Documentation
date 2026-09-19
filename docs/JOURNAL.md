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
*Date :* Août 2026  

### 🧪 Objectifs à la réception du colis
1. *Inspection visuelle & préparation :*
   - Étamage de la panne du fer à souder, vérification des composants reçus.
2. *Tests unitaires sur breadboard :*
   - [x] Test du capteur INA219 (adresse $I^2C$, mesure de tension/courant sur charge connue).
   - [x] Test des sondes thermiques DS18B20 (adresse $1\text{-Wire}$, lecture température ambiante).
   - [x] Validation de la commande des relais et du transistor du ventilateur.
3. *Photos & Compte-rendu :*
   - Ajout des premières photos du montage volant sur breadboard dans docs/images/.
  




     ---

## 🚀 Semaine : Validation de la Phase 1 et Phase 2
*Statut :* Terminé[span_2](start_span)[span_2](end_span)
*Date :* Septembre 2026

### 🛠️ Travail réalisé
- [x] *Validation de la Phase 1 :* Automatisation du cycle charge puis décharge de la batterie Li-ion 18650[span_3](start_span)[span_3](end_span).
- [x] *Validation de la Phase 2 :* Implémentation de la PHASE_RELAXATION (pause de 10s entre charge et décharge avec décompte LCD en temps réel)[span_4](start_span)[span_4](end_span)[span_5](start_span)[span_5](end_span).
- [x] *Résolution de bugs d'affichage & bus I2C :* Correctif du rechargement des chronos d'affichage (dernierChronoLCD) et élimination des écrans blancs lors des transitions d'états[span_6](start_span)[span_6](end_span)[span_7](start_span)[span_7](end_span).
- [x] *Optimisation de la sécurité globale :* Ajustement du seuil de sous-tension à 2,50V et application d'un masque de sécurité transitoire (500-1000ms) pour éviter les faux déclenchements causés par les appels de courant au démarrage de la décharge[span_8](start_span)[span_8](end_span).

### 🛠️ Prochaine étape (Phase 3)
- [ ] Implémentation du cyclage automatique (plusieurs cycles charges/décharges)[span_9](start_span)[span_9](end_span).
- [ ] Gestion et asservissement du ventilateur de refroidissement[span_10](start_span)[span_10](end_span).
