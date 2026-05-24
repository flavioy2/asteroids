# AsteroidsGL

Juego Asteroids en C++ con OpenGL/GLUT.

## Requisitos

- CMake ≥ 3.10
- Compilador C++11 (g++, clang, MSVC)
- OpenGL
- GLUT (freeglut recomendado)

### Instalación de dependencias

**Linux (Arch)**
```
sudo pacman -S cmake freeglut mesa
```

**Linux (Debian/Ubuntu)**
```
sudo apt install cmake freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

**Windows (vcpkg)**
```
vcpkg install freeglut
```
Configurar CMake con `-DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake`.

**Windows (MSYS2)**
```
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-freeglut
```

**macOS**

GLUT incluido en sistema. Solo necesitas CMake:
```
brew install cmake
```

## Compilar

```
cmake -S . -B build
cmake --build build
```

## Ejecutar

```
./build/AsteroidsGL
```

## Guía paso a paso: Visual Studio (Windows)

Requiere **Visual Studio 2019 o superior** con carga de trabajo **"Desarrollo para el escritorio con C++"** (incluye CMake, MSVC, Git).

### 1. Clonar repo

Opción A — desde terminal:
```
git clone <URL_DEL_REPO> asteroids
cd asteroids
```

Opción B — desde Visual Studio:
- `Archivo` → `Clonar repositorio…`
- Pegar URL, elegir carpeta local, `Clonar`.

### 2. Instalar freeglut con vcpkg

Abrir **Developer PowerShell for VS** (menú Inicio):
```
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
C:\vcpkg\bootstrap-vcpkg.bat
C:\vcpkg\vcpkg install freeglut:x64-windows
C:\vcpkg\vcpkg integrate install
```

El último comando registra vcpkg globalmente — Visual Studio detectará `freeglut` automáticamente.

### 3. Abrir proyecto

- Visual Studio → `Archivo` → `Abrir` → `Carpeta…`
- Seleccionar carpeta `asteroids` (la que contiene `CMakeLists.txt`).
- VS detecta CMake y configura solo. Esperar a "Generación de CMake finalizada" en `Salida`.

Si no detecta vcpkg, añadir en `CMakeSettings.json` (botón `Administrar configuraciones…`):
```json
"cmakeToolchain": "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

### 4. Compilar

- Barra superior: seleccionar configuración `x64-Debug` (o `x64-Release`).
- `Compilar` → `Compilar todo` (`Ctrl+Shift+B`).

### 5. Ejecutar

- Barra superior: desplegable junto al botón verde ▶ → elegir `AsteroidsGL.exe`.
- Pulsar ▶ o `F5` (debug) / `Ctrl+F5` (sin debug).

Binario queda en `out\build\x64-Debug\AsteroidsGL.exe`.

### Problemas comunes

- **`Cannot find GLUT`** → vcpkg no integrado. Repetir `vcpkg integrate install` o añadir `cmakeToolchain` arriba.
- **`glut32.dll not found` al ejecutar** → ignorar, no se usa. Si aparece, falta DLL de freeglut: vcpkg debería copiarla; verificar `out\build\x64-Debug\freeglut.dll`.
- **Pantalla negra / cierre inmediato** → ejecutar desde terminal para ver errores.

