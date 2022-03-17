En este repositorio se realizarán los cambios a tener en cuenta para el avance de los lab remotos.


Json a enviar 
{
  "Estado": [
    0,
    true,
    false
  ],
  "Pulsadores": [
    false,
    false,
    false,
    false
  ],
  "Llaves": [
    false,
    false,
    false,
    false
  ],
  "Analogico": [
    1,
    0,
    125,
    542
  ]
}

//Estado: [Laboratorio, SubLab, Inicio del experimento]
Laboratorio:
    0 = Sistemas Digitales
    SubLab:
        true = UART
            Elementos: 
                [Pulsador1, Pulsador2,Pulsador3,Pulsador4 ]
                [Llave1, Llave2, Llave3, Llave4]
        false = I2C
            Elementos: 
                [Pulsador1, Pulsador2,Pulsador3,Pulsador4]
                [Llave1, Llave2, Llave3, Llave4]   
    1 = Sistemas de Control
    SubLab: 
        true = Aliassing
            Elementos: 
                [Llave1, Llave2]
                [Analogico1,Analogico2]
        false = Control automatico de posición
            Elementos: 
                [Analogico1,Analogico2,Analogico3,Analogico4]
    2 = Telecomunicaciones
    SubLab:
        true = WIFI 2.4
            Elementos: 
                [Analogico1,Analogico2]
        false = Enlace de Radio por soft 
            Elementos: 
               [Analogico1,Analogico2,Analogico3,Analogico4] // Revisar
    3 = Fisica Basica
    SubLab:
        true = Convergente
            Elementos: 
            [Pulsador1]
            [Llave1]
            [Analogico1,Analogico2]
        false = Divergente
            Elementos: 
            [Pulsador1]
            [Llave1]
            [Analogico1,Analogico2,Analogico3]
            
//Pulsadores: [Pulsador1, Pulsador2,Pulsador3,Pulsador4 ]

//"Llaves":  [Llave1, Llave2, Llave3, Llave4]

//"Analogico": [Analogico1,Analogico2,Analogico3,Analogico4]