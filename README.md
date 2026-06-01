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

## 🧩 Descripción técnica
La mejora permite ajustar variables de control sin modificar físicamente el circuito, convirtiendo el mando IR en un elemento de supervisión y parametrización remota.  
El sistema mantiene compatibilidad con versiones anteriores y no requiere sustituir sensores ni actuadores.

**Componentes principales:**
- *Microcontrolador Arduino Uno*: Encargado del procesamiento y control general.
- *Receptor IR*: Recibe las órdenes remotas enviadas por el mando infrarrojo para la selección de plantas y la modificación de parámetros de funcionamiento. 
- *Fotorresistor LDR*: Conectado a una entrada analógica del Arduino, permite determinar el nivel de iluminación existente en el entorno. 
- *Sensor digital de humedad y temperatura DHT22*: Conectado al pin digital D3, proporciona las medidas de temperatura y humedad utilizadas por el sistema de control ambiental.  
- *Sensor de movimiento PIR*: Permite detectar la presencia de personas en las proximidades del ascensor, activando determinadas funciones de iluminación y operación.  
- *Servomotor*: Conectado al pin PWM correspondiente, simula el desplazamiento del ascensor entre las diferentes plantas.  
- *Monitor LCD 16x2 (IC2)*: Conectada mediante el bus I2C (SDA y SCL), muestra información relativa a la planta actual, temperatura, humedad y mensajes generados por el sistema.  
- *Pulsadores táctiles 12mm*: Los pulsadores permiten seleccionar manualmente la planta de destino cuando no se utiliza el mando a distancia.  
- *LED RGB*: Indica visualmente el estado ambiental mediante distintos colores asociados a las condiciones de funcionamiento.
- *LED de iluminación*: Representa el sistema de iluminación controlado automáticamente según las condiciones detectadas por los sensores. 

---

## 🛠️ Integración de la mejora (BORRADOR)
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

## ⚙️ Justificación de la mejora aplicada y valor añadido

Se ha elegido la variante de control remoto IR por tres motivos principales. En primer lugar, se trata de una tecnología ya integrada parcialmente en la Actividad 2, por lo que su incorporación avanzada requiere una adaptación progresiva del sistema y no un rediseño completo del montaje. 

En segundo lugar, el uso del mando IR permite mejorar la ergonomía del sistema, ya que el usuario puede modificar parámetros sin interactuar físicamente con el circuito. Por último, esta solución se ajusta a la filosofía de instrumentación avanzada descrita en la actividad, donde se busca perfeccionar el sistema de medición, control, actuación y presentación mediante técnicas modernas de interacción. 

Frente a otras alternativas, como la comunicación Bluetooth o la lógica fuzzy, el control remoto por infrarrojos presenta una implementación más directa en Wokwi y evita la necesidad de incorporar módulos adicionales. La lógica fuzzy se considera una opción interesante para una evolución futura, pero en esta actividad se ha priorizado una mejora funcional, estable y coherente con el sistema ya construido. El autodiagnóstico también podría aportar fiabilidad adicional, pero se ha decidido reservarlo como posible ampliación posterior, ya que el sistema ya incluye una lectura robusta del DHT22 mediante conservación de la última medida válida. 

Por tanto, la variante seleccionada permite mejorar el sistema manteniendo una complejidad razonable, aprovechando componentes ya presentes y reforzando el carácter remoto e interactivo del ascensor inteligente. 


La mejora mediante control remoto IR aporta una evolución clara respecto a la Actividad 2. En la versión anterior, el mando a distancia se utilizaba únicamente para seleccionar la planta de destino. En esta nueva fase, el mando se convierte en un elemento de supervisión y parametrización remota, permitiendo ajustar variables de control sin modificar físicamente el circuito. 

Esta mejora incrementa la ergonomía del sistema, ya que permite actuar sobre el ascensor desde el exterior. También mejora la flexibilidad, puesto que los valores de consigna pueden adaptarse a diferentes condiciones ambientales o necesidades de uso. Además, mantiene la compatibilidad con el sistema existente, ya que no requiere sustituir sensores ni actuadores. 

En resumen, la variante seleccionada permite perfeccionar el ascensor inteligente ACME mediante una funcionalidad sencilla, estable y directamente relacionada con la instrumentación avanzada: la modificación remota de parámetros de control. Esta solución mantiene la estructura de medición, control, actuación y visualización ya desarrollada, pero añade una capa adicional de interacción remota que mejora el valor funcional del sistema.

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

