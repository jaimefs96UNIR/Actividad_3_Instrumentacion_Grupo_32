#include <Servo.h>
#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>

// -------------------- PINES --------------------
const int PIN_IR = 2;
const int PIN_DHT22 = 3;

const int PIN_BOTON_P0 = 4;
const int PIN_SERVO = 5;

// LED de iluminación artificial en pin PWM D6
const int PIN_LED_LUZ = 6;

// RGB LED
// El rojo se mueve a A3 para liberar D6
const int PIN_RGB_R = A3;
const int PIN_RGB_G = 7;
const int PIN_RGB_B = 8;

const int PIN_BOTON_P1 = 10;
const int PIN_BOTON_P2 = 11;
const int PIN_BOTON_P3 = 12;
const int PIN_BOTON_P4 = 13;

const int PIN_LDR = A0;
const int PIN_PIR = A1;

// -------------------- CONFIGURACIÓN DE ACTUADORES --------------------
// RGB configurado como ánodo común:
// COM -> 5V
// LOW enciende color, HIGH apaga color.
const bool RGB_ANODO_COMUN = true;

// LED iluminación artificial conectado normal:
// D6 -> resistencia -> ánodo LED
// cátodo LED -> GND
const bool LED_LUZ_ACTIVO_BAJO = false;

