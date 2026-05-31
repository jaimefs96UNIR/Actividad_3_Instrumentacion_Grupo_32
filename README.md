# 🧠 Actividad 3 – Equipos e Instrumentación Electrónica  
Proyecto grupal de la UNIR (Grupo 32). Implementación, simulación y documentación del sistema de control remoto IR para el ascensor inteligente ACME.

---

## 🎯 Objetivos
- Desarrollar una mejora funcional respecto a la Actividad 2 mediante control remoto IR.  
- Registrar y validar las órdenes enviadas desde el mando y su correcta aplicación.  
- Documentar el valor añadido de la mejora y su impacto en la ergonomía y flexibilidad del sistema.

---

## 🧩 Descripción técnica
La mejora permite ajustar variables de control sin modificar físicamente el circuito, convirtiendo el mando IR en un elemento de supervisión y parametrización remota.  
El sistema mantiene compatibilidad con versiones anteriores y no requiere sustituir sensores ni actuadores.

**Componentes principales:**
- Microcontrolador: ESP32  
- Sensor IR y receptor  
- LCD para visualización de consignas  
- Monitor serie para registro de cambios  

---

## 🛠️ Instalación
1. Clona el repositorio  
2. Abre el proyecto en VSCode / Arduino IDE  
3. Ejecuta en Wokwi o carga en la placa real

## ▶️ Ejecución
Explica cómo iniciar el sistema, qué se debe ver, etc.

---

## 🧪 Pruebas realizadas
- Modificación de temperatura de referencia: `Nuevo Tset: 26°C`  
- Ajuste de consigna de iluminación: `Nuevo Lset: 75%`  
- Verificación de recepción y aplicación de órdenes en el monitor serie.

---

## 📸 Resultados
![Simulación en Wokwi](ruta/a/imagen.png)

---

## ⚠️ Problemas encontrados
- Dificultad con el control del stepper  
- Ajuste de tiempos en el sensor  
- Integración con el módulo X

---

## ⚙️ Justificación de la mejora aplicada
La mejora incrementa la **ergonomía** y **flexibilidad** del sistema, permitiendo actuar sobre el ascensor desde el exterior y adaptarse a diferentes condiciones ambientales o necesidades de uso.

---

## 🚀 Mejoras futuras
- Integración de control PID para mayor precisión.  
- Implementación de interfaz gráfica para supervisión remota.  
- Optimización del código para reducir latencia en la comunicación IR.

---

## 👥 Autores
**Grupo 32 – UNIR**  
- Jaime Fernández Sánchez  
- [Otros integrantes del grupo]

---

## 📸 Capturas
*(Agrega aquí imágenes del circuito o simulación en Wokwi)*  

