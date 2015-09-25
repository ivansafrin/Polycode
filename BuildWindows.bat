@rem Configuration -------------------------------------------------------------

@rem Platform - either "Win32" or "x64"
if "%1%"=="" (
	@set platform=Win32

	@rem Visual Studio version to pass to cmake
	@set generator=Visual Studio 12
) else (
	@set platform=%1%
	if "%1%"=="Win32" (
		@rem Visual Studio version to pass to cmake
		@set generator=Visual Studio 12
	) else (
		@rem Visual Studio version to pass to cmake
		@set generator=Visual Studio 12 Win64
	)
)

@rem Visual C++ compiler path, where 'vcvarsall.bat' is located
@set vcPath=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC

@rem Optional cmake path. Set manually only if not set in PATH system variable
@set cmakePath=

@rem Optional Python path. Set manually only if not set in PATH system variable
@set pythonPath=C:\Python27

@rem Begin build ---------------------------------------------------------------

@set baseDir=%cd%

@call "%vcPath%\vcvarsall.bat" x86
@if %errorlevel% neq 0 goto error
@for %%x in (MSBuild.exe) do @(set msbuildFound=%%~$PATH:x)
@if not defined msbuildFound echo MSBuild.exe not found. Edit 'vcPath' variable to correct path. & goto error

@if defined cmakePath set PATH=%PATH%;%cmakePath%
@for %%x in (cmake.exe) do @(set cmakeFound=%%~$PATH:x)
@if not defined cmakeFound echo cmake.exe not found. Edit 'cmakePath' variable to correct path. & goto error

@if defined pythonPath set PATH=%PATH%;%pythonPath%
@for %%x in (python.exe) do @(set pythonFound=%%~$PATH:x)
@if not defined pythonFound echo python.exe not found. Edit 'pythonPath' variable to correct path. & goto error

@echo Building with "%generator%" for "%platform%"...

@rem cleaning up --------------------------------------------------------------
@cd "%baseDir%"
:while0
@if exist Release rmdir /s /q Release
@if exist Release goto while0

@rem Build Dependencies --------------------------------------------------------

@cd "%baseDir%"
@if %errorlevel% neq 0 goto error
@cd Dependencies
@if %errorlevel% neq 0 goto error

:while1
@if exist Build rmdir /s /q Build
@if exist Build goto while1

@mkdir Build
@if %errorlevel% neq 0 goto error
@cd Build
@if %errorlevel% neq 0 goto error

@cmake -G "%generator%" ..
@if %errorlevel% neq 0 goto error

@MSBuild.exe /nologo /property:Configuration=Debug ALL_BUILD.vcxproj
@if %errorlevel% neq 0 goto error
@MSBuild.exe /nologo /property:Configuration=Debug glext.vcxproj
@if %errorlevel% neq 0 goto error
@MSBuild.exe /nologo /property:Configuration=Debug wglext.vcxproj
@if %errorlevel% neq 0 goto error

@MSBuild.exe /nologo /property:Configuration=Release ALL_BUILD.vcxproj
@if %errorlevel% neq 0 goto error
@MSBuild.exe /nologo /property:Configuration=Release glext.vcxproj
@if %errorlevel% neq 0 goto error
@MSBuild.exe /nologo /property:Configuration=Release wglext.vcxproj
@if %errorlevel% neq 0 goto error

@rem Build Polycode ------------------------------------------------------------

@cd "%baseDir%"
@if %errorlevel% neq 0 goto error

:while2
@if exist Build rmdir /s /q Build
@if exist Build goto while2

@mkdir Build
@if %errorlevel% neq 0 goto error
@cd Build
@if %errorlevel% neq 0 goto error

@cmake -G "%generator%" .. -DPOLYCODE_BUILD_BINDINGS=ON -DPOLYCODE_BUILD_PLAYER=ON
@if %errorlevel% neq 0 goto error

@MSBuild.exe /nologo /property:Configuration=Debug ALL_BUILD.vcxproj
@if %errorlevel% neq 0 goto error
@MSBuild.exe /nologo /property:Configuration=Debug Bindings\Contents\LUA\PolycodeLua.vcxproj
@if %errorlevel% neq 0 goto error

@MSBuild.exe /nologo /property:Configuration=Release ALL_BUILD.vcxproj
@if %errorlevel% neq 0 goto error
@MSBuild.exe /nologo /property:Configuration=Release Bindings\Contents\LUA\PolycodeLua.vcxproj
@if %errorlevel% neq 0 goto error

@MSBuild.exe /nologo /property:Configuration=Debug INSTALL.vcxproj
@if %errorlevel% neq 0 goto error
@MSBuild.exe /nologo /property:Configuration=Release INSTALL.vcxproj
@if %errorlevel% neq 0 goto error

@rem Build Standalone ----------------------------------------------------------

@cd "%baseDir%"
@if %errorlevel% neq 0 goto error
@cd Standalone
@if %errorlevel% neq 0 goto error

:while3
@if exist Build rmdir /s /q Build
@if exist Build goto while3

@mkdir Build
@if %errorlevel% neq 0 goto error
@cd Build
@if %errorlevel% neq 0 goto error

@cmake -G "%generator%" ..
@if %errorlevel% neq 0 goto error

@MSBuild.exe /nologo /property:Configuration=Release INSTALL.vcxproj
@if %errorlevel% neq 0 goto error

@rem Build IDE -----------------------------------------------------------------

@cd "%baseDir%"
@if %errorlevel% neq 0 goto error
@cd IDE\Build\Windows2013
@if %errorlevel% neq 0 goto error

:while4
@if exist Release rmdir /s /q Release
@if exist x64 rmdir /s /q x64
@if exist Win32 rmdir /s /q Win32
@if exist Release goto while4
@if exist x64 goto while4
@if exist Win32 goto while4

@MSBuild.exe /nologo /property:Configuration=Release /property:Platform=%platform% Polycode.vcxproj
@if %errorlevel% neq 0 goto error

@rem End build -----------------------------------------------------------------

@goto success
:error
@echo:
@echo Build error.
@goto stop

:success
@echo:
@echo Build successful.
@goto stop

:stop
@cd "%baseDir%"