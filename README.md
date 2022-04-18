# Bar-code:
This repo contains the code to convert entered text to bar code(128B) and decrypt it back to the original message. This was a part of our first semester programming project.
To build just make sure you include stbi libraries too.

## To compile the code:
You can just type .\build.bat in the terminal (for gcc) or just open the build.bat file and it should create an exe file with the name BarCode.exe  
```build.bat```  
**If this doesn't work, you can do the following:**  
Change directory of terminal to the folder containing the source code and type:  
 ```gcc entry.c makeBars.c readBars.c -o Barcode```

## Contributors:
- [Ishwor](https://github.com/optimistic-ish)
- [Bipul](https://github.com/bipul018)
- [Himansu](https://github.com/itmaybehimm)
- [Mamta](https://github.com/Mamata-Maharjan)

## Files info:

#### barcode.h:
	This file contains important values required for both reading and writing bar codes like reference codes.

#### barcodeio.h:
	This file contains only two function declaration needed for writing and reading bar code.

#### stb_image.h:
	External tool needed to read image files.
	We have used only one function stbi_load()
	Make sure to include this file with STB_IMAGE_IMPLEMENTATION defined to include definitions of functions.

#### stb_image_write.h:
	External tool needed to write image files.
	We have used only one function stbi_write_jpg()
	Make sure to include this file with STB_IMAGE_WRITE_IMPLEMENTATION defined to include definitions of functions.

#### makeBars.c:
	This is source file containing algorithms for creating bar code from given message.

#### readBars.c:
	This is source file containing algorithms for reading message from given image file of barcode.
	Currently, it may not work if you have images of other objects too along with barcode.

#### entry.c:
	This source file contains the main() function and binds all other codes.

**Any advice to improve the codes is appreciated. Thank you!!**
