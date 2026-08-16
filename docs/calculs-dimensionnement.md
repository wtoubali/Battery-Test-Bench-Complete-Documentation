# 📐 Dimensionnement & Calculs Théoriques

## 1. Charge Active & Dissipation Thermique

La charge active convertit l'énergie de la batterie en chaleur via un transistor MOSFET de puissance opérant en régime linéaire.

### Conditions défavorables (Pire cas)
* Tension maximale cellule ($V_{max}$) : $4.2\text{ V}$ (Pleine charge)
* Courant de décharge maximal ($I_{max}$) : $3.0\text{ A}$
* Puissance maximale à dissiper :
$$P_{max} = V_{max} \times I_{max} = 4.2\text{ V} \times 3.0\text{ A} = 12.6\text{ W}$$

### Choix du dissipateur thermique (Radiateur)
Afin de maintenir la température de jonction du MOSFET ($T_j$) en dessous de sa limite absolue ($150^\circ\text{C}$ max, cible de sécurité $\le 90^\circ\text{C}$) pour une température ambiante $T_a = 25^\circ\text{C}$ :

$$R_{th,ja} \le \frac{T_{j,max} - T_a}{P_{max}} = \frac{90 - 25}{12.6} \approx 5.16\text{ K/W}$$

> **Conclusion :** Le dissipateur choisi devra présenter une résistance thermique $R_{th} \le 4\text{ K/W}$ (ou être couplé à une ventilation forcée).

---

## 2. Intégration Numérique de la Capacité (Ah / Wh)

La capacité cumulative est calculée par intégration du courant dans le temps. En environnement embarqué, on utilise la **méthode des trapèzes** :

$$Q(t) = \sum_{k=1}^{N} \frac{I_k + I_{k-1}}{2} \cdot \Delta t$$

Avec un intervalle d'échantillonnage $\Delta t = 1\text{ s}$ :
$$\text{Capacité (mAh)} = \sum \left( \frac{I_k + I_{k-1}}{2} \right) \times \frac{1000}{3600}$$

---

## 3. Mesure de la Résistance Interne (DCIR)

La résistance interne continue (DCIR) est calculée par la méthode de l'impulsion de courant à $t_0$ :

$$R_{internal} = \frac{\Delta V}{\Delta I} = \frac{V_{open\_circuit} - V_{load}}{I_{load}}$$

* **Exemple de résolution visée :** Si $\Delta V = 50\text{ mV}$ pour $\Delta I = 2\text{ A}$, $R_{internal} = 25\text{ m}\Omega$.
