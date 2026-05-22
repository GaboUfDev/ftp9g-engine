# ============================================================================
# FTP9G — Crear repo en GitHub + primer commit + push
# Para ejecutar en Windows PowerShell desde la carpeta donde descomprimiste el ZIP
# ============================================================================
# Pre-requisitos:
#   - Git instalado (>= 2.40)        winget install Git.Git
#   - Git LFS instalado              winget install GitHub.GitLFS
#   - GitHub CLI instalado y logueado: winget install GitHub.cli  &&  gh auth login
# ============================================================================

# ---- CONFIGURACIÓN: ajusta estos valores antes de correr ----
$RepoName    = "ftp9g-engine"
$Visibility  = "public"                       # public | private
$Description = "FTP9G - Flight Trainer Platform 9G - Engine (UE5 + C++)"
$GitUserName = "Gabriel Ugarte"                # nombre que aparece en commits
$GitUserMail = "gabriel.ugarte@microsoft.com"  # mail para commits (puede ser tu cuenta de GH noreply)
# -------------------------------------------------------------

Write-Host ""
Write-Host "==> Paso 1/7: validar herramientas" -ForegroundColor Cyan
foreach ($tool in @("git", "gh")) {
    if (-not (Get-Command $tool -ErrorAction SilentlyContinue)) {
        Write-Host "ERROR: '$tool' no encontrado. Instalalo y vuelve a correr el script." -ForegroundColor Red
        exit 1
    }
}
git lfs version | Out-Null
if ($LASTEXITCODE -ne 0) { Write-Host "ERROR: Git LFS no instalado." -ForegroundColor Red; exit 1 }
Write-Host "    OK - git, gh, git lfs presentes" -ForegroundColor Green

Write-Host ""
Write-Host "==> Paso 2/7: verificar que estamos dentro de la carpeta ftp9g-engine" -ForegroundColor Cyan
if (-not (Test-Path ".gitignore") -or -not (Test-Path ".gitattributes") -or -not (Test-Path "Source/FTP9G")) {
    Write-Host "ERROR: no veo .gitignore / .gitattributes / Source/FTP9G aqui." -ForegroundColor Red
    Write-Host "       Asegurate de correr este script DESDE adentro de la carpeta ftp9g-engine." -ForegroundColor Red
    exit 1
}
Write-Host "    OK - estamos en la carpeta correcta" -ForegroundColor Green

Write-Host ""
Write-Host "==> Paso 3/7: git init + identidad" -ForegroundColor Cyan
git init -b main
git config user.name  "$GitUserName"
git config user.email "$GitUserMail"
Write-Host "    OK" -ForegroundColor Green

Write-Host ""
Write-Host "==> Paso 4/7: habilitar Git LFS" -ForegroundColor Cyan
git lfs install --local
Write-Host "    OK - LFS configurado en este repo" -ForegroundColor Green

Write-Host ""
Write-Host "==> Paso 5/7: primer commit" -ForegroundColor Cyan
git add .gitignore .gitattributes .editorconfig README.md Source Content
git status --short
$commitMsg = @"
Initial: Fase 0 setup - gitignore, LFS, C++ base, TP-150 RG config

- .gitignore UE5 (Binaries, Intermediate, Saved, DDC, IDE)
- .gitattributes con Git LFS para .uasset/.umap/.fbx/texturas/audio
- Source/FTP9G con esqueleto C++:
  * AAircraftPawn + UAircraftConfigDataAsset
  * IFlightModel + UFlightModelSimple + UFlightModelComponent
  * UPropulsionComponent (Rotax 915 iS)
  * UFlightControlComponent
- Content/Data/Aircraft/TP150RG/aircraft.json (parametros de referencia)
- README con checklist de setup UE5 + Visual Studio 2022 + Copilot
"@
git commit -m $commitMsg
Write-Host "    OK - primer commit creado" -ForegroundColor Green

Write-Host ""
Write-Host "==> Paso 6/7: crear repo remoto en GitHub" -ForegroundColor Cyan
gh repo create $RepoName --$Visibility --description "$Description" --source=. --remote=origin
if ($LASTEXITCODE -ne 0) {
    Write-Host "WARN: 'gh repo create' fallo. Probablemente el repo ya existe." -ForegroundColor Yellow
    Write-Host "      Configurando remoto manualmente..." -ForegroundColor Yellow
    $GhUser = (gh api user -q ".login")
    git remote add origin "https://github.com/$GhUser/$RepoName.git" 2>$null
}
Write-Host "    OK" -ForegroundColor Green

Write-Host ""
Write-Host "==> Paso 7/7: push inicial" -ForegroundColor Cyan
git push -u origin main
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: push fallo. Revisa autenticacion (gh auth status) y vuelve a intentar:" -ForegroundColor Red
    Write-Host "       git push -u origin main" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "============================================================" -ForegroundColor Green
Write-Host " LISTO. Repo creado y pusheado." -ForegroundColor Green
Write-Host "============================================================" -ForegroundColor Green
$GhUser = (gh api user -q ".login")
Write-Host " URL: https://github.com/$GhUser/$RepoName" -ForegroundColor Green
Write-Host ""
Write-Host "Proximo paso: crear el proyecto UE 5.3 encima de esta carpeta." -ForegroundColor Cyan
Write-Host "Ver README.md seccion 'Setup inicial - paso 3'." -ForegroundColor Cyan
