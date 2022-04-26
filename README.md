## Protocolo para los laboratorios de Sistemas Digitales

#### Json a enviar 
	
	{
	"Estado": [ 0, true, false],
	"Pulsadores": [ false,	false,	false,	false	],
	"Indicadores": [	false,	false,	false,	false	],
	"Serial": "Mensaje serial"
	}

**Sintaxis**
#### Estado: [Laboratorio, SubLab, Inicio del experimento]

|Laboratorio  | Sub Laboratorio  | Estado del Experimento |
| ------------ | ------------ | ------------ |
| 0  | true  | Sistemas Digitales: UART  |
| 0  | false  | Sistemas Digitales: I2C  |

#### Inicio del experimento:

- true: Inicia el experimento
- false: Finaliza el experimento

#### Serial

Es un string con un tamaño maximo de 100 caracteres.


### Elementos por Laboratorio
**Sistemas digitales**

- Ambos Laboratorios
  - Pulsadores: [Pulsador1, Pulsador2,Pulsador3,Pulsador4 ]
  - Llaves:  [Llave1, Llave2, Llave3, Llave4]

**Esquematico general**
### Diagrama:
![Cyclone II](Imagenes\Esquematico.png)

**Arduino Mega**
### PIN OUT

 ![alt text](https://diyi0t.com/wp-content/uploads/2019/08/Arduino-Mega-Pinout.png) 


**FPGA Cyclone II**

Nombre: Altera_FPGA_Board_EP2C8Q208C8 Cyclone II

![Cyclone II](Imagenes\cyclone-ii.png)

**FPGA Cyclone IV**

Nombre: Altera_FPGA_Board_EP4CE6E22C8
Cyclone IV
![Cyclone IV](Imagenes\cyclone-iv.png)