// -------------------- OBJETOS --------------------
Servo servoAscensor;
SimpleDHT22 dht22(PIN_DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------------------- ASCENSOR --------------------
const int NUM_PLANTAS = 5;

const int angulosPlanta[NUM_PLANTAS] = {
  0, 45, 90, 135, 180
};

const int botonesPlanta[NUM_PLANTAS] = {
  PIN_BOTON_P0,
  PIN_BOTON_P1,
  PIN_BOTON_P2,
  PIN_BOTON_P3,
  PIN_BOTON_P4
};

int plantaActual = 0;
int plantaDestino = 0;

// -------------------- CONTROL AMBIENTAL --------------------
const float TEMP_SETPOINT = 25.0;
const float TEMP_ZONA_MUERTA = 2.0;

const int LUZ_SETPOINT = 80;
const int LUZ_ZONA_MUERTA = 5;

float temperaturaMedida = 25.0;
float humedadMedida = 40.0;

float ultimaTemperaturaValida = 25.0;
float ultimaHumedadValida = 40.0;

float temperaturaControlada = 25.0;

bool dhtDisponible = false;
bool temperaturaInicializada = false;

int luzMedida = 0;
int potenciaLuzArtificial = 0;
bool presenciaUsuario = false;

String accionTemperatura = "Reposo";
String estadoDHT = "Inicial";

// -------------------- TEMPORIZACIÓN --------------------
unsigned long ultimoControl = 0;
const unsigned long INTERVALO_CONTROL = 500;

unsigned long ultimaLecturaDHT = 0;
const unsigned long INTERVALO_DHT = 3000;

unsigned long ultimoLCD = 0;
const unsigned long INTERVALO_LCD = 1000;

unsigned long ultimoLog = 0;
const unsigned long INTERVALO_LOG = 2000;

bool paginaLCD = false;

// ======================================================
//                      RGB LED
// ======================================================

void escribirRGB(bool rojo, bool verde, bool azul) {
  if (RGB_ANODO_COMUN) {
    digitalWrite(PIN_RGB_R, rojo ? LOW : HIGH);
    digitalWrite(PIN_RGB_G, verde ? LOW : HIGH);
    digitalWrite(PIN_RGB_B, azul ? LOW : HIGH);
  } else {
    digitalWrite(PIN_RGB_R, rojo ? HIGH : LOW);
    digitalWrite(PIN_RGB_G, verde ? HIGH : LOW);
    digitalWrite(PIN_RGB_B, azul ? HIGH : LOW);
  }
}

void apagarRGB() {
  escribirRGB(false, false, false);
}

void mostrarRGBCalentar() {
  escribirRGB(true, false, false);   // rojo
}

void mostrarRGBReposo() {
  escribirRGB(false, true, false);   // verde
}

void mostrarRGBEnfriar() {
  escribirRGB(false, false, true);   // azul
}

void pruebaInicialRGB() {
  Serial.println("Test RGB: rojo");
  mostrarRGBCalentar();
  delay(600);

  Serial.println("Test RGB: verde");
  mostrarRGBReposo();
  delay(600);

  Serial.println("Test RGB: azul");
  mostrarRGBEnfriar();
  delay(600);

  apagarRGB();
  delay(300);
}

// ======================================================
//                LED ILUMINACIÓN ARTIFICIAL
// ======================================================

void escribirLedLuz(int pwm) {
  pwm = constrain(pwm, 0, 255);

  if (LED_LUZ_ACTIVO_BAJO) {
    analogWrite(PIN_LED_LUZ, 255 - pwm);
  } else {
    analogWrite(PIN_LED_LUZ, pwm);
  }
}

void pruebaInicialLedLuz() {
  Serial.println("Test LED luz: brillo alto");
  escribirLedLuz(255);
  delay(700);

  Serial.println("Test LED luz: brillo medio");
  escribirLedLuz(80);
  delay(700);

  Serial.println("Test LED luz: apagado");
  escribirLedLuz(0);
  delay(300);
}

// ======================================================
//                        SENSORES
// ======================================================

int leerLuzPorcentaje() {
  int valor = analogRead(PIN_LDR);

  // En tu montaje, poca luz genera lectura ADC alta.
  // Por eso se invierte el mapeo.
  int porcentaje = map(valor, 0, 1023, 100, 0);
  porcentaje = constrain(porcentaje, 0, 100);

  return porcentaje;
}

void leerDHT22Seguro() {
  static float ultimaTempDHTDetectada = 25.0;

  float t = 0.0;
  float h = 0.0;

  int err = dht22.read2(&t, &h, NULL);

  if (err == SimpleDHTErrSuccess) {
    temperaturaMedida = t;
    humedadMedida = h;

    ultimaTemperaturaValida = t;
    ultimaHumedadValida = h;

    dhtDisponible = true;
    estadoDHT = "OK";

    if (!temperaturaInicializada) {
      temperaturaControlada = temperaturaMedida;
      ultimaTempDHTDetectada = temperaturaMedida;
      temperaturaInicializada = true;
    }

    // Si el usuario cambia la temperatura del DHT22 en Wokwi,
    // se toma como perturbación térmica.
    if (abs(t - ultimaTempDHTDetectada) > 1.0) {
      temperaturaControlada = t;
      ultimaTempDHTDetectada = t;
    }
  } else {
    if (dhtDisponible) {
      temperaturaMedida = ultimaTemperaturaValida;
      humedadMedida = ultimaHumedadValida;
      estadoDHT = "UltimaValida";
    } else {
      temperaturaMedida = 25.0;
      humedadMedida = 40.0;
      temperaturaControlada = 25.0;
      estadoDHT = "Pendiente";
    }
  }
}

void leerSensores() {
  unsigned long ahora = millis();

  if (ahora - ultimaLecturaDHT >= INTERVALO_DHT) {
    ultimaLecturaDHT = ahora;
    leerDHT22Seguro();
  }

  luzMedida = leerLuzPorcentaje();
  presenciaUsuario = digitalRead(PIN_PIR);
}

// ======================================================
//                   CONTROL AMBIENTAL
// ======================================================

void controlarTemperatura() {
  float limiteSuperior = TEMP_SETPOINT + TEMP_ZONA_MUERTA;
  float limiteInferior = TEMP_SETPOINT - TEMP_ZONA_MUERTA;

  if (temperaturaControlada > limiteSuperior) {
    accionTemperatura = "Enfriar";
    mostrarRGBEnfriar();

    // Simulación del efecto de refrigeración
    temperaturaControlada -= 0.5;
  }
  else if (temperaturaControlada < limiteInferior) {
    accionTemperatura = "Calentar";
    mostrarRGBCalentar();

    // Simulación del efecto de calefacción
    temperaturaControlada += 0.5;
  }
  else {
    accionTemperatura = "Reposo";
    mostrarRGBReposo();
  }
}

void controlarIluminacion() {
  int limiteInferior = LUZ_SETPOINT - LUZ_ZONA_MUERTA;

  if (luzMedida < limiteInferior) {
    int errorLuz = LUZ_SETPOINT - luzMedida;

    potenciaLuzArtificial = map(errorLuz, 0, 100, 0, 255);
    potenciaLuzArtificial = constrain(potenciaLuzArtificial, 0, 255);
  } else {
    potenciaLuzArtificial = 0;
  }

  escribirLedLuz(potenciaLuzArtificial);
}

// ======================================================
//                          LCD
// ======================================================

String accionCorta() {
  if (accionTemperatura == "Calentar") return "Calor";
  if (accionTemperatura == "Enfriar") return "Frio";
  return "Reposo";
}

void mostrarLCD() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("P");
  lcd.print(plantaActual);
  lcd.print("->P");
  lcd.print(plantaDestino);

  if (presenciaUsuario) {
    lcd.print(" Ocup");
  } else {
    lcd.print(" Libre");
  }

  lcd.setCursor(0, 1);

  if (!paginaLCD) {
    lcd.print("T:");
    lcd.print(temperaturaMedida, 1);
    lcd.print(" H:");
    lcd.print(humedadMedida, 0);
    lcd.print("%");
  } else {
    lcd.print(accionCorta());
    lcd.print(" L:");
    lcd.print(luzMedida);
    lcd.print("%");
  }

  paginaLCD = !paginaLCD;
}

