Option Explicit
On Error Resume Next

' Tool version (matches Dolphin3D engine version)
Const TOOL_VERSION = "1.0"

' Main objects
Dim fso, shell, currentDir, cacheDir, cacheFile

' Initialize objects
Set fso = CreateObject("Scripting.FileSystemObject")
Set shell = CreateObject("WScript.Shell")
currentDir = fso.GetParentFolderName(WScript.ScriptFullName)
cacheDir = currentDir & "\cache"
cacheFile = cacheDir & "\versions.data"

' Ensure cache directory exists
Sub EnsureCacheDir()
    If Not fso.FolderExists(cacheDir) Then
        fso.CreateFolder cacheDir
        If Err.Number <> 0 Then
            MsgBox "Error creating cache directory: " & Err.Description, vbExclamation
        End If
    End If
End Sub

' Extract numeric version from string
Function ExtractNumericVersion(versionString)
    Dim result, i, ch
    result = ""
    For i = 1 To Len(versionString)
        ch = Mid(versionString, i, 1)
        If IsNumeric(ch) Or ch = "." Then
            result = result & ch
        End If
    Next
    ExtractNumericVersion = result
End Function

' Improved version comparison
Function CompareVersions(v1, v2)
    Dim parts1, parts2, i, p1, p2, maxLen
    
    ' Clean version strings
    v1 = ExtractNumericVersion(v1)
    v2 = ExtractNumericVersion(v2)
    
    parts1 = Split(v1, ".")
    parts2 = Split(v2, ".")
    
    ' Find maximum length
    maxLen = UBound(parts1)
    If UBound(parts2) > maxLen Then maxLen = UBound(parts2)
    
    For i = 0 To maxLen
        If i > UBound(parts1) Then
            p1 = 0
        Else
            If IsNumeric(parts1(i)) Then
                p1 = CInt(parts1(i))
            Else
                p1 = 0
            End If
        End If
        
        If i > UBound(parts2) Then
            p2 = 0
        Else
            If IsNumeric(parts2(i)) Then
                p2 = CInt(parts2(i))
            Else
                p2 = 0
            End If
        End If
        
        If p1 > p2 Then
            CompareVersions = 1
            Exit Function
        ElseIf p1 < p2 Then
            CompareVersions = -1
            Exit Function
        End If
    Next
    
    CompareVersions = 0
End Function

' Check if version has suffix (beta, dev, etc)
Function HasVersionSuffix(versionString)
    Dim cleanVersion, i, ch, hasNonNumeric
    cleanVersion = ""
    hasNonNumeric = False
    
    For i = 1 To Len(versionString)
        ch = Mid(versionString, i, 1)
        If IsNumeric(ch) Or ch = "." Then
            cleanVersion = cleanVersion & ch
        Else
            hasNonNumeric = True
        End If
    Next
    
    HasVersionSuffix = hasNonNumeric
End Function

' Download data from internet with timeout
Function DownloadFromInternet()
    On Error Resume Next
    Dim http, url, data, startTime, timeout
    
    url = "https://raw.githubusercontent.com/ColorProgrammy/Dolphin3D/refs/heads/main/Tools/compatibility/cache/versions.data"
    timeout = 10000 ' 10 seconds
    
    Set http = CreateObject("MSXML2.XMLHTTP.6.0")
    If Err.Number <> 0 Then
        Set http = CreateObject("Microsoft.XMLHTTP")
    End If
    
    If Err.Number <> 0 Then
        DownloadFromInternet = ""
        Exit Function
    End If
    
    http.Open "GET", url, False
    http.Send
    
    If http.Status = 200 Then
        data = http.ResponseText
        If Len(Trim(data)) > 10 Then
            DownloadFromInternet = data
        Else
            DownloadFromInternet = ""
        End If
    Else
        DownloadFromInternet = ""
    End If
End Function

' Read data from cache
Function ReadFromCache()
    On Error Resume Next
    Dim file, data
    
    If fso.FileExists(cacheFile) Then
        Set file = fso.OpenTextFile(cacheFile, 1, False)
        data = file.ReadAll
        file.Close
        
        If Len(Trim(data)) > 10 Then
            ReadFromCache = data
        Else
            ReadFromCache = ""
        End If
    Else
        ReadFromCache = ""
    End If
End Function

' Write data to cache
Sub WriteToCache(data)
    On Error Resume Next
    EnsureCacheDir
    
    Dim file
    Set file = fso.CreateTextFile(cacheFile, True)
    If Err.Number = 0 Then
        file.Write data
        file.Close
    End If
End Sub

' Get version data
Function GetVersionData()
    Dim data
    
    ' Try cache first (faster)
    data = ReadFromCache()
    If Len(data) > 10 Then
        GetVersionData = data
        Exit Function
    End If
    
    ' Try to download
    data = DownloadFromInternet()
    If Len(data) > 10 Then
        WriteToCache data
        GetVersionData = data
    Else
        GetVersionData = ""
    End If
End Function

