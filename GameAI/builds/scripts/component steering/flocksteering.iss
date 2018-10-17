; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{699C19A9-3073-4C22-8796-4EFA87F6AFFD}
AppName=Flock Steering
AppVersion=1.0
;AppVerName=Flock Steering 1.0
AppPublisher=Walter Hill
AppPublisherURL=https://github.com/walthill/EGP-410/tree/master
AppSupportURL=https://github.com/walthill/EGP-410/tree/master
AppUpdatesURL=https://github.com/walthill/EGP-410/tree/master
DefaultDirName={pf}\Flock Steering
DefaultGroupName=Flock Steering
AllowNoIcons=yes
OutputBaseFilename=setupflocksteering
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\steering.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\vsdata\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\arrow.png"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\clapping.wav"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\cour.ttf"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\data.ini"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\enemy-arrow.png"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\libfreetype-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\libjpeg-9.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\libpng16-16.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\libtiff-5.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\libwebp-4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\SDL2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\SDL2_gfx.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\SDL2_image.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\SDL2_ttf.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\target.png"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\wallpaper.bmp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\student\Documents\waltdocs\EGP-410\GameAI\component steering SDL\Release\zlib1.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Flock Steering"; Filename: "{app}\steering.exe"
Name: "{commondesktop}\Flock Steering"; Filename: "{app}\steering.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Flock Steering"; Filename: "{app}\steering.exe"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\steering.exe"; Description: "{cm:LaunchProgram,Flock Steering}"; Flags: nowait postinstall skipifsilent
