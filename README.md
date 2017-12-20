# README

## Needed dependencies:
[SFML v2.0 32bit or higher](http://www.sfml-dev.org/)
[FMODEXAPI v4](http://www.fmod.org/download-previous-products/)
[FMODAPI v1.7](http://www.fmod.org/download/)

Make sure you install them to:
C:\Program Files (x86)\SFML-2.3.2\library; C:\Program Files (x86)\FMOD SoundSystem\FMOD Programmers API Windows\lib; C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\lowlevel\lib;

Alternative, change the project C++ General and Linker path to wherever you installed your APIs.


If you need to create a new solution, you'll have to set your projects:
1. Right click on Project > Properties
2. Make sure Configuration is set to All Configurations
3. on C/C++, Additional Include Directories, type:
```
C:\Program Files (x86)\SFML-2.3.2\include; 
C:\Program Files (x86)\FMOD SoundSystem\FMOD Programmers API Windows\api\inc; 
C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\lowlevel\inc;
```
4. on Linker, Additional Library Directories, type:
```
C:\Program Files (x86)\SFML-2.3.2\lib; 
C:\Program Files (x86)\FMOD SoundSystem\FMOD Programmers API Windows\api\lib; 
C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\lowlevel\lib;
```
5. On Build Events > Post-Build Event, command line, type:
```
start xcopy /y "C:\Program Files (x86)\FMOD SoundSystem\FMOD Programmers API Windows\api\fmodex.dll" "$(OutDir)"
start xcopy /y "C:\Program Files (x86)\SFML-2.3.2\bin\*" "$(OutDir)"
start xcopy /y "$(SolutionDir)Resources\*" "$(OutDir)"
```
6. On Linker > Input, with Configuration set to Debug, type into Additional Dependencies:
`sfml-graphics-d.lib;sfml-system-d.lib;sfml-window-d.lib;fmodex_vc.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)`
7. On Linker > Input, with Configuration set to Release, type into Additional Dependencies:
`sfml-graphics.lib;sfml-system.lib;sfml-window.lib;fmodex_vc.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)`