' Get latest version from data
Function GetLatestVersion(data)
    Dim lines, line, parts
    
    ' Normalize line endings
    data = Replace(data, vbCrLf, vbLf)
    data = Replace(data, vbCr, vbLf)
    lines = Split(data, vbLf)
    
    For Each line in lines
        line = Trim(line)
        If Left(line, 7) = "latest=" Then
            parts = Split(line, "=")
            If UBound(parts) >= 1 Then
                GetLatestVersion = Trim(parts(1))
                Exit Function
            End If
        End If
    Next
    
    GetLatestVersion = ""
End Function

' Get version info from data
Function GetVersionInfo(data, version)
    Dim lines, line, parts, prefix, status, message, cleanVersion
    status = ""
    message = ""
    
    ' Normalize line endings
    data = Replace(data, vbCrLf, vbLf)
    data = Replace(data, vbCr, vbLf)
    lines = Split(data, vbLf)
    
    ' Get clean version
    cleanVersion = ExtractNumericVersion(version)
    
    ' Try exact match first (with suffix)
    prefix = "version_" & version & "_"
    
    For Each line in lines
        line = Trim(line)
        If Left(line, Len(prefix)) = prefix Then
            parts = Split(line, "=")
            If UBound(parts) >= 1 Then
                If InStr(line, prefix & "status=") = 1 Then
                    status = Trim(parts(1))
                ElseIf InStr(line, prefix & "message=") = 1 Then
                    message = Trim(parts(1))
                End If
            End If
        End If
    Next
    
    ' If not found and clean version is not empty, try numeric version match
    If status = "" And cleanVersion <> "" And cleanVersion <> version Then
        prefix = "version_" & cleanVersion & "_"
        
        For Each line in lines
            line = Trim(line)
            If Left(line, Len(prefix)) = prefix Then
                parts = Split(line, "=")
                If UBound(parts) >= 1 Then
                    If InStr(line, prefix & "status=") = 1 Then
                        status = Trim(parts(1))
                    ElseIf InStr(line, prefix & "message=") = 1 Then
                        message = Trim(parts(1))
                    End If
                End If
            End If
        Next
    End If
    
    Dim info(1)
    info(0) = status
    info(1) = message
    GetVersionInfo = info
End Function

' Get status text
Function GetStatusText(statusCode)
    Select Case statusCode
        Case "0": GetStatusText = "OUTDATED"
        Case "1": GetStatusText = "USABLE"
        Case "2": GetStatusText = "LATEST"
        Case "3": GetStatusText = "BETA/TEST"
        Case Else: GetStatusText = "UNKNOWN"
    End Select
End Function

' Main check function
Function CheckVersion(version)
    Dim data, latest, info, status, message, result, comparison
    Dim cleanVersion, originalVersion
    
    ' Store original version and get clean version
    originalVersion = Trim(version)
    cleanVersion = ExtractNumericVersion(originalVersion)
    
    ' Get data
    data = GetVersionData()
    
    If Len(data) = 0 Then
        result = "Dolphin3D Compatibility Check" & vbCrLf & String(35, "-") & vbCrLf
        result = result & "Tool version: " & TOOL_VERSION & vbCrLf & vbCrLf
        result = result & "Your version: " & originalVersion & vbCrLf & vbCrLf
        result = result & "ERROR: No version data available." & vbCrLf
        result = result & "Check internet connection or update cache."
        CheckVersion = result
        Exit Function
    End If
    
    ' Get latest version
    latest = GetLatestVersion(data)
    
    ' Get version info
    info = GetVersionInfo(data, originalVersion)
    status = info(0)
    message = info(1)
    
    ' Build result
    result = "Dolphin3D Compatibility Check" & vbCrLf & String(35, "-") & vbCrLf
    result = result & "Tool version: " & TOOL_VERSION & vbCrLf & vbCrLf
    result = result & "Your version: " & originalVersion & vbCrLf
    result = result & "Latest stable: " & latest & vbCrLf & vbCrLf
    
    ' Determine status
    If Len(status) > 0 Then
        ' Version found in data
        result = result & "STATUS: " & GetStatusText(status) & vbCrLf & vbCrLf
        result = result & message
    Else
        ' Version not in data, compare with latest
        If Len(latest) = 0 Then
            result = result & "STATUS: UNKNOWN" & vbCrLf & vbCrLf
            result = result & "Cannot determine version status."
        Else
            comparison = CompareVersions(cleanVersion, latest)
            
            If comparison = 0 Then
                ' Versions are numerically equal
                If HasVersionSuffix(originalVersion) Then
                    result = result & "STATUS: BETA/TEST" & vbCrLf & vbCrLf
                    result = result & "Your version is a development version with same numeric version as stable."
                Else
                    result = result & "STATUS: LATEST" & vbCrLf & vbCrLf
                    result = result & "Your version matches the latest stable release."
                End If
            ElseIf comparison > 0 Then
                ' Version is newer than latest stable
                result = result & "STATUS: BETA/TEST" & vbCrLf & vbCrLf
                result = result & "Your version appears to be newer than the latest stable release."
            Else
                ' Version is older than latest stable
                result = result & "STATUS: OUTDATED" & vbCrLf & vbCrLf
                result = result & "Your version is older than the latest stable release."
                result = result & vbCrLf & vbCrLf & "Recommendation: Update to version " & latest
            End If
        End If
    End If
    
    CheckVersion = result
