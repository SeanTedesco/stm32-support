# stm32-support
This repository contains a basic project template and library to provide basic communication across UART, I2C, and SPI protocols.

## Setup in STM32CubeIDE

1. Change into the STM32CubeIDE project, for example:
```
cd /Users/seantedesco/STM32CubeIDE/workspace_1.10.1/nucleo-f411re-radio-controller/ 
```

1. Clone the Repository into the repository
```
git clone https://github.com/SeanTedesco/stm32-support.git
```

1. Open up STM32CubeIDE and navigate to the desired 

1. Include paths into the project properties. 
a. Navigate to *Project > Properties > C/C++ General > Paths and Symbols*
b. Select *Include*, *GNU C* and *Add...*
c. Select *Is a workspace path* and *Workspace...* and include the path to the program/Inc, communication/Inc, and any other folder as desired. 
d. Repeat for b. and c. *Include*, *GNU C++*, and *Add...* 
e. Move over to *Source Location* Tab, and select *Add Folder...* and add the paths to the program/Src, communication/Src, and any other folder as desired. 
f. Select *Apply and Close*

1. Modify the main.c folder
a. Include the header file for our main program.
```
/* USER CODE BEGIN Includes */
	#include "cppmain.h"
/* USER CODE END Includes */
```

b. Call our main function
```
/* USER CODE BEGIN 2 */
	cpp_main();
/* USER CODE END 2 */
```
