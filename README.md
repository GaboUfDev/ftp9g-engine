# FTP9G — Engine

> **Flight Trainer Platform 9G**
> Plataforma de entrenamiento de vuelo — **NO es un juego**.
> Stack: Unreal Engine 5.3 + C++ + GitHub Copilot. Filosofía "Editor-last".

---

## Estructura del repo

```
ftp9g-engine/
├── .gitignore              # UE5 — todo lo autogenerado fuera del repo
├── .gitattributes          # Git LFS para assets binarios (.uasset, .umap, .fbx, etc.)
├── .editorconfig           # Estilo de código unificado
├── README.md               # Este archivo
├── FTP9G.uproject          # Manifiesto UE5 (se crea al iniciar el proyecto)
├── Source/
│   └── FTP9G/
│       ├── FTP9G.Build.cs        # Configuración de módulos
│       ├── FTP9G.h / FTP9G.cpp   # Entrypoint del módulo
│       ├── Aircraft/             # Pawn del avión + config data asset
│       ├── FlightModel/          # Interfaz IFlightModel + implementaciones
│       ├── Propulsion/           # Motor (Rotax 915 iS para TP-150 RG)
│       └── FlightControl/        # Superficies (alerones, elevador, rudder)
└── Content/
    └── Data/
        └── Aircraft/
            └── TP150RG/
                └── aircraft.json # Parámetros del primer avión
```

---

## Setup inicial — checklist

### 1. Pre-requisitos
- [ ] Windows 10/11 con Visual Studio 2022 (workload **Game development with C++**)
- [ ] Unreal Engine **5.3** instalado vía Epic Games Launcher
- [ ] Git ≥ 2.40
- [ ] Git LFS: `git lfs install`
- [ ] GitHub CLI: `gh auth login`
- [ ] **GitHub Copilot** habilitado en Visual Studio 2022 (extensión + sesión)

### 2. Crear el repo en GitHub
- [ ] Crear repositorio público `ftp9g-engine` en tu cuenta GitHub
- [ ] `git init` en la carpeta local
- [ ] Copiar `.gitignore`, `.gitattributes`, `.editorconfig`, `README.md` (los de este zip)
- [ ] `git lfs install`
- [ ] `git add .gitignore .gitattributes .editorconfig README.md`
- [ ] `git commit -m "Initial: gitignore + LFS config"`
- [ ] `git remote add origin git@github.com:<tu-usuario>/ftp9g-engine.git`
- [ ] `git push -u origin main`

### 3. Crear proyecto UE5
- [ ] Abrir Epic Games Launcher → Unreal Engine 5.3
- [ ] **Games → Blank → C++** (no Blueprint)
- [ ] Nombre: `FTP9G`, ubicación: la carpeta del repo
- [ ] **Starter Content: OFF**, **Raytracing: OFF** (lo activamos después si vale la pena)
- [ ] Esto crea `FTP9G.uproject` + `Source/FTP9G/` automáticamente

### 4. Plugin de Git (UEGitPlugin)
- [ ] Descargar [UEGitPlugin de ProjectBorealis](https://github.com/ProjectBorealis/UEGitPlugin)
- [ ] Copiar en `Plugins/UEGitPlugin/` (crear carpeta `Plugins/` en raíz)
- [ ] Editar `FTP9G.uproject` → agregar el plugin
- [ ] Editor → Source Control → Provider: **Git LFS 2**

### 5. Reemplazar el esqueleto autogenerado
- [ ] Copiar los archivos `.h` y `.cpp` de `Source/FTP9G/` de este zip sobre el `Source/FTP9G/` recién creado
- [ ] Reemplazar también `Source/FTP9G/FTP9G.Build.cs`
- [ ] En Visual Studio: clic derecho sobre `FTP9G.uproject` → **Generate Visual Studio project files**
- [ ] Build → Build Solution (Development Editor, Win64)

### 6. Verificar Copilot
- [ ] Abrir cualquier `.cpp` en Visual Studio
- [ ] Verificar que aparece el ícono de Copilot en la barra inferior
- [ ] Probar autocompletado en una función vacía

---

## Filosofía de desarrollo

1. **C++ first** — todo el código del simulador está en `Source/`. El UE Editor se usa para configurar assets, no para programar gameplay.
2. **Copilot first** — clases con headers claros y context inline. Copilot autocompleta implementaciones; nosotros revisamos.
3. **Data-driven** — configuraciones de aviones, lecciones y aeródromos viven en JSON / `UDataAsset`, NO en código.
4. **Multi-aircraft desde el día 1** — la arquitectura soporta agregar un nuevo avión sin tocar código del engine.
5. **Datos sensibles nunca al repo** — telemetría, grades y progreso de alumnos NO entran a este repositorio.

---

## Convenciones

- **Indentación**: tabs (4 spaces equivalentes) — estándar UE5.
- **Naming UE5**:
  - Clases que heredan de `AActor` → prefijo `A` (ej: `AAircraftPawn`)
  - Clases que heredan de `UObject` → prefijo `U` (ej: `UFlightModelComponent`)
  - Interfaces → prefijo `I` (ej: `IFlightModel`)
  - Data assets → sufijo `DataAsset` (ej: `UAircraftConfigDataAsset`)
- **Idioma del código**: inglés (identifiers, comments técnicos).
- **Idioma de documentación**: español (es-CL) — README, manuales, lecciones.

---

## Siguiente paso

Cuando esto compile sin errores y veas la cabecera "Welcome to FTP9G" en el log del Editor, pasamos a:
- Fase 0 / Paso 2 → cargar SCLC Vitacura como mapa de prueba.
- Fase 0 / Paso 3 → primer vuelo libre con teclado/joystick.

> Detalle completo en `ROADMAP.md` (carpeta FTP9G en OneDrive).
