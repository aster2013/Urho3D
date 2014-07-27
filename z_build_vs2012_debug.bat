call "%VS110COMNTOOLS%VsDevCmd.bat"
cd Build
msbuild.exe Urho3D.sln /m /consoleloggerparameters:PerformanceSummary;NoSummary;Verbosity=minimal %*
pause