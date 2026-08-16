# 📐 Dimensionnement & Calculs Théoriques

## 1. Charge Passive & Validation Thermique

La dissipation d'énergie est assurée par une résistance de puissance de $R = 5\,\Omega$ ($10\text{ W}$ max). La décharge est commutée de manière tout-ou-rien via un relais électromécanique, garantissant une isolation galvanique complète lors de l'arrêt du test.

### Conditions de décharge (Pire cas - Batterie pleine)
* Tension maximale cellule ($V_{max}$) : $4.2\text{ V}$
* Résistance de charge ($R$) : $5.0\,\Omega$

#### Courant maximal ($I_{max}$) :
$$I_{max} = \frac{V_{max}}{R} = \frac{4.2\text{ V}}{5.0\,\Omega} = 0.84\text{ A}$$

> Le courant maximal reste sous la limite fixée de $1.0\text{ A}$.

#### Puissance maximale dissipée dans la résistance ($P_{R,max}$) :
$$P_{R,max} = \frac{V_{max}^2}{R} = \frac{(4.2)^2}{5.0} = \frac{17.64}{5} = 3.53\text{ W}$$

#### Bilan de puissance & Marge de sécurité :
* **Puissance nominale de la résistance :** $10\text{ W}$
* **Taux d'utilisation thermique (Pire cas) :**
$$\text{Taux d'utilisation} = \frac{3.53\text{ W}}{10\text{ W}} \times 100 \approx 35.3\%$$

> **Conclusion :** La résistance de $10\text{ W}$ fonctionne avec une marge de sécurité importante ($>64\%$), ce qui limite son échauffement tout en garantissant un fonctionnement passif stable. Le relais évite les fuites de courant hors phases de test.

---

## 2. Intégration Numérique de la Capacité (Ah / Wh)

La capacité cumulative est calculée par intégration du courant mesuré en temps réel. En environnement embarqué, on utilise la **méthode des trapèzes** :

$$Q(t) = \sum_{k=1}^{N} \frac{I_k + I_{k-1}}{2} \cdot \Delta t$$

Avec un intervalle d'échantillonnage $\Delta t = 1\text{ s}$ :
$$\text{Capacité (mAh)} = \sum \left( \frac{I_k + I_{k-1}}{2} \right) \times \frac{1000}{3600}$$

---

## 3. Mesure de la Résistance Interne (DCIR)

La résistance interne continue (DCIR) est calculée lors de la fermeture du relais de décharge (mesure de la chute de tension sous charge) :

$$R_{internal} = \frac{\Delta V}{\Delta I} = \frac{V_{vide} - V_{en\_charge}}{I_{mesuré}}$$

* **Exemple de calcul :** Si la tension passe de $4.10\text{ V}$ (relais ouvert) à $3.95\text{ V}$ (relais fermé, $I = 0.79\text{ A}$) :
$$\Delta V = 0.15\text{ V} \implies R_{internal} = \frac{0.15\text{ V}}{0.79\text{ A}} \approx 190\text{ m}\Omega$$
