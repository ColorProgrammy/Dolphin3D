Write-Host "Dolphin3D (v1.0) - Builder" -ForegroundColor Cyan
Write-Host ""

try {
    $null = Get-Command cmake -ErrorAction Stop
    Write-Host "CMake found" -ForegroundColor Green
} catch {
    Write-Host "ERROR: CMake not found!" -ForegroundColor Red
    Write-Host ""
    Write-Host "Please install CMake from:"
    Write-Host "https://cmake.org/download/"
    Write-Host ""
    Write-Host "Make sure CMake is in your PATH."
    pause
    exit 1
}

# Menu
Write-Host "Build options:"
Write-Host "1) Build"
Write-Host "2) Clean everything and exit"
Write-Host ""
$choice = Read-Host "Select [1-2]"

if ($choice -eq "2") {
    Write-Host ""
    Write-Host "Cleaning everything..." -ForegroundColor Yellow
    
    if (Test-Path "build") { Remove-Item "build" -Recurse -Force }
    if (Test-Path "bin\Dolphin3D.exe") { Remove-Item "bin\Dolphin3D.exe" -Force }
    if (Test-Path "bin\assets") { Remove-Item "bin\assets" -Recurse -Force }
    if (Test-Path "bin\BuildLog.txt") { Remove-Item "bin\BuildLog.txt" -Force }
    if (Test-Path "bin\Release") { Remove-Item "bin\Release" -Recurse -Force }
    
    Write-Host "Cleanup completed." -ForegroundColor Green
    pause
    exit 0
}

if ($choice -ne "1") {
    Write-Host "Invalid choice!" -ForegroundColor Red
    exit 1
}

# Build process
Write-Host ""
Write-Host "Starting build... (It may take a while)" -ForegroundColor Yellow
Write-Host ""

# Clean old files
if (Test-Path "build") {
    Write-Host "Removing old build directory..."
    Remove-Item "build" -Recurse -Force
}

if (Test-Path "bin\Dolphin3D.exe") {
    Write-Host "Removing old executable..."
    Remove-Item "bin\Dolphin3D.exe" -Force
}

if (!(Test-Path "bin")) { New-Item "bin" -ItemType Directory | Out-Null 

$logFile = "bin\BuildLog.txt"
"Build started: $(Get-Date)" | Out-File $logFile
"=================================" | Out-File $logFile -Append
"" | Out-File $logFile -Append

New-Item "build" -ItemType Directory | Out-Null
Set-Location "build"

Write-Host "Configuring project..." -ForegroundColor Yellow
cmake .. 2>&1 | Out-File "..\$logFile" -Append
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: CMake configuration failed!" -ForegroundColor Red
    Set-Location ..
    exit 1
}

Write-Host "Building project..." -ForegroundColor Yellow
cmake --build . --config Release 2>&1 | Out-File "..\$logFile" -Append
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: Build failed!" -ForegroundColor Red
    Set-Location ..
    exit 1
}

Set-Location ..

Write-Host "Copying executable..." -ForegroundColor Yellow
$exeCopied = $false

if (Test-Path "build\Release\Dolphin3D.exe") {
    Copy-Item "build\Release\Dolphin3D.exe" "bin\" -Force
    $exeCopied = $true
}
if (Test-Path "build\Dolphin3D.exe") {
    Copy-Item "build\Dolphin3D.exe" "bin\" -Force
    $exeCopied = $true
}
if (Test-Path "bin\Release\Dolphin3D.exe") {
    Copy-Item "bin\Release\Dolphin3D.exe" "bin\" -Force
    Remove-Item "bin\Release" -Recurse -Force -ErrorAction SilentlyContinue
    $exeCopied = $true
}

if (!$exeCopied) {
    Write-Host "ERROR: Executable not found!" -ForegroundColor Red
    exit 1
}

# Success message
Write-Host ""
Write-Host "Build successful!" -ForegroundColor Green
Write-Host ""

if (Test-Path "bin\Dolphin3D.exe") {
    $size = (Get-Item "bin\Dolphin3D.exe").Length
    Write-Host "Executable: bin\Dolphin3D.exe [$size bytes]" -ForegroundColor Yellow
}

# Clean up
if (Test-Path "build") {
    Write-Host "Cleaning up..."
    Remove-Item "build" -Recurse -Force
}

Write-Host ""
Write-Host "Build completed at $(Get-Date -Format 'HH:mm:ss')" -ForegroundColor Green
Write-Host "Log file: $logFile" -ForegroundColor Green
Write-Host ""

pause
