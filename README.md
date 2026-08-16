# Battery-Test-Bench-Complete-Documentation
## 📌 Présentation du projet

Ce projet consiste en la conception et la réalisation d'un banc de test automatisé permettant de caractériser des cellules  Li-ion 18650.

L'objectif principal est d'obtenir des mesures précises et répétables sur l'état de santé (*State of Health - SoH*) et la capacité réelle des batteries sous différentes contraintes de décharge.

### Objectifs clés
* **Mesure précise** de la tension, du courant et de la température en temps réel.
* **Décharge à courant variable ** via une résistance de puissance fixe, dimensionnée pour le courant maximal de test.
* **Sécurité matérielle et logicielle** intégrée contre les surtensions, sous-tensions et emballements thermiques.
* **Journalisation automatique** des données sur [carte SD / liaison série / dashboard Web].

---

## 🛠️ Architecture du Système

### Hardware
* **Microcontrôleur :**  Arduino Uno 
* **Capteurs :**
  * Tension & Courant : INA219 
  * Température :  DS18B20 au contact de la cellule et de la résistance de puissance.
* **Étage de puissance & Charge active :** [ex : MOSFET de puissance N-Channel, dissipateur thermique, régulation AOP]
* **Sécurité physique :** Relais de coupure d'urgence.

### Software
* **Langage :** C++ / Embedded C (Arduino framework / FreeRTOS)
* **Traitement de données :** [Python (Pandas / Matplotlib) pour la génération automatique de graphiques à partir des fichiers CSV]

---

## ⚙️ Fonctionnalités & Sécurités

### 1. Modes de fonctionnement
* **Test de capacité (Ah / Wh) :** Intégration numérique du courant dans le temps (méthode des trapèzes).
* **Estimation de la résistance interne (DCIR) :** Mesure de la chute de tension lors d'une impulsion de courant ($\Delta V / \Delta I$).
* **Coupure automatique (*Cut-off*) :** Arrêt immédiat dès l'atteinte de la tension minimale de sécurité (2,8V pour du Li-ion).

### 2. Moteur de sécurité (*Safety Engine*)
| Risque | Condition de déclenchement | Action corrective |
| :--- | :--- | :--- |
| **Sous-tension** | $V_{cell} < V_{min}$ | Ouverture du relais & arrêt décharge |
| **Surchauffe** | $T > 60^\circ\text{C}$ | Coupure de puissance + ventilation max |
| **Surintensité** | $I > I_{max}$ | Disjonction logicielle en $< 10\text{ ms}$ |
