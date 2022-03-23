## Protocolo

En este repositorio se realizarán los cambios a tener en cuenta para el avance de los lab remotos.

#### Json a enviar (Indented style)

{
 "Estado": [ 0, true, false],
 "Pulsadores": [ false, false, false, false ],
 "Llaves": [ false, false, false, false ],
 "Analogico": [ 1, 0, 125, 542 ]
}

**Sintaxis**
#### Estado: [Laboratorio, SubLab, Inicio del experimento]

|Laboratorio  | Sub Laboratorio  | Estado del Experimento |
| ------------ | ------------ | ------------ |
| 0  | true  | Sistemas Digitales: UART  |
| 0  | false  | Sistemas Digitales: I2C  |
| 1  | true  |  Sistemas de control: Aliassing |
| 1  | false  | Sistemas de control: Control automatico de posición |
| 2  | true  |  Telecomunicaciones: Wifi 2.4G |
| 2  | false  | Telecomunicaciones: Enlace de Radio por soft |
| 3  | true  | Fisica Basica: Lente Convergente  |
| 3  | false  | Fisica Basica: Lente Divergente  |

**Inicio del experimento:**

- true: Inicia el experimento
- false: Finaliza el experimento

#### Elementos por Laboratorio
**Sistemas digitales**

- Ambos Laboratorios
  - Pulsadores: [Pulsador1, Pulsador2,Pulsador3,Pulsador4 ]
  - Llaves:  [Llave1, Llave2, Llave3, Llave4]

**Sistemas de control**

- Aliassing
  - Llaves:  [Llave1, Llave2]
  - Analogico: [Analogico1,Analogico2]
- Control automatico de posición
  - Analogico: [Analogico1,Analogico2,Analogico3,Analogico4]

**Telecomunicaciones**

- WIFI 2.4
  - Analogico: [Analogico1,Analogico2]
- Enlace de Radio por soft
  - Analogico: [Analogico1,Analogico2,Analogico3,Analogico4] // Revisar
**Fisica Basica**
- Convergente
  - Pulsadores:[Pulsador1]
  - Llaves:[Llave1]
  - Analogico:[Analogico1,Analogico2]
- Divergente
  - Pulsadores:[Pulsador1]
  - Llaves:[Llave1]
  - Analogico:[Analogico1,Analogico2,Analogico3]
**
Pulsadores: [Pulsador1, Pulsador2,Pulsador3,Pulsador4 ]
Llaves:  [Llave1, Llave2, Llave3, Llave4]
Analogico: [Analogico1,Analogico2,Analogico3,Analogico4]
**
