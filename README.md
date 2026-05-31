# 🧠 Actividad 3 – Equipos e Instrumentación Electrónica  
(BORRADOR)Proyecto grupal de la UNIR (Grupo 32). Implementación, simulación y documentación del sistema de control remoto IR para el ascensor inteligente ACME.

---

## 📘 Introducción
Este proyecto corresponde a la Actividad 3 de la asignatura Equipos e Instrumentación Electrónica (UNIR). El objetivo principal es implementar una mejora funcional basada en control remoto por infrarrojos (IR), permitiendo ajustar consignas del sistema sin modificar físicamente el circuito. El repositorio recoge el código, las pruebas realizadas y la documentación técnica del Grupo 32.

---

## 🎯 Objetivos
- Desarrollar la mejora funcional propuesta (control remoto mediante infrarrojos) sobre el diseño planteado en la Actividad 2.
- Registrar y validar las órdenes enviadas desde el mando y su correcta aplicación.
- Desarollar diferentes pruebas para garantizar el correcto funcionamiento, así como detectar los posibles problemas, de dicha mejora.
- Documentar el valor añadido de la mejora y su impacto en la ergonomía y flexibilidad del sistema.

---

## 🧩 Descripción técnica (BORRADOR)
La mejora permite ajustar variables de control sin modificar físicamente el circuito, convirtiendo el mando IR en un elemento de supervisión y parametrización remota.  
El sistema mantiene compatibilidad con versiones anteriores y no requiere sustituir sensores ni actuadores.

**Componentes principales:**
- Microcontrolador Arduino Uno
- Sensor IR y receptor
- Fotorresistor LDR
- Sensor digital de humedad y temperatura DHT22
- Sensor de movimiento PIR
- Servomotor
- Monitor LCD 16x2 (IC2)
- Botones táctiles 12mm
- LEDs
- Resistencias

---

## 🛠️ Instalación (BORRADOR)
1. Clona el repositorio  
2. Abre el proyecto en VSCode / Arduino IDE  
3. Ejecuta en Wokwi o carga en la placa real

## ▶️ Ejecución (BORRADOR)
Explica cómo iniciar el sistema, qué se debe ver, etc.

---

## 🧪 Pruebas realizadas (BORRADOR)
- Modificación de temperatura de referencia: `Nuevo Tset: 26°C`  
- Ajuste de consigna de iluminación: `Nuevo Lset: 75%`  
- Verificación de recepción y aplicación de órdenes en el monitor serie.

---

## ⚠️ Problemas encontrados (BORRADOR)
- Dificultad con el control del stepper  
- Ajuste de tiempos en el sensor  
- Integración con el módulo X

---

## ⚙️ Justificación de la mejora aplicada y valor añadido (BORRADOR)
La mejora incrementa la **ergonomía** y **flexibilidad** del sistema, permitiendo actuar sobre el ascensor desde el exterior y adaptarse a diferentes condiciones ambientales o necesidades de uso.

---

## 🚀 Mejoras futuras (BORRADOR)
- Integración de control PID para mayor precisión.  
- Implementación de interfaz gráfica para supervisión remota.  
- Optimización del código para reducir latencia en la comunicación IR.

---

## 👥 Autores
**Grupo 32 – UNIR**  
- María Fernández Maíso
- Jaime Fernández Sánchez  
- Laura Gállego Ortega
- Pablo García López
- Alfredo García Martín
---

## 📸 Capturas (BORRADOR)

