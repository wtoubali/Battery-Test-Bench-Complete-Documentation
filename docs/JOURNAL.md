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
- *Suivi des essais :* [Consulter le journal de bord](./JOURNAL.md)

---

## 📌 Semaine 2 : Réception du Matériel & Tests Unitaires
*Statut :* À venir (En attente de livraison)  
*Date :* Août 2026  

### 🧪 Objectifs à la réception du colis
1. *Inspection visuelle & préparation :*
   - Étamage de la panne du fer à souder, vérification des composants reçus.
2. *Tests unitaires sur breadboard :*
   - [ ] Test du capteur INA219 (adresse $I^2C$, mesure de tension/courant sur charge connue).
   - [ ] Test des sondes thermiques DS18B20 (adresse $1\text{-Wire}$, lecture température ambiante).
   - [ ] Validation de la commande des relais et du transistor du ventilateur.
3. *Photos & Compte-rendu :*
   - Ajout des premières photos du montage volant sur breadboard dans docs/images/.
