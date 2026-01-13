$path = "build\Debug\ai_lib.exe"
if (-not (Test-Path $path)) { $path = "build\ai_lib.exe" }

if (Test-Path $path) {
    & $path
} else {
    Write-Host "Erreur : ai_lib.exe introuvable. Avez-vous compile le projet ?" -ForegroundColor Red
}