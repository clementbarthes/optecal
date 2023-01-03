# OpteCAL
### Digital Image Correlation Software for Conventional Cameras

Optecal, Copyright &copy; 2023 Clement B. Barthes
OpteCAL is distributed for free under GNU General Public License, version 3
    

If you modify OpteCAL source and made your changes public, you should accept
the license and credit the author. Furthermore, if you use OpteCAL to publish 
in a journal you should cite OpteCAL as such:
```
C. Barthes (2023). OpteCAL, Digital Image Correlation Software. 
Available: https://optecal.com
```


# Build Instructions (Windows only)
### Tools
Make sure that you install them in this order to avoid any issue.
* [Visual Studio Community 2019 (not 2022)](https://visualstudio.microsoft.com/vs/older-downloads/)
* [Qt6 Community Edition](https://www.qt.io/product/qt6)
* [CMake](https://cmake.org/download/)

### Libraries
* [OpenCV](https://github.com/opencv/opencv)
* [LibRAW](https://www.libraw.org/download)
* [Lensfun](https://lensfun.github.io/)
* [Matlab External DLL](https://www.mathworks.com/products/compiler/matlab-runtime.html)

### OpenCV build and configure
Using CMake GUI, click on 'Browse Source...' and open OpenCV root folder. Open 
'Browse Build...' and choose the build target folder. I recommend using a folder called 'build' inside the OpenCV folder.
Click on 'Configure', choose Visual Studio 16 2019, keep everything else as default and click 'Finish'.
In the list of arguments, look for 'WITH_QT' and activate it. Next. click on 'Generate'.
At this point, you now have a Visual Studio solution file ready to be built, but you have not compiled any library yet. In your build folder, open 'OpenCV.sln' with MSVC2019. 
Select Debug configuration, in the Solution Explorer, under CMakeTargets, right click on ALL_BUILD and click 'Compile'. Next, right click on INSTALL and click 'Compile'. When done, select the Release configuration and perform the same operations. You will find the header files, the lib files and the dll files in the 'install' subfolder.
### Libraw
Using MSVC2019, open 'Libraw.sln'. In the solution explorer, right click on the solution and select 'Build Solution...'. Make sure that you perform this operation for the Debug and the Release configurations.
### Lensfun
To add the lensfun database to the project, you need to pull the [lensfun](https://github.com/lensfun/lensfun) repo, go to the 'lensfun/data/db' sub-directory, copy all the XML files, and paste them in a folder called 'lensfundb', in the same directory than your executable. Make sure that you copy this folder in the debug and release Qt build folders if you need this library while developing. OpteCAL will load up the files at runtime.
### Matlab
Download and install the R2014b version of the [Matlab Runtime](https://www.mathworks.com/products/compiler/matlab-runtime.html). Once installed, go to v84/extern to find the '.h' files and the '.lib' files. The DLL files are located in v84/bin/win64.
OpteCAL still relies on this old implementation. I will try to update it in the release but for what it does it works fine. Its only purpose is to allow the user to save the results as '.mat' files.
### Qt Configuration
In Qt Creator, select optecal.pro file to open the project. In optecal.pro, replace the 
LIBSDIR variable with your libs path. Also check the INCLUDEPATH and LIBS variables at the bottom of the file, and make sure that they point to your libraries directories.
I recommend avoiding path with spaces and special characters (Such as 'Program Files'). These filepath sometimes cause compile errors that are hard to debug.
On the left pane, click on the Projects icon, then click on Run to edit the Run Configuration. In the Environment list, select PATH and make sure that it includes the path to all external DLL libraries (OpenCV DLL path).
