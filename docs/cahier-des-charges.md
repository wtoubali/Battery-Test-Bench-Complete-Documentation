
# 📋 Cahier des Charges — Banc de Test de Batteries

## 1. Contexte & Objectifs
Ce projet vise à concevoir un banc d'essai automatisé permettant de mesurer la capacité réelle (mAh / Wh) et la résistance interne (DCIR) de cellules rechargeables (format 18650 / Li-ion), afin d'évaluer leur état de santé (*State of Health - SoH*).

## 2. Spécifications Techniques

### 2.1. Exigences Système
| Paramètre | Valeur Cible |
| :--- | :--- |
| **Plage de tension d'entrée** | $0,0\text{ V} - 4,2\text{ V}$ (Li-ion nominal) |
| **Courant de décharge max** | $\approx 0,84\text{ A}$ (Limité par la résistance passive de $5\,\Omega$) |
| **Type de charge de décharge** | Résistance de puissance $5\,\Omega$ / $10\text{ W}$ avec commutation MOSFET |
| **Précision de mesure de tension** | $\le \pm 10\text{ mV}$ |
| **Précision de mesure de courant** | $\le \pm 10\text{ mA}$ |
| **Fréquence d'échantillonnage** | $1\text{ Hz}$ (1 mesure / seconde) |

### 2.2. Seuils de Sécurité (Sécurité Matérielle & Logicielle)
* **Tension minimale de coupure ($V_{min}$) :** $2,8\text{ V}$ (Arrêt de la décharge pour préserver la cellule)
* **Température maximale ($T_{max}$) :** $60^\circ\text{C}$ sur le corps de la batterie / résistance
* **Protection surintensité ($I_{max}$) :** $1,0\text{ A}$ (Limite de sécurité)

## 3. Exigences Fonctionnelles
1. **Coupure Automatique :** Déconnexion physique immédiate de la charge via le MOSFET dès qu'un seuil de sécurité est atteint.
2. **Journalisation des Données :** Envoi en temps réel des horodatages, de la tension $V_{cell}$, du courant $I_{décharge}$, de la température $T_{cell}$ et de la capacité accumulée ($mAh$).
3. **Fiabilité :** Gestion propre des déconnexions intempestives de capteurs ou de la batterie.
