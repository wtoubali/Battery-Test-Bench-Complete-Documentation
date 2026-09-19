//Library
 #include <DallasTemperature.h>
 #include <OneWire.h>
 #include <LiquidCrystal.h>
 #include <Wire.h>
 #include <Adafruit_INA219.h>
 Adafruit_INA219 ina219;

#define ONE_WIRE_BUS 4 
const byte MOSFET1 = 2; // MOSFET de décharge
const byte MOSFET2 = 3; // Relais / MOSFET de charge

//Mesure de la tension à vide et calcul du pourcentage de batterie
 float tensionAVide = 0.0;
 int pourcentageBatterie= 0;
 int calculerPourcentageBatterie(float tension){
 if (tension>= 4.10) return 100;
 if (tension <= 3 ) return 0;
 if (tension >= 4.05) return map(tension * 100, 405, 410, 90, 100);
 if (tension >= 3.80) return map(tension * 100, 380, 405, 50, 90);
 if (tension >= 3.60) return map(tension * 100, 360, 380, 20, 50);
 if (tension >= 3.30) return map(tension * 100, 330, 360, 5, 20);
 return map(tension * 100, 300, 330, 0, 5);
    }


// Boutons
 const byte BTN_START_STOP = 6;
 const byte BTN_REARMEMENT = 5;
 bool etatBtnStartPrec = HIGH;
 bool etatBtnRearmPrec = HIGH;
 bool etaitEnCharge = true;
// Timers OCV
 unsigned long dernierMesureOCV = 0;
 const unsigned long INTERVALLE_OCV = 60000;
 bool enPauseOCV = false;
 unsigned long debutPauseOCV = 0;
 unsigned long debutPhaseDecharge = 0;
// Masquage transitoire
 unsigned long tempsCommutation = 0;

// Affichage LCD
 unsigned long dernierChangementEcran = 0;
 unsigned long dernierChronoLCD = 0;
 bool afficherTemp = true;
 LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
 String messageDefaut1 = "  DEFAUT TEMPERATURE 1 !  ";
 String messageDefaut2 = "  DEFAUT TEMPERATURE 2 !  ";
 String messageDefaut3 = "SURINTENSITE !";
 String messageDefaut4 = "BATTERIE SOUS TENSION !";
 String motifDefaut= "";
 int indexCaractere = 0;
// Capteurs DS18B20
 OneWire oneWire(ONE_WIRE_BUS);
 DallasTemperature sensors(&oneWire);
 DeviceAddress sensor1 = {0x28, 0x46, 0x52, 0x6D, 0x00, 0x00, 0x00, 0xC2};
 DeviceAddress sensor2 = {0x28, 0x5E, 0x8E, 0x70, 0x00, 0x00, 0x00, 0xE2};

enum EtatSysteme {
    PHASE_REPOS,
    PHASE_CHARGE,
    PHASE_DECHARGE,
    FIN_TEST,
    PHASE_DEFAUT
 };
 EtatSysteme etatActuel = PHASE_REPOS; // Démarre au repos par sécurité
 bool estEnPause = false;

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    
    // Boutons avec Pull-Up interne 
     pinMode(BTN_START_STOP, INPUT_PULLUP);
     pinMode(BTN_REARMEMENT, INPUT_PULLUP);

    sensors.begin();
    sensors.setResolution(sensor1, 10); // 10-bit pour réduire le délai à 187ms
    sensors.setResolution(sensor2, 10);
    sensors.setWaitForConversion(false); // Mode non-bloquant

    ina219.begin();
    ina219.setCalibration_32V_1A();

    pinMode(MOSFET1, OUTPUT);
    pinMode(MOSFET2, OUTPUT);
    digitalWrite(MOSFET1, LOW);
    digitalWrite(MOSFET2, LOW);

    lcd.print("SYSTEME PRET");
    lcd.setCursor(0, 1);
    lcd.print("APPUYER START");

    tensionAVide = ina219.getBusVoltage_V() + (ina219.getShuntVoltage_mV() / 1000.0);
    pourcentageBatterie = calculerPourcentageBatterie(tensionAVide);
}

