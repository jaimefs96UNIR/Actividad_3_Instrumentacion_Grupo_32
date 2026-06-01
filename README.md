# 🧠 Actividad 3 – Equipos e Instrumentación Electrónica  
Repositorio del Proyecto del Grupo 32 de Equipamiento e Instrumentación Electrónica del Máster en Telecomunicaciones de UNIR. Implementación, simulación y documentación del sistema de control remoto IR para el ascensor inteligente ACME.

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
La mejora permite ajustar variables de control sin modificar físicamente el circuito, convirtiendo el mando IR en un elemento de supervisión y parametrización remota. El sistema mantiene compatibilidad con versiones anteriores y no requiere sustituir sensores ni actuadores.

**Componentes principales:**

- **Microcontrolador Arduino Uno**: Encargado del procesamiento y control general.
  
- **Receptor IR**: Recibe las órdenes remotas enviadas por el mando infrarrojo para la selección de plantas y la modificación de parámetros de funcionamiento.
  
- **Fotorresistor LDR**: Conectado a una entrada analógica del Arduino, permite determinar el nivel de iluminación existente en el entorno.
  
- **Sensor digital de humedad y temperatura DHT22**: Conectado al pin digital D3, proporciona las medidas de temperatura y humedad utilizadas por el sistema de control ambiental.
  
- **Sensor de movimiento PIR**: Permite detectar la presencia de personas en las proximidades del ascensor, activando determinadas funciones de iluminación y operación.
  
- **Servomotor**: Conectado al pin PWM correspondiente, simula el desplazamiento del ascensor entre las diferentes plantas.
  
- **Monitor LCD 16x2 (IC2)**: Conectada mediante el bus I2C (SDA y SCL), muestra información relativa a la planta actual, temperatura, humedad y mensajes generados por el sistema.
  
- **Pulsadores táctiles 12mm**: Los pulsadores permiten seleccionar manualmente la planta de destino cuando no se utiliza el mando a distancia.
  
- **LED RGB**: Indica visualmente el estado ambiental mediante distintos colores asociados a las condiciones de funcionamiento.
  
- **LED de iluminación**: Representa el sistema de iluminación controlado automáticamente según las condiciones detectadas por los sensores. 

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

## 🛠️ Integración de la mejora
La incorporación del receptor infrarrojo se ha realizado sin modificar la arquitectura principal del sistema. El nuevo dispositivo se conecta al pin digital D2 del Arduino y permite recibir órdenes procedentes del mando a distancia. De esta forma, el usuario dispone de una segunda vía de interacción además de los pulsadores físicos ya existentes. 

La integración se ha llevado a cabo garantizando la compatibilidad con todas las funciones desarrolladas anteriormente. Los pulsadores continúan permitiendo la selección manual de plantas, mientras que el mando IR añade la posibilidad de realizar las mismas acciones de forma remota. Además, se incorporan nuevas funciones relacionadas con la modificación de parámetros de funcionamiento, como los valores de referencia utilizados por los sistemas de control ambiental. 

El algoritmo de control de temperatura mantiene su estructura ON-OFF con zona muerta, mientras que el sistema de iluminación continúa utilizando la información proporcionada por el sensor LDR para adaptar el funcionamiento del alumbrado. La mejora implementada permite modificar las consignas de funcionamiento sin necesidad de acceder físicamente al circuito ni alterar el código fuente. 

La pantalla LCD sigue desempeñando la función de interfaz hombre-máquina local, mostrando la planta seleccionada, las variables ambientales y los cambios realizados mediante el mando a distancia. Del mismo modo, el monitor serie registra los eventos generados por el sistema, facilitando la supervisión y la verificación del funcionamiento. 

Gracias a esta integración se obtiene un sistema más flexible y cómodo de utilizar, manteniendo la estructura original del ascensor inteligente ACME e incorporando capacidades adicionales de interacción remota que mejoran las prestaciones globales de la instalación. 

---
## ▶️ Ejecución (BORRADOR)
Explica cómo iniciar el sistema, qué se debe ver, etc.

---

## 🧪 Pruebas realizadas (BORRADOR)
A continuación, se detallan algunas de las pruebas realizadas una vez implementadas las nuevas funcionalidades. En la sección de capturas pueden observarse los resultados de dichas pruebas. En total, se han realizado las siguientes pruebas:

- **Ajuste manual de temperatura y humedad**: se ajusta manualmente la temperatura y humedad en el sensor DHT22. Al hacerlo, se comprueba que el LED de enfriado/calentado/reposo cambia de color. Además, gracias al log del serial, es posible ver que las actualizaciones se realizan de manera correcta.
  
- **Ajuste manual de iluminación**: se ajusta manualmente la iluminación en el fotoresistor LDR. Se comprueba que aumenta o disminuye su intensidad, llegando incluso a apagarse, cuando se realizan variaciones en la temeratura.

- **Introducción de llamadas de ascensor con mando**: se observa que el sistema responde correctamente a las llamadas realizadas desde los pulsadores. Se observa, además, el movimiento correcto del servomotor.
  
- **Introducción de llamadas de ascensor con botones**: se observa que el sistema responde correctamente a las llamadas realizadas desde los pulsadores. Se observa, además, el movimiento correcto del servomotor.
  
- **Activación de iluminación manual**: al activar la iluminación manual, es posible ajustar la intensidad de la luz, incluso apagar el led, desde el mando, independientemente de la iluminación exterior, pero con limitaciones. Si se desactiva el modo manual estando la iluminación baja, no se aprecia la diferencia ni el paso de un modo a otro, ya que el led se queda activado.
  
- **Activación de control de enfriador/calentador manual**: al activar el modo manual, es posible calentar/enfriar independientemente de la tempertura externa, accionando los botones correspondientes. Con limitaciones eso si, es necesario ajustar los botones para incluir funcionalidades, ya que sólo quedaban tres botones numñericos disponibles para cuatro estados. No era posible tener un estado de apagado y otro de reposo.

- **Detección de objetos cerca del ascensor**: se comprueba que, ajustando manualmente el sensor de detección, el ascensor queda bloqueado si se detecta un objeto ficticio a 20cm o menos.

---

## 📸 Capturas (BORRADOR)

- **Ajuste manual de temperatura y humedad**:
- **Ajuste manual de iluminación**:
- **Introducción de llamadas de ascensor con mando**:
- **Introducción de llamadas de ascensor con botones**:
- **Activación de iluminación manual**:
- **Activación de control de enfriador/calentador manual**:
- **Detección de objetos cerca del ascensor**:


---

## ⚠️ Problemas encontrados (BORRADOR)
- Dificultad con el control del stepper  
- Ajuste de tiempos en el sensor  
- Integración con el módulo X

---

## 🚀 Mejoras futuras (BORRADOR)
- Integración de control PID para mayor precisión.  
- Implementación de interfaz gráfica para supervisión remota.  
- Optimización del código para reducir latencia en la comunicación IR.

---

## 🔗 Enlace a la simulación en Wokwi
Puedes acceder a la simulación completa del proyecto en el siguiente enlace:

👉 Fase inicial: 

👉 Fase final: https://wokwi.com/projects/465656832774518785

---

## 👥 Autores
**Grupo 32 – UNIR**  
- María Fernández Maíso
- Jaime Fernández Sánchez  
- Laura Gállego Ortega
- Pablo García López
- Alfredo García Martín


