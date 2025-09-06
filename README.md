# 🧠 PHILOSOPHERS

**Dominando la concurrencia, inspirando innovación, elevando soluciones**

Simulación del clásico problema de los filósofos comensales, con enfoque en concurrencia, sincronización y gestión de recursos. Ideal para demostrar habilidades en programación multihilo y estructuras de bajo nivel.

---

## 📚 Tabla de Contenidos

- [Descripción General](#descripción-general)
- [Primeros Pasos](#primeros-pasos)
- [Requisitos](#requisitos)
- [Instalación](#instalación)
- [Uso](#uso)
- [Pruebas](#pruebas)
- [Características Clave](#características-clave)
- [Licencia](#licencia)

---

## 🧩 Descripción General

**Philosophers** es una herramienta educativa y técnica que permite explorar escenarios complejos de sincronización entre hilos. Simula el comportamiento de filósofos que comparten recursos (tenedores) y deben coordinarse para evitar condiciones de carrera y bloqueos.

---

## 🚀 Primeros Pasos

Este proyecto está escrito en **C** y utiliza **Make** para la automatización de compilación y ejecución.

---

## 📦 Requisitos

Asegúrate de tener instalado lo siguiente:

- Lenguaje: `C`
- Gestor de compilación: `make`

---

## 🛠️ Instalación

Clona el repositorio y compila el proyecto:

```bash
git clone https://github.com/Escudo5/Philosophers
cd Philosophers
make
```
## Uso

Ejecuta el programa con los siguientes argumentos: 

- n_filosofos: Número de filósofos (máximo 200)

- tiempo_muerte: Tiempo en milisegundos antes de que un filósofo muera si no come

- tiempo_comer: Tiempo que tarda en comer

- tiempo_dormir: Tiempo que tarda en dormir

- limite_comidas (opcional): Número de veces que cada filósofo debe comer

Ejemplo: 


```bash 
./philo "5 800 200 200 3"
```

## ✨ Características Clave
🧩 Automatización de Compilación: Uso de Makefile para compilar y gestionar dependencias.

🛠️ Estructuras de Datos: Definición clara de entidades y mecanismos de sincronización.

🔄 Gestión del Ciclo de Vida: Coordinación de hilos, limpieza de recursos y control de estados.

🕰️ Funciones de Temporización: Precisión en tiempos, validación de entrada y manejo de errores.

📝 Registro Sincronizado: Salida clara con timestamps para facilitar el análisis y depuración.




---

# English Version

# 🧠 PHILOSOPHERS
**Mastering concurrency, inspiring innovation, elevating solutions**

Simulation of the classic dining philosophers problem, focused on concurrency, synchronization, and resource management. Perfect for showcasing skills in multithreaded programming and low-level systems design.

## 📚 Table of Contents

- [Overview](#overview)
- [Getting Started](#getting-tarted)
- [Requirements](#requirements)
- [Installation](#Installation)
- [Usage](#usage)
- [Test](#test)
- [Core Features](#core-features)


## 🧩 Overview
Philosophers is an educational and technical tool that explores complex thread synchronization scenarios. It simulates philosophers sharing resources (forks) and coordinating to avoid race conditions and deadlocks.

## 🚀 Getting Started
This project is written in C and uses Make for build automation and execution.

## 📦 Requirements
Make sure you have the following installed:

Language: C

Build tool: make

## 🛠️ Installation
Clone the repository and compile the project:

bash
git clone https://github.com/Escudo5/Philosophers
cd Philosophers
make
## ▶️ Usage
Run the program with the following arguments:

n_philosophers: Number of philosophers (maximum 200)

time_to_die: Time in milliseconds before a philosopher dies if they don't eat

time_to_eat: Time it takes to eat

time_to_sleep: Time it takes to sleep

meals_limit (optional): Number of times each philosopher must eat

Example:

```bash
./philo "5 800 200 200 3"
```
## ✨ Core Features
🧩 Build Automation: Uses Makefile to compile and manage dependencies.

🛠️ Data Structures: Clear definition of entities and synchronization mechanisms.

🔄 Lifecycle Management: Thread coordination, resource cleanup, and state control.

🕰️ Timing Functions: Accurate timing, input validation, and error handling.

📝 Synchronized Logging: Clear output with timestamps for easier analysis and debugging.
