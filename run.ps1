# Créer le dossier de build si nécessaire
if (-not (Test-Path build)) { New-Item -Path build -ItemType Directory }

Write-Host "--- Compilation en cours ---" -ForegroundColor Cyan
cd build
cmake ..
cmake --build . --config Release

# Vérifier si l'exécutable existe (en cherchant dans Debug ou à la racine du build)
$exePath = "Release/ai_lib.exe"

if (Test-Path $exePath) {
    Write-Host "--- Lancement de l'application ---" -ForegroundColor Green
    & $exePath
} else {
    Write-Host "Erreur : ai_lib.exe introuvable après compilation." -ForegroundColor Red
}
cd ..