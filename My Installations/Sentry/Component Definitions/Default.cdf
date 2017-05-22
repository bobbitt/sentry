[Components]
component0=Help Files
component1=Program Files
component2=Security Tools

[Help Files]
required0=Program Files
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=Copying Help Files...
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component includes all help files for Sentry. It is strongly advised that you install these files.
DISPLAYTEXT=Help Files
IMAGE=
DEFSELECTION=Yes
filegroup0=Help Files
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=ALWAYSOVERWRITE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[TopComponents]
component0=Program Files
component1=Help Files
component2=Security Tools

[SetupType]
setuptype0=Compact
setuptype1=Typical
setuptype2=Custom

[SetupTypeItem-Compact]
Comment=
item0=Help Files
item1=Program Files
Descrip=Security Utilities are not installed
DisplayText=Compact Installation

[Program Files]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=Copying Program Files...
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component includes all files required to run Sentry.
DISPLAYTEXT=Program Files
IMAGE=
DEFSELECTION=Yes
filegroup0=Program Executable Files
requiredby0=Help Files
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=ALWAYSOVERWRITE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[SetupTypeItem-Custom]
Comment=
item0=Help Files
item1=Program Files
item2=Security Tools
Descrip=Install components are required
DisplayText=Custom Installation

[Security Tools]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=Copying Security Tools...
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=This component contains SDEL, a secure delete utility.
DISPLAYTEXT=Security Tools
IMAGE=
DEFSELECTION=Yes
filegroup0=Security Tools
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=ALWAYSOVERWRITE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Info]
Type=CompDef
Version=1.00.000
Name=

[SetupTypeItem-Typical]
Comment=
item0=Help Files
item1=Program Files
item2=Security Tools
Descrip=All components are installed
DisplayText=Typical Installation

