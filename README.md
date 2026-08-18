# 🔋 Banc d'Essai & Caractérisation de Batteries Li-ion

> **Projet d'ingénierie embarquée : banc de test automatisé pour mesure de capacité (mAh / Wh), évaluation de la résistance interne (DCIR) et suivi de l'état de santé (SoH) de cellules 18650.**

![Status](https://img.shields.io/badge/Statut-Phase%20de%20conception%20%26%20Spécifications-blue)

---

## 📌 Présentation du Projet

Ce projet consiste en la conception d'un banc de test automatisé pour caractériser des cellules Li-ion (format 18650). Le système assure une décharge contrôlée à travers une résistance de puissance, mesure en temps réel les paramètres physiques ($V, I, T$) et isole physiquement la batterie via un **relais électromécanique** dès l'atteinte des seuils de sécurité.

### Objectifs clés
* **Sécurité absolue :** Isolation galvanique immédiate par relais en cas de sous-tension ($< 2{,}8\text{ V}$) ou de surchauffe ($> 60^\circ\text{C}$).
* **Caractérisation :** Calcul de la capacité réelle par intégration numérique ($mAh$) et mesure de la résistance interne ($DCIR$).
* **Répétabilité :** Journalisation automatique des données de décharge à $1\text{ Hz}$.
* 
## 📌 Progression du projet — Batterie banc d'essai

- [x] Commander le matériel
- [ ] Test du matériel
- [ ] Câblage
- [ ] Création du schéma KiCad
- [ ] Phase 1 : Charge puis décharge batterie
- [ ] Phase 2 : Charge puis repos puis décharge de batterie
- [ ] Phase 3 : Plusieurs cycles automatiques de charges/décharges et ajout du ventilateur
- [ ] Phase 4 : Stockage d'informations et calcul de la capacité
- [ ] Phase 5 : Création en 3D du châssis et du PCB
---

## 🛠️ Architecture du Système

```mermaid
graph TD
    Cellule[Cellule Li-ion 18650] -->|Tension / Courant| Capteurs[Capteur V / I]
    Cellule -->|Température| DS18B20[Capteur Température]
    Capteurs -->|I2C / ADC| MCU[Microcontrôleur]
    DS18B20 -->|OneWire / ADC| MCU
    MCU -->|Commande logique| Relais[Module Relais]
    Relais -->|Commutation| Charge[Résistance de puissance 5 Ω / 10 W]
    Charge -->|Boucle de décharge| Cellule
