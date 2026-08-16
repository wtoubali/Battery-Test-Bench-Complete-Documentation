
# 📋 Cahier des Charges — Banc de Test de Batteries

## 1. Context & Objectives
Ce projet vise à concevoir un banc d'essai automatisé permettant de mesurer la capacité réelle (mAh / Wh) et la résistance interne (DCIR) de cellules rechargeables (format 18650 / Li-ion), afin d'évaluer leur état de santé (*State of Health - SoH*).

## 2. Technical Specifications

### 2.1. System Requirements
| Parameter | Target Value |
| :--- | :--- |
| **Input Voltage Range** | $0.0\text{ V} - 5.0\text{ V}$ |
| **Discharge Current Range** | $0.1\text{ A} - 3.0\text{ A}$ (adjustable) |
| **Current Regulation Mode** | Constant Current (CC) via active load |
| **Voltage Measurement Accuracy** | $\le \pm 10\text{ mV}$ |
| **Current Measurement Accuracy** | $\le \pm 10\text{ mA}$ |
| **Sampling Rate** | $1\text{ Hz}$ (1 sample / second) |

### 2.2. Safety Limits (Hard Thresholds)
* **Under-Voltage Cut-off ($V_{min}$):** $2.8\text{ V}$ (configurable depending on chemistry)
* **Over-Temperature Cut-off ($T_{max}$):** $60^\circ\text{C}$ on cell body
* **Over-Current Protection ($I_{max}$):** $3.5\text{ A}$ (software & hardware limit)

## 3. Operational Requirements
1. **Automated Cut-off:** Immediate physical disconnection of the load upon reaching any safety threshold.
2. **Data Logging:** Real-time stream of timestamp, $V_{cell}$, $I_{discharge}$, $T_{cell}$, and accumulated capacity ($mAh$).
3. **Data Integrity:** Graceful handling of sensor disconnections.