void mostrarLCDMovimiento() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("P");
  lcd.print(plantaActual);
  lcd.print("->P");
  lcd.print(plantaDestino);

  if (presenciaUsuario) {
    lcd.print(" Ocup");
  } else {
    lcd.print(" Libre");
  }

  lcd.setCursor(0, 1);
  lcd.print("Moviendo cabina");
}

// ======================================================
//                     CONTROL ASCENSOR
// ======================================================

void moverAscensorA(int destino) {
  if (destino < 0 || destino >= NUM_PLANTAS) {
    return;
  }

  plantaDestino = destino;
  mostrarLCDMovimiento();

  if (destino == plantaActual) {
    delay(800);
    mostrarLCD();
    return;
  }

  int anguloInicial = angulosPlanta[plantaActual];
  int anguloFinal = angulosPlanta[plantaDestino];

  if (anguloFinal > anguloInicial) {
    for (int angulo = anguloInicial; angulo <= anguloFinal; angulo++) {
      servoAscensor.write(angulo);
      delay(30);
    }
  } else {
    for (int angulo = anguloInicial; angulo >= anguloFinal; angulo--) {
      servoAscensor.write(angulo);
      delay(30);
    }
  }

  plantaActual = plantaDestino;
  mostrarLCD();
}

void comprobarBotones() {
  static bool estadoAnterior[NUM_PLANTAS] = {
    HIGH, HIGH, HIGH, HIGH, HIGH
  };

  for (int i = 0; i < NUM_PLANTAS; i++) {
    bool estadoActual = digitalRead(botonesPlanta[i]);

    // INPUT_PULLUP:
    // sin pulsar = HIGH
    // pulsado = LOW
    if (estadoAnterior[i] == HIGH && estadoActual == LOW) {
      moverAscensorA(i);

      Serial.print("Llamada por pulsador a planta ");
      Serial.println(i);

      delay(250);
    }

    estadoAnterior[i] = estadoActual;
  }
}

// ======================================================
//                       MANDO IR
// ======================================================
// Wokwi IR Remote usa comandos NEC.
// Teclas:
// 0 = 104
// 1 = 48
// 2 = 24
// 3 = 122
// 4 = 16
//
// IMPORTANTE:
// IrReceiver.begin(PIN_IR) se usa SIN ENABLE_LED_FEEDBACK
// para no interferir con D13.

