# PTrain

This is the main source repository for the MVFT realtime aircraft simulator for use in prototyping and pilot training. 

## Setup
To configure a CAEN machine to use the simulator in-editor, follow these instructions:
1. Use AppsAnywhere to install Visual Studio and Unreal Engine 4.26 (NOT 4.23!)
2. `git clone --depth=1` (to avoid downloading the entire history) __into `C:\TEMP`__. This is very important, because the temp folder is not networked. If you try to open the project from your home folder, it will probably not work.
    - because of this, you must commit and push all changes you make before logging out, otherwise you may lose your work.
3. Run `openall.bat` in the repository root folder. This will launch SteamVR and Unreal. Skip the SteamVR portions if you do not intend to use it. If there is an issue, you can open them manually by following these instructions:
    1. Launch SteamVR by going to `C:\Program Files (x86)\Steam\steamapps\common\SteamVR\bin\win64` and opening `vrstartup.exe`. SteamVR may take you through the room configuration. Follow the on-screen prompts for room-size VR. 
    2. Open the PTrainer repository folder in Explorer and right-click `PTrain.uproject`, then select Open With, select Choose an App from this PC, then navigate to `C:\Program Files\Epic Games\UE_4.26\Engine\Binaries\Win64\UE4_Editor.exe`
6. On first-time launch, Unreal should ask to compile content, press Yes, then that should complete and the editor window should appear.
    - Wait for shaders to finish compiling for visuals to be correct
    - It will take around 20 minutes for Unreal to first-time launch on a CAEN computer, so if it looks stuck, it's not, just give it some time (subsequent launches on the same machine will be much faster)
7. To run in VR, select the dropdown menu next to Play, and select VR Preview. It will launch a separate window. To exit, press the escape key or alt-tab to the Unreal window.
    
To configure on a personal computer:
1. Install prerequisites for your platform:
    - All: SteamVR (optional) (for VR support, note SteamVR does not support macOS)
    - macOS: Xcode
    - Windows: Visual Studio with Desktop Development for C++ module
2. Install Unreal Engine. The installer should set `.uproject` file associations for you.
3. Download this repository as zip, or clone using `git clone --depth=1`
4. Open `PTrain.uproject`. When prompted to compile content, press Yes, and wait for that to complete. After that, the Editor window should appear. It should auto-launch SteamVR. If it does not, you must close Unreal, launch SteamVR manually, and then reopen Unreal. 

## Writing C++ code
1. Right-click `PTrain.uproject` and select Generate Xcode/Visual Studio Project
    - If this option is not available, open `PTrain.uproject` and go to File->Generate Xcode/Visual Studio Project
    - Afterwards, close the editor
2. Open the generated IDE project file and press the Start Debugging (Visual Studio) or Run (Xcode) button
    - This will launch the Editor with the debugger attached so C++ source debugging works
    - You can also use Attach To Process on an already-running Editor from your IDE to debug from there without restarting it

## 3D Models
We use Autodesk Maya for all model creation for use in the simulator. You can install Maya from AppsAnywhere when logged in to CAEN. You may optionally acquire a free student license for Maya from Autodesk
by providing a photo of your student ID when creating an educational account. 

### Modeling notes:
1. Save model files as **.ma** into the `Models` directory.
2. Export FBX files from maya into the `Models/exports` directory.
3. Ensure your Maya scene dimension is set to Centimeters (the default) or Meters.
4. Ensure transformations for your root object are frozen before export.
5. To import your FBX into unreal, drag the files from the file explorer to the `Content/Assets` directory. Then apply the following settings:
   - Generate Missing Collision: **false**
   - Material Import Method: **Do not Create Material**
   - Import Textures: **false**
6. To update your model in unreal after exporting a new version, right click the model in Assets and press Reimport.

## Usage In Editor
- The `Arena` Level file contains the simulated environment. Simply press Play to start the simulation

## Generating Builds
For CAEN
- Run `build.bat`.The built program will be written to the parent directory (not in the repository folder) named WindowsNoEditor

For other platforms
- Go to File->Package Project, and select the desired target. 
