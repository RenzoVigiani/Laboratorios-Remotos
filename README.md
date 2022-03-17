En este repositorio se realizarán los cambios a tener en cuenta para el avance de los lab remotos.


Json a enviar 
{
  "Estado": [0,"LOW","HIGH"], 
  "Pulsadores": ["LOW",    "LOW",    "LOW",    "LOW"],
  "Llaves": ["LOW",    "LOW",    "LOW",    "LOW",    "LOW"  ],
  "Analogico": [ 1,    0, 125, 542  ] 
}

//Estado: [Laboratorio, SubLab, Inicio del experimento]
Laboratorio:
    0 = Sistemas Digitales
    SubLab:
        HIGH = UART
            Elementos: 
                [Pulsador1, Pulsador2,Pulsador3,Pulsador4 ]
                [Llave1, Llave2, Llave3, Llave4]
        LOW = I2C
            Elementos: 
                [Pulsador1, Pulsador2,Pulsador3,Pulsador4]
                [Llave1, Llave2, Llave3, Llave4]   
    1 = Sistemas de Control
    SubLab: 
        HIGH = Aliassing
            Elementos: 
                [Llave1, Llave2]
                [Analogico1,Analogico2]
        LOW = Control automatico de posición
            Elementos: 
                [Analogico1,Analogico2,Analogico3,Analogico4]
    2 = Telecomunicaciones
    SubLab:
        HIGH = WIFI 2.4
            Elementos: 
                [Analogico1,Analogico2]
        LOW = Enlace de Radio por soft 
            Elementos: 
               [Analogico1,Analogico2,Analogico3,Analogico4] // Revisar
    3 = Fisica Basica
    SubLab:
        HIGH = Convergente
            Elementos: 
            [Pulsador1]
            [Llave1]
            [Analogico1,Analogico2]
        LOW = Divergente
            Elementos: 
            [Pulsador1]
            [Llave1]
            [Analogico1,Analogico2,Analogico3]

            
//Pulsadores: [Pulsador1, Pulsador2,Pulsador3,Pulsador4 ]

//"Llaves":  [Llave1, Llave2, Llave3, Llave4]

//"Analogico": [Analogico1,Analogico2,Analogico3,Analogico4]