void comprobarMandoIR() {
  if (IrReceiver.decode()) {
    uint8_t comando = IrReceiver.decodedIRData.command;

    Serial.print("Codigo IR recibido: ");
    Serial.println(comando);

    switch (comando) {
      case 104:   // tecla 0
        moverAscensorA(0);
        break;

      case 48:    // tecla 1
        moverAscensorA(1);
        break;

      case 24:    // tecla 2
        moverAscensorA(2);
        break;

      case 122:   // tecla 3
        moverAscensorA(3);
        break;

      case 16:    // tecla 4
        moverAscensorA(4);
        break;

      default:
        Serial.println("Tecla IR sin asignar");
        break;
    }

    IrReceiver.resume();
  }
}

// ======================================================
//                         LOG
// ======================================================

void enviarLogSerie() {
  Serial.print(plantaActual);
  Serial.print(",");
  Serial.print(plantaDestino);
  Serial.print(",");
  Serial.print(presenciaUsuario ? "SI" : "NO");
  Serial.print(",");

  Serial.print(temperaturaMedida);
  Serial.print(",");
  Serial.print(humedadMedida);
  Serial.print(",");
  Serial.print(temperaturaControlada);
  Serial.print(",");
  Serial.print(luzMedida);
  Serial.print(",");
  Serial.print(accionTemperatura);
  Serial.print(",");
  Serial.print(potenciaLuzArtificial);
  Serial.print(",");
  Serial.println(estadoDHT);
}

// ======================================================
//                         SETUP
// ======================================================

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_PLANTAS; i++) {
    pinMode(botonesPlanta[i], INPUT_PULLUP);
  }

  pinMode(PIN_RGB_R, OUTPUT);
  pinMode(PIN_RGB_G, OUTPUT);
  pinMode(PIN_RGB_B, OUTPUT);
  pinMode(PIN_LED_LUZ, OUTPUT);
  pinMode(PIN_PIR, INPUT);

  apagarRGB();
  escribirLedLuz(0);

  servoAscensor.attach(PIN_SERVO);
  servoAscensor.write(angulosPlanta[plantaActual]);

  lcd.init();
  lcd.backlight();

  // Receptor IR sin LED de feedback para evitar conflicto con D13
  IrReceiver.begin(PIN_IR);

  lcd.setCursor(0, 0);
  lcd.print("ACME Ascensor");
  lcd.setCursor(0, 1);
  lcd.print("Test actuadores");

  pruebaInicialRGB();
  pruebaInicialLedLuz();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ACME Ascensor");
  lcd.setCursor(0, 1);
  lcd.print("Inicializando");

  delay(2500);

  leerDHT22Seguro();

  luzMedida = leerLuzPorcentaje();
  presenciaUsuario = digitalRead(PIN_PIR);

  ultimaLecturaDHT = millis();

  mostrarRGBReposo();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistema listo");

  lcd.setCursor(0, 1);
  if (dhtDisponible) {
    lcd.print("DHT22 OK");
  } else {
    lcd.print("DHT pendiente");
  }

  Serial.println("Planta_Actual,Planta_Destino,Presencia,Temp_DHT(C),Humedad(%),Temp_Control(C),Luz(%),Accion_Temp,PWM_Luz,Estado_DHT");

  delay(1500);
  lcd.clear();
}

// ======================================================
//                          LOOP
// ======================================================

void loop() {
  comprobarBotones();
  comprobarMandoIR();

  unsigned long ahora = millis();

  if (ahora - ultimoControl >= INTERVALO_CONTROL) {
    ultimoControl = ahora;

    leerSensores();
    controlarTemperatura();
    controlarIluminacion();
  }

  if (ahora - ultimoLCD >= INTERVALO_LCD) {
    ultimoLCD = ahora;
    mostrarLCD();
  }

  if (ahora - ultimoLog >= INTERVALO_LOG) {
    ultimoLog = ahora;
    enviarLogSerie();
  }
}