End Function

' Quick check - проверяет версию движка без запроса
Sub QuickCheckEngine()
    Dim result
    result = CheckVersion(TOOL_VERSION)
    MsgBox result, vbInformation, "Dolphin3D Engine Check"
End Sub

' Custom check
Sub CustomVersionCheck()
    Dim version, result
    version = InputBox("Enter Dolphin3D version to check (e.g., 1.0):", "Custom Version Check", TOOL_VERSION)
    If version <> "" Then
        result = CheckVersion(Trim(version))
        MsgBox result, vbInformation, "Custom Version Check"
    Else
        MsgBox "No version entered. Operation cancelled.", vbInformation, "Custom Version Check"
    End If
End Sub

' Update cache
Sub UpdateCache()
    Dim data, result, latest
    
    data = DownloadFromInternet()
    
    result = "Cache Update" & vbCrLf & String(20, "-") & vbCrLf & vbCrLf
    
    If Len(data) > 10 Then
        WriteToCache data
        latest = GetLatestVersion(data)
        
        result = result & "SUCCESS: Cache updated" & vbCrLf & vbCrLf
        result = result & "Latest version: " & latest & vbCrLf
        result = result & "Data size: " & Len(data) & " bytes" & vbCrLf
        result = result & "Tool version: " & TOOL_VERSION
    Else
        result = result & "FAILED: Cannot update cache" & vbCrLf & vbCrLf
        result = result & "Check internet connection or try again later."
    End If
    
    MsgBox result, vbInformation, "Update Cache"
End Sub

' Clear cache
Sub ClearCache()
    On Error Resume Next
    
    If fso.FileExists(cacheFile) Then
        fso.DeleteFile cacheFile, True
        If Err.Number = 0 Then
            MsgBox "Cache cleared successfully", vbInformation, "Clear Cache"
        Else
            MsgBox "Error clearing cache: " & Err.Description, vbExclamation, "Clear Cache"
        End If
    Else
        MsgBox "Cache file doesn't exist", vbInformation, "Clear Cache"
    End If
End Sub

' About dialog
Sub ShowAbout()
    Dim aboutText
    
    aboutText = "Dolphin3D Compatibility Checker" & vbCrLf
    aboutText = aboutText & "Version: " & TOOL_VERSION & vbCrLf
    aboutText = aboutText & String(30, "-") & vbCrLf & vbCrLf
    aboutText = aboutText & "Checks Dolphin3D version compatibility" & vbCrLf & vbCrLf
    aboutText = aboutText & "Status codes:" & vbCrLf
    aboutText = aboutText & "0 - OUTDATED: Update recommended" & vbCrLf
    aboutText = aboutText & "1 - USABLE: Works but not latest" & vbCrLf
    aboutText = aboutText & "2 - LATEST: Up to date" & vbCrLf
    aboutText = aboutText & "3 - BETA/TEST: Development version" & vbCrLf & vbCrLf
    
    MsgBox aboutText, vbInformation, "About"
End Sub

' Main menu
Sub ShowMainMenu()
    Dim choice
    
    Do
        choice = InputBox( _
            "Dolphin3D Compatibility Checker v1.0" & vbCrLf & _
            "Engine version: " & TOOL_VERSION & vbCrLf & _
            String(35, "-") & vbCrLf & vbCrLf & _
            "1. Quick check: Current engine version" & vbCrLf & _
            "2. Custom check: Any version" & vbCrLf & _
            String(20, "-") & vbCrLf & _
            "3. Update version data cache" & vbCrLf & _
            "4. Clear cache data" & vbCrLf & _
            "5. About" & vbCrLf & _
            "6. Exit" & vbCrLf & vbCrLf & _
            "Enter choice (1-6):", _
            "Dolphin3D Compatibility Checker", "1")
        
        If choice = "" Then Exit Do
        
        Select Case Trim(choice)
            Case "1"
                QuickCheckEngine
                
            Case "2"
                CustomVersionCheck
                
            Case "3"
                UpdateCache
                
            Case "4"
                ClearCache
                
            Case "5"
                ShowAbout
                
            Case "6"
                Exit Do
                
            Case Else
                MsgBox "Invalid choice. Please enter 1-6.", vbExclamation, "Error"
        End Select
    Loop
    
    MsgBox "Goodbye!", vbInformation, "Dolphin3D Checker"
End Sub

If WScript.Arguments.Count > 0 Then
    Dim argVersion, checkResult
    argVersion = Trim(WScript.Arguments(0))
    argVersion = Replace(argVersion, """", "")
    
    If LCase(argVersion) = "quick" Or argVersion = "" Then
        checkResult = CheckVersion(TOOL_VERSION)
        MsgBox checkResult, vbInformation, "Quick Engine Check"
    Else
        checkResult = CheckVersion(argVersion)
        MsgBox checkResult, vbInformation, "Version Check"
    End If
Else
    ShowMainMenu

End If
