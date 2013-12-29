SET VisualStudioVersion=11.0

cd Dependencies
mkdir Build
cd Build
cmake -G "Visual Studio 11" ..

"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Debug ALL_BUILD.vcxproj
"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Debug glext.vcxproj
"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Debug wglext.vcxproj

"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Release ALL_BUILD.vcxproj
"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Release glext.vcxproj
"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Release wglext.vcxproj

cd..
cd..

pause

mkdir Build
cd Build
cmake -G "Visual Studio 11" .. -DPOLYCODE_BUILD_BINDINGS=ON -DPOLYCODE_BUILD_PLAYER=ON

"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Debug ALL_BUILD.vcxproj
"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Debug PolycodeLua.vcxproj

"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Release ALL_BUILD.vcxproj
"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Release PolycodeLua.vcxproj

"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Debug INSTALL.vcxproj
"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Release INSTALL.vcxproj

cd..
pause

cd Standalone
mkdir Build
cd Build
cmake -G "Visual Studio 11" ..

"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Debug ALL_BUILD.vcxproj
"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Release ALL_BUILD.vcxproj

"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Debug INSTALL.vcxproj
"%windir%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe" /nologo /property:Configuration=Release INSTALL.vcxproj

cd..
cd..
pause