void loop() {
    // 1. MESURES
     float busvoltage = ina219.getBusVoltage_V();
     float shuntvoltage = ina219.getShuntVoltage_mV();
     float current_mA = ina219.getCurrent_mA();
     float power_mW = ina219.getPower_mW();
     float loadvoltage = busvoltage + (shuntvoltage / 1000.0);
     Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
     Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
     Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
     Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
     Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
     Serial.println("");
   // Lecture non-bloquante des températures
     sensors.requestTemperatures();
     float temp1 = sensors.getTempC(sensor1);
     float temp2 = sensors.getTempC(sensor2);
     Serial.print("temperature 1:");
     Serial.println(temp1);
     Serial.print("temperature 2:");
     Serial.println(temp2);
    
    // 2. GESTION DES BOUTONS
    bool lectureStart = digitalRead(BTN_START_STOP);
    if (lectureStart == LOW && etatBtnStartPrec == HIGH) {
        if (etatActuel == PHASE_REPOS) { 
            if (estEnPause){
              if (etaitEnCharge){
                  etatActuel = PHASE_CHARGE;
              }
              else{ 
                etatActuel = PHASE_DECHARGE;
              }
              estEnPause = false;
               }
              else { 
                etatActuel = PHASE_CHARGE;
              }
            tempsCommutation = millis();
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("DEMARRAGE...");
            dernierChangementEcran = millis();
        } else if (etatActuel == PHASE_CHARGE || etatActuel == PHASE_DECHARGE) {
            etaitEnCharge = (etatActuel == PHASE_CHARGE);
            etatActuel = PHASE_REPOS;
            estEnPause = true;
            digitalWrite(MOSFET1,LOW);
            digitalWrite(MOSFET2,LOW);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("ARRET MANUEL");
            dernierChangementEcran = millis();
        }
    }
    etatBtnStartPrec = lectureStart;

    bool lectureRearm = digitalRead(BTN_REARMEMENT);
    if (lectureRearm == LOW && etatBtnRearmPrec == HIGH) {
        if (etatActuel == PHASE_DEFAUT) {
                etatActuel = PHASE_REPOS;
                estEnPause = false;
                motifDefaut="";
                lcd.clear();
                lcd.print("DEFAUT ACQUITTE");
                dernierChangementEcran = millis();
            
        }
    }
    etatBtnRearmPrec = lectureRearm;

    // 3. SÉCURITÉ GLOBALE (Pendant le test)
    if (etatActuel == PHASE_CHARGE || etatActuel == PHASE_DECHARGE) {
        // Test de sécurité uniquement après le masque de commutation (500 ms)
        if (millis() - tempsCommutation > 500) {
        
        if (temp1 > 40.0) {
            motifDefaut = "TEMP1_HAUTE";
            etatActuel = PHASE_DEFAUT;
            indexCaractere = 0;
            lcd.clear();
        } 
        else if (temp2 > 40.0) {
            motifDefaut = "TEMP2_HAUTE";
            etatActuel = PHASE_DEFAUT;
            indexCaractere = 0;
            lcd.clear();
        } 
        else if (current_mA > 1000.0) {
            motifDefaut = "SURINTENSITE";
            etatActuel = PHASE_DEFAUT;
            indexCaractere = 0;
            lcd.clear();
        } 
        else if (loadvoltage < 2.80) {
            motifDefaut = "SOUS_TENSION";
            etatActuel = PHASE_DEFAUT;
            indexCaractere = 0;
            lcd.clear();
        }

    }
    }

    // 4. MACHINE D'ÉTAT PRINCIPALE
    switch (etatActuel) {

        case PHASE_REPOS:
            digitalWrite(MOSFET1, LOW);
            digitalWrite(MOSFET2, LOW);
            if (millis() - dernierChangementEcran >= 3000) {
                dernierChangementEcran = millis();
                afficherTemp = !afficherTemp; 
                lcd.clear();
                if (estEnPause){ 
                  lcd.setCursor(0, 0);
                  lcd.print("SYSTEME EN PAUSE");
                  lcd.setCursor(0, 1);
                  if (afficherTemp) {
                    lcd.print("Pourcentage:"); lcd.print(pourcentageBatterie, 1); lcd.print ("%");
                   // lcd.print("C T2:"); lcd.print(temp2, 1); lcd.print("C");
                   }
                   else {
                    lcd.print("START: D5"); 
                     }
                     } 
                 else { 
                  lcd.print("SYSTEME PRET");
                  lcd.setCursor(0, 1);
                  lcd.print("APPUYER START");
                  }       
                   }
            break;

        case PHASE_CHARGE:
            digitalWrite(MOSFET1, LOW);

            // Déclenchement séquence OCV
            if (!enPauseOCV && (millis() - dernierMesureOCV >= INTERVALLE_OCV)) {
                dernierMesureOCV = millis();
                debutPauseOCV = millis();
                enPauseOCV = true;
                digitalWrite(MOSFET2, LOW); // Coupe la charge
            }

            // Traitement mesure OCV après 200 ms
            if (enPauseOCV && (millis() - debutPauseOCV >= 200)) {
                enPauseOCV = false;
                loadvoltage = ina219.getBusVoltage_V();
                tensionAVide = loadvoltage;
                pourcentageBatterie = calculerPourcentageBatterie(tensionAVide);
                if (loadvoltage >= 4.10) { // Fin de charge
                    digitalWrite(MOSFET2, LOW);
                    etatActuel = PHASE_DECHARGE;
                    tempsCommutation = millis();
                    debutPhaseDecharge = millis();
                    lcd.clear();
                    break;
                } else {
                    digitalWrite(MOSFET2, HIGH);
                }
            } else if (!enPauseOCV) {
                digitalWrite(MOSFET2, HIGH);
            }

            // Affichage alterné
            if (millis() - dernierChangementEcran >= 3000) {
                dernierChangementEcran = millis();
                afficherTemp = !afficherTemp;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PHASE CHARGE    ");
                lcd.setCursor(0, 1);
                if (afficherTemp) {
                    lcd.print("Pourcentage:"); lcd.print(pourcentageBatterie, 1); lcd.print ("%");
                   // lcd.print("C T2:"); lcd.print(temp2, 1); lcd.print("C");
                } else {
                    lcd.print("Tension:"); lcd.print(tensionAVide, 2); lcd.print("V");
                    //lcd.print("V I:"); lcd.print((int)current_mA); lcd.print("mA");
                }
            }
            break;

        case PHASE_DECHARGE:
            digitalWrite(MOSFET2, LOW);
            
            if (!enPauseOCV && (millis() - dernierMesureOCV >= INTERVALLE_OCV)) {
                dernierMesureOCV = millis();
                debutPauseOCV = millis();
                enPauseOCV = true;
                digitalWrite(MOSFET1, LOW); // Coupe la decharge
            }

            // Traitement mesure OCV après 200 ms
            if (enPauseOCV && (millis() - debutPauseOCV >= 200)) {
                enPauseOCV = false;
                loadvoltage = ina219.getBusVoltage_V();
                tensionAVide = loadvoltage;
                pourcentageBatterie = calculerPourcentageBatterie(tensionAVide);
                if (tensionAVide <= 3.10) { // Fin de decharge
                    digitalWrite(MOSFET1, LOW);
                    etatActuel = FIN_TEST;
                    tempsCommutation = millis();
                    debutPhaseDecharge = millis();
                    lcd.clear();
                    break;
                } else {
                    digitalWrite(MOSFET1, HIGH);
                }
                 }
                 else if (!enPauseOCV) {
                digitalWrite(MOSFET1, HIGH);
                 } 

            if (millis() - dernierChangementEcran >= 3000) {
                dernierChangementEcran = millis();
                afficherTemp = !afficherTemp;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PHASE DECHARGE  ");
                lcd.setCursor(0, 1);
                if (afficherTemp) {
                    lcd.print("Pourcentage:"); lcd.print(pourcentageBatterie);
                    //lcd.print("C T2:"); lcd.print(temp2, 1); lcd.print("C");
                } else {
                    lcd.print("V:"); lcd.print(tensionAVide, 2);
                    lcd.print("I:"); lcd.print((int)current_mA); lcd.print("mA");
                }
            }
            break;

        case FIN_TEST:
            digitalWrite(MOSFET1, LOW);
            digitalWrite(MOSFET2, LOW);
            lcd.setCursor(0, 0);
            lcd.print("CYCLE TERMINE ! ");
            lcd.setCursor(0, 1);
            lcd.print("BATTERIE OK     ");
            break;

        case PHASE_DEFAUT:
            digitalWrite(MOSFET1, LOW);
            digitalWrite(MOSFET2, LOW);

            if (millis() - dernierChronoLCD >= 400) {
                dernierChronoLCD = millis();
                lcd.clear();
                if (motifDefaut == "TEMP1_HAUTE"){
                       lcd.clear();
                       lcd.setCursor(0,0);
                       lcd.print(messageDefaut1.substring(indexCaractere, indexCaractere + 16));;
                       indexCaractere++;
                       lcd.setCursor(0,1);
                       lcd.print("T1:");
                       lcd.print(temp1);
                       lcd.print("C");
                       if (indexCaractere > messageDefaut1.length() - 16)  { 
                       indexCaractere = 0; 
                       } 
                        }
                else if (motifDefaut == "TEMP2_HAUTE" ) { 
                     if (millis()- dernierChronoLCD > 300 ) {
                     dernierChronoLCD = millis();
                     lcd.clear();
                     lcd.setCursor(0,0);
                     lcd.print(messageDefaut2.substring(indexCaractere, indexCaractere + 16));;
                     indexCaractere++;
                     lcd.setCursor(0,1);
                     lcd.print("T2:");
                     lcd.print(temp2);
                     lcd.print("C");
                     if (indexCaractere > messageDefaut2.length() - 16)  { 
                     indexCaractere = 0;
                     } 
                      } 
                       }
                        }
                else if (motifDefaut == "SURINTENSITE") {
                       lcd.clear();
                       lcd.setCursor(0,0);
                       lcd.print(messageDefaut3.substring(indexCaractere, indexCaractere + 16));;
                       indexCaractere++;
                       lcd.setCursor(0,1);
                       lcd.print("VEUILLEZ REARMER");
                       if (indexCaractere > messageDefaut3.length() - 16)  { 
                       indexCaractere = 0; 
                       } 
                        }
                else if (motifDefaut == "SOUS_TENSION") {
                       lcd.clear();
                       lcd.setCursor(0,0);
                       lcd.print(messageDefaut4.substring(indexCaractere, indexCaractere + 16));;
                       indexCaractere++;
                       lcd.setCursor(0,1);
                       lcd.print("VEUILLEZ REARMER");
                       if (indexCaractere > messageDefaut4.length() - 16)  { 
                       indexCaractere = 0; 
                       } 
                        }
             
            break;
        }
